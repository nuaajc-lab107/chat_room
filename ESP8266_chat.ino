#include <ESP8266WiFi.h>

const char* ssid = "lab107_international";
const char* password = "lab107lab107";
const char* serverIP = "1.14.63.108";
const int serverPort = 5080;
const int ledPin = D2; // 这里使用D2，可以根据需要更改

WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // 连接到Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("正在连接到WiFi...");
  }

  Serial.println("已连接到WiFi");

  // 连接到服务器
  if (client.connect(serverIP, serverPort)) {
    Serial.println("已连接到服务器");
    // 发送“你好”到服务器
    sendToServer("你好");
  } else {
    Serial.println("无法连接到服务器");
  }
}

void loop() {
  // 检查是否有数据从服务器接收
  if (client.available() > 0) {
    readFromServer();
  }

  // 如果连接丢失，尝试重新连接
  if (!client.connected()) {
    reconnect();
  }
}

void sendToServer(const char* message) {
  // 将消息发送到服务器
  client.print(message);
  Serial.println("消息已发送到服务器");

}

void readFromServer() {
  // 读取服务器发送的数据
  String serverMessage = client.readStringUntil('\n');
  Serial.print("从服务器接收到: ");
  Serial.println(serverMessage);

  // 根据服务器的消息执行动作
  if (serverMessage == "b") {
    blinkLED();
  }
}

void blinkLED() {
  // 让LED每秒闪烁一次，总计闪烁10次
  for (int i = 0; i < 10; ++i) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}

void reconnect() {
  // 如果我们失去了连接或者从未连接过服务器
  Serial.print("尝试重新连接");
  // 重连
  while (!client.connected()) {
    Serial.println("重新连接到服务器...");
    if (client.connect(serverIP, serverPort)) {
      Serial.println("已连接到服务器");
      // 重新发送“你好”到服务器
      sendToServer("你好");
      break;
    } else {
      Serial.println("连接失败");
      // 等待5秒后重试
      delay(5000);
    }
  }
}
