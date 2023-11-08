import socket
import threading
import cv2

# 设置服务器的IP地址和端口
HOST = '1.14.63.108'  # 服务器的IP地址
PORT = 5000

# 创建 socket 对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

# 接收服务器发送的消息
def receive_message():
    while True:
        try:
            message = client_socket.recv(1024).decode("utf-8")
            if "paizhao" in message:
                take_picture()
            else:
                print(message)
        except Exception as e:
            print(f"Error: {e}")
            client_socket.close()
            break

# 发送消息给服务器
def send_message():
    while True:
        message = input()
        client_socket.sendall(message.encode("utf-8"))

# 拍照并保存
def take_picture():
    cap = cv2.VideoCapture(0)
    ret, frame = cap.read()
    if ret:
        cv2.imwrite('captured_image.jpg', frame)
        print("照片已保存为 captured_image.jpg")
    cap.release()

# 创建线程处理发送和接收消息
receive_thread = threading.Thread(target=receive_message)
receive_thread.start()

send_thread = threading.Thread(target=send_message)
send_thread.start()
