# programa para criar uma pagina web com flask
from flask import Flask

# criando a variavel que vai instanciar a biblioteca flask
app = Flask(__name__)

# criando nossa primeira rota padrao
@app.route("/")
# criando uma funcao qq que retorna uma mensagem de texto na tela
def index():
    return "<h1>Hello, World!</h1>"

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
#               Hello, World!
#         </h1>
#     </body>
# </html>