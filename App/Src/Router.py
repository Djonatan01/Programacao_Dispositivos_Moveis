from flask import Blueprint
from Src.View.Home import Home
from Src.View.Traffic import Traffic
from Src.View.About import About
from Src.View.User import User
from Src.View.Login import Login
from Src.View.Func import Func

Router = Blueprint('router', __name__)

Router.register_blueprint(Home)
Router.register_blueprint(Traffic, url_prefix='/traffic')
Router.register_blueprint(About)
Router.register_blueprint(User, url_prefix='/user')
Router.register_blueprint(Func, url_prefix='/func')
Router.register_blueprint(Login)