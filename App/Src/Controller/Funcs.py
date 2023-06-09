from Src.Model.BancoDados import FuncBd
from confg import db
from sqlalchemy.exc import IntegrityError
from werkzeug.security import generate_password_hash

class FuncsController:  
  def createFunc(mat,nome,endereco,contato,email,senha):
    passwd=generate_password_hash(senha)
    func = FuncBd(mat.upper(),nome.upper(),endereco.upper(),contato.upper(),email,passwd)
    db.session.add(func) 
    try:
      db.session.commit()
      return True
    except IntegrityError:
      db.session.rollback()
      return False

  def updateFunc(id, _registro, _nome, _endereco, _contato, _email, _senha):   
    try:
      passwd=generate_password_hash(_senha)
      FuncBd.query.filter_by(id=id).update({'mat':_registro.upper(),'nome':_nome.upper(), 'endereco':_endereco.upper(),'contato':_contato.upper(),'email':_email,'senha':passwd })
      db.session.commit()
      return True
    except IntegrityError:
      db.session.rollback()
      return False
      
  def removeFunc(id):   
    _func = FuncBd.query.filter_by(id=id).first()    
    db.session.delete(_func)
    db.session.commit()
    
  def List(page,_funcFilter, per_page=15):
    print(_funcFilter)
    if len(_funcFilter)<1 :
      query = FuncBd.query.paginate(page=page, per_page=per_page)
      queryCount = FuncBd.query.count()
    else:
      query = FuncBd.query.filter(FuncBd.nome.like('%'+_funcFilter+'%')).paginate(page=page, per_page=per_page)        
      queryCount = FuncBd.query.count()
    return {
      "regFunc": query,
      "count": queryCount,
      "page": page,
      "per_page": per_page
    }

  def checkEmail(_email):
    query=FuncBd.query.filter_by(email=_email).first()
    print(query)
    return False if query==None or query=='None' else True
    