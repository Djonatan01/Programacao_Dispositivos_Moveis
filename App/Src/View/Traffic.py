from flask import Blueprint, render_template, request
from Src.Controller.RFID import RFID


Traffic = Blueprint('traffic', __name__)

@Traffic.route('/register/<rfid>', methods=['GET', 'POST'])    
def register(rfid):
  return "1" if RFID.Register(rfid) else "0"

@Traffic.route('/list', defaults={'page': 1}, methods=['GET','POST'])
@Traffic.route('/list/<int:page>', methods=['GET','POST'])
def list(page):
  _data=request.form.get('filtroData')  
  return render_template('lista.html', listData=RFID.List(page,_data))
#######################
#@Traffic.route('/filtro/<dataF>', methods=['GET', 'POST'])    
#def filtro(dataF):
#  data = dataF.strftime("%dd/%mm/%YYYY") 
#  print(data)
  #print(data1)
