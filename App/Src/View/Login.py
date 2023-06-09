from flask import Blueprint, render_template, request, flash, redirect,url_for
from Src.Model.BancoDados import FuncBd
from werkzeug.security import check_password_hash
from confg import login_manager
from flask_login import login_user, logout_user, login_required, current_user

Login = Blueprint('login', __name__)



@login_manager.user_loader
def load_user(employee_id):
  funcionario = FuncBd.query.filter_by(id=employee_id).first()         
  return funcionario
@Login.route('/login')
def login(): 
  return render_template('login.html')

@Login.route('/make-login', methods=['POST'])
def makeLogin():
  email = request.form.get('emailLogin')
  passwd = request.form.get('passwdLogin')
  employee = FuncBd.query.filter_by(email=email).first() 
  if request.method == 'POST': 
    if not employee or not check_password_hash(employee.senha, passwd):
      flash('Usuário ou senha não encontrados.', 'error') 
      return redirect(url_for('router.login.login'))
    else:
      load_user(employee.id)
      login_user(employee)
      print(current_user)
      return redirect(url_for('router.traffic.list', current_user=current_user.nome))
 
@Login.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('router.home.index'))
