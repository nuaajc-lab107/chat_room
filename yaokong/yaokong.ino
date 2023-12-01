#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>// 本程序使用ESP8266WiFiMulti库
WiFiClient client;
ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'
const char* serverIP = "1.14.63.108";
const int serverPort = 5080;
const int D1_PIN = D1;
const int D2_PIN = D2;
const int D3_PIN = D3;
const int D4_PIN = D4;

void sendToServer(const char* message) 
{
  // Send the message to the server
  client.print(message);
  Serial.println("Message sent to server");
}
void setup() {
  Serial.begin(115200);
  wifiMulti.addAP("lab107_international", "lab107lab107");  // 这三条语句通过调用函数addAP来记录3个不同的WiFi网络信息。
  wifiMulti.addAP("MI 9", "2n2032n203");
  wifiMulti.addAP("GT", "ljh180418"); // 这3个WiFi网络名称分别是taichi-maker, taichi-maker2, taichi-maker3。
  Serial.println("Connected to WiFi");
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

  // 设置引脚模式
  pinMode(D1_PIN, INPUT_PULLUP);
  pinMode(D2_PIN, INPUT_PULLUP);
  pinMode(D3_PIN, INPUT_PULLUP);
  pinMode(D4_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(D1_PIN) ==LOW) {
    sendToServer("1");
  } else if (digitalRead(D2_PIN) == LOW) {
    sendToServer("2");
  } else if (digitalRead(D3_PIN) == LOW) {
    sendToServer("3");
  } else if (digitalRead(D4_PIN) == LOW) {
    sendToServer("4");
  }
  delay(100);
}

