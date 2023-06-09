from flask import Blueprint, render_template, request, flash, redirect, url_for
from Src.Controller.Funcs import FuncsController
from Src.Model.BancoDados import FuncBd
from flask_login import login_required
from Src.Model import Regex

Func = Blueprint('func', __name__)

@Func.route('/list', defaults={'page':1}, methods=['GET'])
@Func.route('/list/<int:page>', methods=['GET'])
@login_required
def listFunc(page):
  _funcFilter=request.values.get('nomeFuncionario')
  if _funcFilter == 'None' or _funcFilter is None:
    _funcFilter=""  
  return render_template('listaFuncionario.html', listData=FuncsController.List(page,_funcFilter),_nomeFunc=_funcFilter)

@Func.route('/createFunc', methods=['GET', 'POST'])
@login_required
def createFunc():
  _registro=request.form.get('mat') 
  _nome=request.form.get('nome')
  _endereco=request.form.get('endereco')
  _contato=request.form.get('contato')
  _email=request.form.get('email')
  _senha=request.form.get('senha')
  
  if request.method == 'POST':
    if FuncsController.checkEmail(_email):
      flash('Email já cadastrado', 'error')
    else:
      if any((x is None or len(x)<1) for x in [_registro, _nome, _endereco, _contato , _email, _senha]):
        flash('Preencha todos os campos do formulário', 'error')
      else:
        if Regex.contatoRegex(_contato):
          if Regex.emailRegex(_email):
            if FuncsController.createFunc(_registro,_nome,_endereco,_contato,_email,_senha):      
              return redirect(url_for('router.func.listFunc'))
            else:
              flash('Funcionário já cadastrado', 'error')
          else:
            flash('E-mail inválido', 'error')
        else:
            flash('Celular inválido', 'error')
  return render_template('criarFuncionario.html')

@Func.route('/<int:id>/updateFunc', methods=['GET','POST'])
@login_required
def updateFunc(id):
  _registro=request.form.get('mat')  
  _nome=request.form.get('nome')
  _endereco=request.form.get('endereco')
  _contato=request.form.get('contato')
  _email=request.form.get('email')
  _senha=request.form.get('senha')

  _func = FuncBd.query.filter_by(id=id).first()
  if request.method == 'POST':
    if any((x is None or len(x)<1) for x in [_registro, _nome, _endereco, _contato , _email, _senha]):
        flash('Preencha todos os campos do formulário', 'error')
    else:
        if FuncsController.updateFunc(id, _registro,_nome,_endereco,_contato,_email,_senha):
          return redirect(url_for('router.func.listFunc'))
        else:
          flash('Funcionário já cadastrado', 'error')
  return render_template('atualizarFuncionario.html', func=_func) 

@Func.route('/<int:id>/removeFunc', methods=['GET','POST'])
@login_required
def removeFunc(id):
  FuncsController.removeFunc(id) 
  return redirect(url_for('router.func.listFunc'))

