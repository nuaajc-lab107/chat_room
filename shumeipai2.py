import socket
import threading
import cv2
import RPi.GPIO as GPIO
import time

IN1 = 11  # IN1, 左前进 
IN2 = 12  # IN2, 左后退 
IN3 = 16  # IN3, 右前进 
IN4 = 15  # IN4, 右后退 
# 设置服务器的IP地址和端口
HOST = '1.14.63.108'  # 服务器的IP地址
PORT = 5080

# 创建 socket 对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

# 初始化昵称
nickname = "shumaipai"
client_socket.sendall(nickname.encode("utf-8"))

def init():
    
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(IN1,GPIO.OUT)
    GPIO.setup(IN2,GPIO.OUT)
    GPIO.setup(IN3,GPIO.OUT)
    GPIO.setup(IN4,GPIO.OUT)

def forward(sleep_time):
    init()
    GPIO.output(IN1,GPIO.HIGH)
    GPIO.output(IN2,GPIO.LOW)
    GPIO.output(IN3,GPIO.HIGH)
    GPIO.output(IN4,GPIO.LOW)
    time.sleep(sleep_time)
    GPIO.cleanup()
 
def back(sleep_time):
    init()
    GPIO.output(IN1,GPIO.LOW)
    GPIO.output(IN2,GPIO.HIGH)
    GPIO.output(IN3,GPIO.LOW)
    GPIO.output(IN4,GPIO.HIGH)
    time.sleep(sleep_time)
    GPIO.cleanup()
 
def left(sleep_time):
    init()
    GPIO.output(IN1,False)
    GPIO.output(IN2,False)
    GPIO.output(IN3,GPIO.HIGH)
    GPIO.output(IN4,GPIO.LOW)
    time.sleep(sleep_time)
    GPIO.cleanup()
 
def right(sleep_time):
    init()
    GPIO.output(IN1,GPIO.HIGH)
    GPIO.output(IN2,GPIO.LOW)
    GPIO.output(IN3,False)
    GPIO.output(IN4,False)
    time.sleep(sleep_time)
    GPIO.cleanup()
# 接收服务器发送的消息
def receive_message():
    while True:
        try:
            message = client_socket.recv(1024).decode("utf-8")
            if "l" in message:
                left(1)
                print(message)
            elif "r" in message:
                right(1)
                print(message)
            elif "f" in message:
                forward(1)
                print(message)
            elif "b" in message:
                back(1)
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

# 创建线程处理发送和接收消息
receive_thread = threading.Thread(target=receive_message)
receive_thread.start()

send_thread = threading.Thread(target=send_message)
send_thread.start()
