import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """add money to the account."""

    # check the method type
    if request.method == "GET":
        return render_template("cash.html")

    else:

        # get the value of the form field
        add_cash = request.form.get("cash")

        # validates if the user entered a value
        if not add_cash:
            return apology("Sorry! Enter a value", 403)

        # updates the balance amount
        db.execute("UPDATE users SET cash = cash + :add_cash WHERE id = :user_id",
            user_id = session["user_id"],
            add_cash = add_cash)

        # Flash info for the user
        flash(f"Congratulations, cash added!")

        # Redirect user to homepage
        return redirect("/")


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    """change passwords"""

    # if the method is GET, call the change.html
    if request.method =="GET":
        return render_template("change.html")

    else:

        # validates if the user entered the current password
        if not request.form.get("current_password"):

            return apology("Sorry! You must provide a current password", 403)

        else:
            # checks the password data of the logged in user
            rows = db.execute("SELECT * FROM users WHERE id = :user_id",
                              user_id = session["user_id"])

            # validates the current password
            if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("current_password")):
                return apology("invalid current password", 403)

        # validates if the user entered a new password
        if not request.form.get("new_password"):
            return apology("Sorry! You must provide a new password", 403)

        # validates if the user entered the password confirmation
        if not request.form.get("new_confirmation"):
            return apology("Sorry! You must provide a confirmation of new password", 403)

        # get the contents of the current form password
        current_password = request.form.get("current_password")

        # get the contents of the new form password
        new_password = request.form.get("new_password")

        # get the confirmation content of the new form password
        new_confirmation = request.form.get("new_confirmation")

        # checks if the current password and new password fields have equivalent content
        if current_password == new_password:
            return apology("Sorry! You must provide a different password than the previous one", 403)

        # checks if the password and confirmation fields have equivalent content
        if new_confirmation != new_password:
            return apology("Sorry! You must provide the equivalent password and password confirmation", 403)

        # updates the user's password in the database
        db.execute("UPDATE users SET hash = :new_password WHERE id = :user_id",
                    new_password=generate_password_hash(new_password, method="sha256"),
                    user_id = session["user_id"])

        # Flash info for the user
        flash(f"Congratulations, password changed!")

        # Redirect user to home page
        return redirect("/")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # obtains the data of the logged user's portfolio
    portfolio = db.execute("SELECT symbol, shares FROM portfolios WHERE user_id = :user_id ORDER BY symbol DESC",
                    user_id = session["user_id"])

    # get the balance of the logged in user
    cash_balance = db.execute("SELECT cash FROM users WHERE id = :user_id",
                    user_id = session["user_id"])[0]["cash"]

    # checks if the user has actions
    if not portfolio:
        return render_template("index.html", cash_balance = usd(cash_balance), total = usd(cash_balance))

    total = 0

    # if the user has shares, scan the list and store it in array
    for stock in portfolio:
        name = price = lookup(stock["symbol"])["name"]
        stock.update({ "name": name })
        price = lookup(stock["symbol"])["price"]
        stock.update({ "price": usd(price) })
        value = price * stock["shares"]
        stock.update({ "value": usd(value) })
        total = total + value

    # Calculates the total value of shares purchased by adding the amount that the user already had balance
    total = total + cash_balance

    # returns the values to mount the "index.html"
    return render_template("index.html", portfolio = portfolio, cash_balance = usd(cash_balance), total = usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # if the method is GET, call the register page
    if request.method == "GET":
        return render_template("buy.html")
    else:

        # get the form fields
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # if the field is empty, returns message
        if not symbol:
            return apology("Sorry! You must provide a Simbol", 403)

        # if the entered symbol does not exist, returns a message
        if not lookup(symbol):
            return apology("Sorry! Stock not found", 403)

        # checks if the user has entered a positive integer
        if int(shares) <= 0:
            return apology("Sorry! Whole numbers only")

        # obtain customer account balance
        user_money = db.execute("SELECT cash FROM users WHERE id = :user_id",
                        user_id = session["user_id"])[0]["cash"]

        # checks the total value of the user's purchase
        total_buy = lookup(symbol)["price"] * int(shares)

        # checks if the user has money to buy
        if total_buy > user_money:
            return apology("Sorry! insufficient funds", 403)

        # otherwise, execute the purchase
        db.execute("INSERT INTO transactions (user_id, type, symbol, shares, price) VALUES (:user_id, :transaction_type, :symbol, :shares, :price)",
            user_id = session["user_id"],
            transaction_type = "buy",
            symbol = symbol,
            shares = int(shares),
            price = format(total_buy, '.2f'))

        # debit the purchase of the user's balance
        user_money = user_money - total_buy
        db.execute("UPDATE users SET cash = :user_money WHERE id = :user_id",
                    user_id = session["user_id"],
                    user_money = user_money)

        # checks if the user already has shares in the company
        portfolio = db.execute("SELECT shares FROM portfolios WHERE user_id = :user_id AND symbol = :symbol",
                        user_id = session["user_id"],
                        symbol = symbol)

        # If the user has already purchased
        if len(portfolio) == 1:

            # calculates total shares
            total_shares = portfolio[0]["shares"] + int(shares)

            # Updates the data with the new quantity
            db.execute("UPDATE portfolios SET shares = :shares WHERE user_id = :user_id AND symbol = :symbol",
                user_id = session["user_id"],
                symbol = symbol,
                shares = total_shares)

        # if the user has not purchased
        else:
            # insere um novo registro
            db.execute("INSERT INTO portfolios (user_id, symbol, shares) VALUES (:user_id, :symbol, :shares)",
                user_id = session["user_id"],
                symbol = symbol,
                shares = int(shares))

        # Flash info for the user
        flash(f"Congratulations, purchase made!")

        # Redirect user to homepage
        return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query data for history of transactions
    transactions = db.execute("SELECT date, type, symbol, shares, price FROM transactions WHERE user_id = :user_id ORDER BY date DESC",
                        user_id = session["user_id"])

    return render_template("history.html", transactions = transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    #if the method for GET, call the quote.html
    if request.method == "GET":

        return render_template("quote.html")

    else:

        #get the contents of the username field of the form
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Sorry! You must provide a Simbol", 403)

        elif not lookup(symbol):
            return apology("Stock not found", 403)

        quote = lookup(symbol)

        quote["price"] = usd(quote["price"])

        return render_template("quoted.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # if the method for GET, call the register.html
    if request.method =="GET":
        return render_template("register.html")
    else:
        # get the contents of the username field of the form
        username = request.form.get("username")

        # checks if the username field is empty, returning a message
        if not username:
            return apology("Sorry! You must provide a username", 403)
        else:
            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                              username=request.form.get("username"))

            # Ensure username exists and password is correct
            if len(rows) != 0:
                return apology("Sorry! This username already exists, please choose another one", 403)

        # get the contents of the password field from the form
        password = request.form.get("password")

        # checks if the password field is empty, returning a message
        if not password:
            return apology("Sorry! You must provide a password", 403)

        # take the contents of the confirmation field of the form
        confirmation = request.form.get("confirmation")

        # checks if the confirmation field is empty, returning a message
        if not confirmation:
            return apology("Sorry! You must provide a confirmation of password", 403)

        # checks if the password and confirmation fields have equivalent content
        if confirmation != password:
            return apology("Sorry! You must provide the equivalent password and password confirmation", 403)

        # insert the user into the database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=username, password=generate_password_hash(password, method="sha256"))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via GET
    if request.method == "GET":

        # Query database for stocks where user_id is equal to logged in user id
        portfolio = db.execute(
            "SELECT symbol FROM portfolios WHERE user_id =:user_id ORDER BY symbol ASC",
                        user_id = session["user_id"])

        return render_template("sell.html", portfolio = portfolio)

    else:
        # get the sales screen fields
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # check if the symbol field is blank
        if not symbol:
            return apology("Sorry! You must provide a Simbol", 403)

        # checks if the quantity field is blank
        elif int(shares) <= 0:
            return apology("Sorry! Whole numbers only", 403)

        # checks if the user already has shares in the company
        portfolio = db.execute("SELECT shares FROM portfolios WHERE user_id = :user_id AND symbol = :symbol",
                        user_id = session["user_id"],
                        symbol = symbol)

        # checks if the user has enough shares in his portfolio to sell
        if len(portfolio) != 1 or portfolio[0]["shares"] < int(shares):
            return apology("Sorry! Not enough shares", 403)

        # if he has it, calculates the value according to the current sales price
        price = lookup(symbol)["price"] * int(shares)

        # performs the sale of the stock
        db.execute("INSERT INTO transactions (user_id, type, symbol, shares, price) VALUES (:user_id, :transaction_type, :symbol, :shares, :price)",
            user_id = session["user_id"],
            transaction_type = "sell",
            symbol = symbol,
            shares = int(shares),
            price = format(price,".2f"))

        # checks the current balance of the logged in user
        cash_balance = db.execute("SELECT cash FROM users WHERE id = :user_id",
                        user_id = session["user_id"])[0]["cash"]

        # calculates the new balance according to the sale
        cash_balance = cash_balance + price

        # updates the new balance in the user's account
        db.execute("UPDATE users SET cash = :balance WHERE id = :user_id",
            user_id = session["user_id"],
            balance = cash_balance)

        # calculates the total shares sold, after sale
        total_shares = portfolio[0]["shares"] - int(shares)

        # updates the user's total actions
        db.execute("UPDATE portfolios SET shares = :shares WHERE user_id = :user_id AND symbol = :symbol",
            user_id = session["user_id"],
            symbol = symbol,
            shares = total_shares)

        # flash info for the user
        flash(f"Congratulations, successfully sold!")

        # redirect user to homepage
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
