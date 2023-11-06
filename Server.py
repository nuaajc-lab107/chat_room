import socket
import threading

# 服务器地址和端口
HOST = '0.0.0.0'  # 可以尝试使用 '1.14.63.108' 或 '0.0.0.0'
PORT = 5000

# 创建 socket 对象
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(5)

clients = {}


# 处理客户端连接
def handle_client(client_socket, address):
    print(f"Connection from {address} has been established!")
    client_socket.sendall("Enter your nickname: ".encode("utf-8"))  # 发送昵称要求
    nickname = client_socket.recv(1024).decode("utf-8")
    clients[client_socket] = nickname
    broadcast_message(f"{nickname} 进入聊天室")  # 向所有客户端广播新用户进入的消息
    while True:
        try:
            message = client_socket.recv(1024).decode("utf-8")
            if not message:
                break
            print(f"Received message: {message}")
            # 转发消息给所有其他客户端
            for client in clients:
                if client != client_socket:
                    client.sendall((nickname + ": " + message).encode("utf-8"))
        except Exception as e:
            print(f"Error: {e}")
            break

    del clients[client_socket]
    broadcast_message(f"{nickname} 退出聊天室")  # 向所有客户端广播用户离开的消息
    client_socket.close()


# 广播消息给所有客户端
def broadcast_message(message):
    for client in clients:
        client.sendall(message.encode("utf-8"))


# 接受新的连接请求
while True:
    client_socket, address = server_socket.accept()
    client_thread = threading.Thread(target=handle_client, args=(client_socket, address))
    client_thread.start()
