from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///therapy.db")

@app.route("/", methods=["GET", "POST"])
def index():
    """Pagina principal"""

    professionals = db.execute("SELECT count(id) as qtde FROM professional")

    count = professionals[0]["qtde"]

    # Monta a tela "index.html"
    return render_template("index.html", count = count)


@app.route("/search", methods=["GET", "POST"])
def search():
    """Pagina de consulta dos profissionais cadastrados"""

    if request.method =="GET":

        # seleciona a lista de abordagens no BD
        subjects = db.execute("SELECT * FROM subjects")

        return render_template("search.html", subjects = subjects)

    else:
        # montar envio do POST

        # filtro: abordagens
        subject_id = request.form.get("subject")

        # selecionando os dados de acordo com o filtro
        professionals = db.execute("SELECT professional.*, subjects.title FROM professional JOIN subjects ON professional.subject_id = subjects.id WHERE subject_id = :subject_id ORDER BY professional.name ASC",
                        subject_id = subject_id)

        # seleciona a lista de abordagens no BD
        subjects = db.execute("SELECT * FROM subjects")

        return render_template("search.html", professionals = professionals, subjects = subjects)


@app.route("/give", methods=["GET", "POST"])
def give():
    """Pagina de cadastro dos profissionais"""

    if request.method =="GET":

        # seleciona a lista de abordagens no BD
        subjects = db.execute("SELECT * FROM subjects")

        # seleciona a lista de dias da semana no BD
        weekdays = db.execute("SELECT * FROM weekdays")

        return render_template("give.html", subjects = subjects,
                                            weekdays = weekdays)

    else:
        # montar envio do POST

        # setor: Seus dados
        name        = request.form.get("name")
        avatar      = request.form.get("avatar")
        whatsapp    = request.form.get("whatsapp")
        bio         = request.form.get("bio")

        # setor: abordagens
        subject_id      = request.form.get("subject")
        subject_license = request.form.get("license")

        # setor: horarios disponiveis
        # weekday_id  = request.form.get("weekday")
        # time_from   = request.form.get("time_from")
        # time_to     = request.form.get("time_to")

        # inserindo dados no BD
        db.execute("INSERT INTO professional (name, avatar, whatsapp, bio, subject_id, subject_license) VALUES (:name, :avatar, :whatsapp, :bio, :subject_id, :subject_license)",
            name = name,
            avatar = avatar,
            whatsapp = whatsapp,
            bio = bio,
            subject_id = subject_id,
            subject_license = subject_license)

        # # selecionando o id do profissional que acabamos de inserir
        # professional_id = db.execute("SELECT id FROM professional WHERE name = :name",
        #                                 name = name)

        # db.execute("INSERT INTO approaches (professional_id, subject_id, license, cost) VALUES (:professional_id, :subject_id, :license, :cost)",
        #     professional_id = int(professional_id),
        #     subject_id = int(subject_id),
        #     license = license,
        #     cost = str("0"))

        # db.execute("INSERT INTO therapy_schedule (professional_id, subject_id, weekday_id, time_from, time_to) VALUES (:professional_id, :subject_id, :weekday_id, :time_from, :time_to)",
        #     professional_id = int(professional_id),
        #     subject_id = int(subject_id),
        #     weekday_id = int(weekday_id),
        #     time_from = convert_hour_to_minute(time_from),
        #     time_to = convert_hour_to_minute(time_to))

        return redirect("/success")



@app.route("/success", methods=["GET", "POST"])
def success():
    """Pagina principal"""

    # Monta a tela "index.html"
    return render_template("success.html")


def convert_hour_to_minute(time):
    time_split = time.split(":")
    hours = int(time_split[0])
    minutes = int(time_split[1])

    total_hours = hours * 60
    total_minutes = total_hours + minutes

    return str(total_minutes)


def convert_minute_to_hour(total_minutes):

    if total_minutes >= 60:
        hours = int(total_minutes / 60)
        if int(total_minutes % 60) == 0:
            minutes = '00'
        else:
            minutes = int(total_minutes % 60)
    else:
        hours = '00'
        minutes = total_minutes

    time = str(hours) +':'+ str(minutes) #minutes[2:]

    return time