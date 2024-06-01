#include <IRremote.h>
#include <Servo.h>

#define IR_PIN 10 // 红外接收器连接到Arduino的引脚
#define SERVO_PIN 9 // 舵机连接到Arduino的引脚

#define SERVO_MAX_ANGLE 180 // 舵机最大角度
#define SERVO_MIN_ANGLE 0 // 舵机最小角度

IRrecv irrecv(IR_PIN);
decode_results results;

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // 启用红外接收器
  servoMotor.attach(SERVO_PIN); // 将舵机连接到对应引脚
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); // 输出接收到的红外信号值（16进制）
    switch(results.value) {
      case 0xFFA25D: // CH-键对应的红外信号值
        servoMotor.write(SERVO_MAX_ANGLE); // 转动舵机到最大角度位置
        delay(500); // 等待500毫秒
        break;
      case 0xFFE21D: // CH+键对应的红外信号值
        servoMotor.write(SERVO_MIN_ANGLE); // 转动舵机到最小角度位置
        delay(500); // 等待500毫秒
        break;
    }
    irrecv.resume(); // 继续接收下一个红外信号
  }
}
