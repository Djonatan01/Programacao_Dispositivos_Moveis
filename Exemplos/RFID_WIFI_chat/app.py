
from flask import Flask, request

app = Flask(__name__)

@app.route('/rfid', methods=['POST'])
def handle_rfid():
    rfid = request.form['rfid']
    print("RFID lido: " + rfid)
    if request.method == 'POST':
    # processa a solicitação POST
        return 'POST OK'
    else:
    # retorna um erro se a solicitação não for POST
        return 'Method Not Allowed', 405


if __name__ == '__main__':
    app.run(debug=True)
