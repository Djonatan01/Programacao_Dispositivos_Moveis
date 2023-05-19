from flask import Blueprint, render_template

About = Blueprint('about',__name__)

@About.route('/sobre')
def sobre():
  return render_template('sobre.html')