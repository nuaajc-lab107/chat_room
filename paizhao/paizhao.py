import socket
import threading
import cv2
import requests

# 设置服务器的IP地址和端口
HOST = '1.14.63.108'  # 服务器的IP地址
PORT = 5080

# 创建 socket 对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

# 接收服务器发送的消息
def receive_message():
    while True:
        try:
            message = client_socket.recv(1024).decode("utf-8")
            if "paizhao" in message:
                # 拍摄照片
                cap = cv2.VideoCapture(0)
                ret, frame = cap.read()
                cap.release()
                # 将图像转换为JPEG格式
                _, img_encoded = cv2.imencode('.jpg', frame)
                img_bytes = img_encoded.tobytes()

                # 发送图像到Flask服务器
                url = 'http://1.14.63.108:8000/receive_image'
                files = {'image': ('image.jpg', img_bytes, 'image/jpeg')}
                response = requests.post(url, files=files)
                print(response.text)
            else:
                print(message)
        except Exception as e:
            print(f"Error: {e}")
            client_socket.close()
            break

# 创建线程处理发送和接收消息
receive_thread = threading.Thread(target=receive_message)
receive_thread.start()
