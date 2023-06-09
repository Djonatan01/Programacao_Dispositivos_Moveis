import os
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager

template_dir = os.path.abspath('./Templates')

app = Flask(__name__,
            template_folder=template_dir,
            static_url_path="/Public",
            static_folder='Public')

app.secret_key = 'aceleraDaDepressao'
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///easyinout.sqlite3"

db = SQLAlchemy(app)

login_manager = LoginManager()
login_manager.login_view = 'router.login.login'
login_manager.login_message = 'Realize o login para acessar essa página!'
login_manager.init_app(app)

