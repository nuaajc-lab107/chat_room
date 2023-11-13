from flask import Flask, render_template, request, send_file
import socket
app = Flask(__name__)

# 存储图片的路径
image_path = 'static/captured_image.jpg'

# 标记是否已经拍摄过照片
photo_taken = False

@app.route('/')
def index():
    return render_template('index.html')
@app.route('/receive_image', methods=['POST'])
def receive_image():
    image_file = request.files['image']
    image_file.save('static/image.jpg')  # 将图像保存到 static 文件夹
    return '图像接收成功'

@app.route('/take_photo', methods=['POST'])
def take_photo():
    global photo_taken

    # 检查是否已经拍摄过照片
    if not photo_taken:
        # 向树莓派发送拍照指令
        send_command_to_raspberry_pi('paizhao')

        # 标记已经拍摄过照片
        photo_taken = True

    # 显示照片页面
    return render_template('photo.html', image_path=image_path)

def send_command_to_raspberry_pi(command):
    # 树莓派的IP地址和端口
    raspberry_pi_ip = '1.14.63.108'
    raspberry_pi_port = 5080

    # 创建 socket 对象
    raspberry_pi_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    raspberry_pi_socket.connect((raspberry_pi_ip, raspberry_pi_port))

    # 向树莓派发送指令
    raspberry_pi_socket.sendall(command.encode("utf-8"))


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000)
