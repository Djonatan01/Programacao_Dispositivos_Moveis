from flask import Flask, render_template, request

app = Flask (__name__)

@app.route('/', methods=['GET',"POST"])
def main():
    #rfinput=rfid
    return render_template('index.html')

@app.route('/rfid_read/<rfid>',methods=['GET','POST'])
def rfid_read(rfid):
    
if __name__ == '__main__':
    app.run(debug=True)