#include <ModbusMaster.h>   //modbusmaster库
uint8_t result;     
uint16_t MotorSpeed = 0;//initial speedValue
uint8_t t=1;  
ModbusMaster node;// instantiate ModbusMaster object
uint16_t receivedValue = 0;
uint16_t receiveddis = 0;
bool isFirstInput = true;
bool speedSet = false;
//主程序主体开机运行首先进入模式选择，a为阿克曼转向模式，b为原地转向模式，c为平移模式。

// 将控制小车的代码与nRF24L01+库整合
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // 使用9和10引脚连接nRF24L01+模块
const byte address[6] = "00001"; // 设置通信地址

// 小车控制代码
void setup() {
  // 初始化nRF24L01+模块
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  // 初始化小车控制引脚
  pinMode(/* 设置小车控制引脚 */);
}

void loop() {
  if (radio.available()) {
    char receivedCommand;
    radio.read(&receivedCommand, sizeof(receivedCommand));

    // 根据接收到的指令控制小车
    if (receivedCommand == 'w') {
      // 前进的代码
    } else if (receivedCommand == 's') {
      // 后退的代码
    } else if (receivedCommand == 'a') {
      // 左转的代码
    } else if (receivedCommand == 'd') {
      // 右转的代码
    }
  }
}

