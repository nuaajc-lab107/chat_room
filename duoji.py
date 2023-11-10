import socket
import threading
import RPi.GPIO as GPIO
import time

# 设置服务器的IP地址和端口
HOST = '1.14.63.108'  # 服务器的IP地址
PORT = 5080

# 创建 socket 对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

# 初始化昵称
nickname = "shumaipai"
client_socket.sendall(nickname.encode("utf-8"))

# 创建舵机控制相关的变量
P_SERVO = 7  # GPIO端口号，根据实际修改
fPWM = 50     # Hz (软件PWM方式，频率不能设置过高)
a = 10
b = 2
servo_initialized = False  # 作为全局变量

def setup():
    global pwm, servo_initialized
    # 检查PWM对象是否已经存在
    if not servo_initialized:
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(P_SERVO, GPIO.OUT)
        pwm = GPIO.PWM(P_SERVO, fPWM)
        pwm.start(0)
        servo_initialized = True

def setDirection(direction):
    duty = a / 180 * direction + b
    pwm.ChangeDutyCycle(duty)
    print("direction =", direction, "-> duty =", duty)
    time.sleep(1) 

# 接收服务器发送的消息
def receive_message():
    while True:
        try:
            message = client_socket.recv(1024).decode("utf-8")
            print(message)
            handle_command(message)
        except Exception as e:
            print(f"Error: {e}")
            client_socket.close()
            break

# 处理命令
def handle_command(command):
    try:
        # 尝试将消息转化为数字
        angle = int(command)
        # 初始化舵机控制
        setup()
        # 调用舵机控制函数
        setDirection(angle)
        setDirection(0)
    except ValueError:
        print("Invalid command format. Expected a number.")

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
