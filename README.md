# chat_room
关于聊天室的跨网段问题，本代码采用云服务器中转消息方法实现跨网段交流

# 核心思想

## 中转
客户端发消息给云服务器,云服务器将消息发送给连接上服务器的所有客户。当用户进入聊天室时，服务器会要求客户输入昵称,当昵称输入完毕后会向所有用户发送XXX进入聊天室。退出聊天室同样。

# 为什么写聊天室？
这并不是想写一个聊天软件。这是为了解决单片机跨网段通讯的问题。如果手机上运行一个客户端代码，在远端树莓派也运行一个客户端，手机端就可以给树莓派发送消息以便控制树莓派。
