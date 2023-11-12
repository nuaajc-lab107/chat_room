void setup() {
  Serial.begin(9600);  // 初始化串口，设置波特率为9600
}

void loop() {
  if (Serial.available()) {  // 检查是否有可用数据
    char data = Serial.read();  // 读取单个字节数据
    // 在这里处理接收到的数据
    // 例如，你可以将数据打印到串口监视器上
    Serial.print("Received data: ");
    Serial.println(data);
  }
}
