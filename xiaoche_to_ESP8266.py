import socket
import keyboard

# 设置服务器的IP地址和端口
HOST = '1.14.63.108'  # 服务器的IP地址
PORT = 5080  # 注意使用云服务器时一定要开放端口

# 创建 socket 对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

def send_key(key):
    client_socket.sendall(key.encode('utf-8'))

if __name__ == "__main__":
    print("Press and hold a lowercase letter key to send it. Release the key to stop sending.")
    
    while True:
        key = keyboard.read_event().name
        if key and len(key) == 1 and key.isalpha() and key.islower():
            send_key(key)
