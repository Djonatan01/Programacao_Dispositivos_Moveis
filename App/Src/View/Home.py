from flask import Blueprint, render_template

Home = Blueprint('home', __name__)

@Home.route('/')
def index():
  return render_template('index.html')
  
@Home.route('/home')
def home():
  return render_template('home.html')