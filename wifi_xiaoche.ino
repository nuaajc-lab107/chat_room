#include <ESP8266WiFi.h>

const char* ssid = "lab107_international";
const char* password = "lab107lab107";
const char* serverIP = "1.14.63.108";
const int serverPort = 5080;
const int IN1 = D4;  // GPIO5, IN1, 左前进 
const int IN2 = D3;  // GPIO4, IN2, 左后退 
const int IN3 = D2;  // GPIO2, IN3, 右前进 
const int IN4 = D1;  // GPIO0, IN4, 右后退 

WiFiClient client;
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
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void setup() 
{
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

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

void sendToServer(const char* message) 
{
  // Send the message to the server
  client.print(message);
  Serial.println("Message sent to server");
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
      // Resend "你好" to the server
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
