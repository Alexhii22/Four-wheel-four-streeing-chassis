#include <ModbusMaster.h>
#include <Arduino_FreeRTOS.h>

ModbusMaster FL1;  // 左前驱动轮实例创建
ModbusMaster FR1;  // 右前驱动轮
ModbusMaster RL1;  // 左后驱动轮
ModbusMaster RR1;  // 右后驱动轮

bool isFirstTime = true;
uint16_t motorspeed = 3000;

// 电机任务
void motorTask(ModbusMaster& motor, int motorNumber) {
  motor.setTransmitBuffer(0, 0);
  vTaskDelay(pdMS_TO_TICKS(10));
  motor.writeMultipleRegisters(0x0303, 1);  // 失能初始化
  vTaskDelay(pdMS_TO_TICKS(10));
  motor.setTransmitBuffer(0, motorspeed);  // 速度初始化
  vTaskDelay(pdMS_TO_TICKS(10));
  motor.writeMultipleRegisters(0x0603, 1);
  vTaskDelay(pdMS_TO_TICKS(10));
  motor.setTransmitBuffer(0, 1);  // 速度写入
  vTaskDelay(pdMS_TO_TICKS(10));
  motor.writeMultipleRegisters(0x0303, 1);  // 使能运转
  vTaskDelay(pdMS_TO_TICKS(10));
}

void motor1Task(void *pvParameters) {
  (void)pvParameters; 
  while (1) {
    if (isFirstTime) {
      motorTask(FL1, 1);
      isFirstTime = false;
    }
    vTaskDelay(pdMS_TO_TICKS(1000));  // 1秒的延迟，根据需要调整
  }
}

void motor2Task(void *pvParameters) {
  (void)pvParameters; 
  while (1) {
    if (isFirstTime) {
      motorTask(FR1, 2);
      isFirstTime = false;
    }
    vTaskDelay(pdMS_TO_TICKS(1000));  // 1秒的延迟，根据需要调整
  }
}

void motor3Task(void *pvParameters) {
  (void)pvParameters; 
  while (1) {
    if (isFirstTime) {
      motorTask(RL1, 1);
      isFirstTime = false;
    }
    vTaskDelay(pdMS_TO_TICKS(1000));  // 1秒的延迟，根据需要调整
  }
}

void motor4Task(void *pvParameters) {
  (void)pvParameters; 
  while (1) {
    if (isFirstTime) {
      motorTask(RR1, 1);
      isFirstTime = false;
    }
    vTaskDelay(pdMS_TO_TICKS(1000));  // 1秒的延迟，根据需要调整
  }
}

void setup() {
  Serial.begin(57600);  // 初始化串口1
  Serial1.begin(57600, SERIAL_8N1);  // 初始化串口1,无校验位
  FL1.begin(1, Serial1);  // 通过串口1与从设备1通讯
  FR1.begin(1, Serial1);
  RL1.begin(1, Serial1);
  RR1.begin(1, Serial1);

  xTaskCreate(motor1Task, "Motor1Task", 1000, NULL, 1, NULL);

}

void loop() {
  
}

