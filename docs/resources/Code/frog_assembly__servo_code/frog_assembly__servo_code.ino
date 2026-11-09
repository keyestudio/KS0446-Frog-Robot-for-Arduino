#include <Servo.h>

Servo servo_2;  //实例化舵机2
Servo servo_3;  //实例化舵机3
Servo servo_4;  //实例化舵机4
Servo servo_5;  //实例化舵机5

void setup(){
  servo_2.attach(2);  //将舵机2信号线（黄线）连接到数字引脚2
  servo_3.attach(3);  //将舵机3信号线（黄线）连接到数字引脚3
  servo_4.attach(4);  //将舵机4信号线（黄线）连接到数字引脚4
  servo_5.attach(5);  //将舵机5信号线（黄线）连接到数字引脚4
}

void loop(){
  servo_2.write(90);  //设定舵机2的角度是90°
  delay(500);         //延迟500毫秒
  servo_3.write(90);  //设定舵机3的角度是90°
  delay(500);         //延迟500毫秒
  servo_4.write(90);  //设定舵机4的角度是90°
  delay(500);         //延迟500毫秒
  servo_5.write(90);  //设定舵机5的角度是90°
  delay(500);         //延迟500毫秒

}
