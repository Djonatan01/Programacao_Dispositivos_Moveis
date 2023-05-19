from Src.Model.BancoDados import FuncBd
from confg import db
from sqlalchemy.exc import IntegrityError

class FuncsController:  
  def createFunc(mat,nome,endereco,contato,email,senha):
    func = FuncBd(mat,nome,endereco,contato,email,senha)
    db.session.add(func) 
    try:
      db.session.commit()
      return True
    except IntegrityError:
      db.session.rollback
      return False

  def updateFunc(id, _registro, _nome, _endereco, _contato, _email, _senha):   
    try:
      FuncBd.query.filter_by(id=id).update({'mat':_registro,'nome':_nome, 'endereco':_endereco,'contato':_contato,'email':_email,'senha':_senha })
      db.session.commit()
      return True
    except IntegrityError:
      db.session.rollback
      return False
      
  def removeFunc(id):   
    _func = FuncBd.query.filter_by(id=id).first()    
    db.session.delete(_func)
    db.session.commit()
    
  def List(page, per_page=15):
    query = FuncBd.query.paginate(page=page, per_page=per_page)
    queryCount = FuncBd.query.count()
    return {
      "regFunc": query,
      "count": queryCount,
      "page": page,
      "per_page": per_page
    }