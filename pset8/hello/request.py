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


# Como estava o index.html?
# <!DOCTYPE html>

# <html lang="en">
#     <head>
#         <title>Hello!</title>
#     </head>
#     <body>
#         <form action="/hello">
#             <input name="name" type="text">
#             <input type="submit">
#         </form>
#     </body>
# </html>

# Como estava o hello.html?
# <!DOCTYPE html>

# <html lang="en">
#     <head>
#         <title>Hello!</title>
#     </head>
#     <body>
#         <h1>
#             Hello, {{ name }}!
#         </h1>
#     </body>
# </html>

# Como estava o failure.html?
# <!DOCTYPE html>

# <html lang="en">
#     <head>
#         <title>Hello!</title>
#         <style>
#             body
#             {
#                 color: red;
#             }
#         </style>
#     </head>
#     <body>
#         <h1>
#             You must provide a name!
#         </h1>
#     </body>
# </html>