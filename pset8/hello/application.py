# programa para criar uma pagina web com flask
import random
from flask import Flask, render_template, request

# criando a variavel que vai instanciar a biblioteca flask
app = Flask(__name__)

# criando nossa primeira rota padrao
@app.route("/")
# criando uma funcao qq que retorna uma mensagem de texto na tela
def index():
    return render_template("index.html")

# criando uma segunda rota qq
@app.route("/hello")
def hello():
    name = request.args.get("name")
    if not name:
        return render_template("failure.html")
    return render_template("hello.html", name=name)