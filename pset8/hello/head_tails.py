# programa para criar uma pagina web com flask
import random
from flask import Flask, render_template

# criando a variavel que vai instanciar a biblioteca flask
app = Flask(__name__)

# criando nossa primeira rota padrao
@app.route("/")
# criando uma funcao qq que retorna uma mensagem de texto na tela
def index():
    number = random.randint(0, 1)
    return render_template("index.html", number=number)

# criando uma segunda rota qq
@app.route("/goodbye")
def bye():
    return "Goodbye!"

# Como estava o index.html?
# <!DOCTYPE html>

# <html lang="en">
#     <head>
#         <title>Hello!</title>
#     </head>
#     <body>
#         <h1>
#           {% if number == 1 %}
#               Your coin flip is HEADS.
#           {% else %}
#               Your coin flip is TAILS.
#           {% endif %}
#         </h1>
#     </body>
# </html>