from flask import Flask, render_template, request
import socket
# 设置服务器的IP地址和端口
HOST = '1.14.63.108'  # 服务器的IP地址
PORT = 5080

# 创建 socket 对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/submit', methods=['POST'])
def submit():
    data_from_form = request.form['data']
    
    client_socket.sendall(data_from_form.encode("utf-8"))
    # 打印数据到控制台
    print(data_from_form)

    # 返回一个响应给前端
    return f'成功接收到数据：{data_from_form}'

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=5000)
