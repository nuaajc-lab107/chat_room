#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // 本程序使用ESP8266WiFiMulti库
WiFiClient client;
ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'
const char* serverIP = "1.14.63.108";
const int serverPort = 5080;
const int IN1 = D4;  // GPIO5, IN1, 左前进 
const int IN2 = D3;  // GPIO4, IN2, 左后退 
const int IN3 = D2;  // GPIO2, IN3, 右前进 
const int IN4 = D1;  // GPIO0, IN4, 右后退 
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void forward(int sleep_time) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(sleep_time);
  // 根据你的设置，可能需要在一定时间后停止电机
  stopMotors();
}

// 实现其他运动函数（后退、左转、右转）类似地
void back(int sleep_time) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(sleep_time);
  // 根据你的设置，可能需要在一定时间后停止电机
  stopMotors();
}
void right(int sleep_time) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(sleep_time);
  // 根据你的设置，可能需要在一定时间后停止电机
  stopMotors();
}
void left(int sleep_time) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(sleep_time);
  // 根据你的设置，可能需要在一定时间后停止电机
  stopMotors();
}
void sendToServer(const char* message) 
{
  // Send the message to the server
  client.print(message);
  Serial.println("Message sent to server");
}
void reconnect() 
{
  // If the connection is lost or has never been connected to the server
  Serial.print("Attempting to reconnect");
  // Reconnect
  while (!client.connected()) 
  {
    Serial.println("Reconnecting to server...");
    if (client.connect(serverIP, serverPort)) 
    {
      Serial.println("Connected to server");
      // Resend "重新上线" to the server
      sendToServer("重新上线");
      break;
    } 
    else 
    {
      Serial.println("Connection failed");
      // Retry after waiting for 5 seconds
      delay(5000);
    }
  }
}
void readFromServer() 
{
  // Read data from the server
  while (client.available()) 
  {
    char receivedChar = client.read();
    Serial.print("Received from server: ");
    Serial.println(receivedChar);

    // Perform actions based on the server's message

    switch (receivedChar)
    {
      case 'w':
      forward(10);
      break;

      case 's':
      back(10);
      break;
      case 'a':
      left(10);
      break;
      case 'd':
      right(10);
      break;
    }
  }
}

void setup() 
{
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Connect to Wi-Fi
  //通过addAp函数存储  WiFi名称       WiFi密码
  wifiMulti.addAP("lab107_international", "lab107lab107");  // 这三条语句通过调用函数addAP来记录3个不同的WiFi网络信息。
  wifiMulti.addAP("MI 9", "2n2032n203"); // 这3个WiFi网络名称分别是taichi-maker, taichi-maker2, taichi-maker3。
  Serial.println("Connecting ...");         // 通过串口监视器输出信息告知用户NodeMCU正在尝试连接WiFi                               
  while (wifiMulti.run() != WL_CONNECTED) 
  {  // 此处的wifiMulti.run()是重点。通过wifiMulti.run()，NodeMCU将会在当前
    delay(1000);                             // 环境中搜索addAP函数所存储的WiFi。如果搜到多个存储的WiFi那么NodeMCU
    Serial.print('.');                       // 将会连接信号最强的那一个WiFi信号。
  }                                           // 一旦连接WiFI成功，wifiMulti.run()将会返回“WL_CONNECTED”。这也是
                                              // 此处while循环判断是否跳出循环的条件。

  // Connect to the server
  if (client.connect(serverIP, serverPort)) 
  {
    Serial.println("Connected to server");
    // Send "你好" to the server
    sendToServer("ESP8266已经上线");
  } 
  else 
  {
    Serial.println("Unable to connect to server");
  }
}

void loop() 
{
  // Check if there is data available from the server
  if (client.available()) 
  {
    readFromServer();
  }

  // If the connection is lost, attempt to reconnect
  if (!client.connected()) 
  {
    reconnect();
  }
}
