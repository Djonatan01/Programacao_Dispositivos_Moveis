from Src.Model.BancoDados import UserBd
from confg import db
from sqlalchemy.exc import IntegrityError

class UsersController:  
  def createUser(mat,rfid,nome,endereco,contato):
    user = UserBd(mat,rfid,nome,endereco,contato)
    db.session.add(user) 
    try:
      db.session.commit()
      return True
    except IntegrityError:
      db.session.rollback
      return False

  def updateUser(id, _registro, _rfid, _nome, _endereco, _contato):   
    try:
      UserBd.query.filter_by(id=id).update({'mat':_registro,'rfid':_rfid,'nome':_nome, 'endereco':_endereco,'contato':_contato})
      db.session.commit()
      return True
    except IntegrityError:
      db.session.rollback
      return False
      
  def removeUser(id):   
    _user = UserBd.query.filter_by(id=id).first()    
    db.session.delete(_user)
    db.session.commit()
    
  def List(page, _userFilter, per_page=15):
    if _userFilter == None:
      query = UserBd.query.paginate(page=page, per_page=per_page)
      queryCount = UserBd.query.count()
    else: 
      print(_userFilter)
      query = UserBd.query.filter(UserBd.nome.like('%'+_userFilter+'%')).paginate(page=page, per_page=per_page)  
      queryCount = UserBd.query.count()
    
    return {
      "regUser": query,
      "count": queryCount,
      "page": page,
      "per_page": per_page
    }