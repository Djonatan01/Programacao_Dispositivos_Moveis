import os
from flask import Flask
from flask_sqlalchemy import SQLAlchemy

template_dir = os.path.abspath('./Templates')

app = Flask(__name__,
            template_folder=template_dir,
            static_url_path="/Public",
            static_folder='Public')

app.secret_key = 'aceleraDaDepressao'
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///easyinout.sqlite3"

db = SQLAlchemy(app)
