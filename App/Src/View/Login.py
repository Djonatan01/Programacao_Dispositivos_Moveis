from flask import Blueprint, render_template

Login = Blueprint('login', __name__)

@Login.route('/login')
def login():
  return render_template('login.html')
