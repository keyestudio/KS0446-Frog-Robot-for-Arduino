#include <Servo.h>

Servo servo_4;    //实例化舵机

void setup(){
  servo_4.attach(4);     //将舵机信号线（黄线）连接到数字引脚4
}

void loop(){
  for (int i = 0; i <= 180; i = i + (1)) {   //设置变量i来存储舵机位置,从0度到180度，步长为1
    servo_4.write(i);    //告诉舵机转到变量i的位置
    delay(200);         //等待200ms舵机转到变量i的位置
  }
  for (int i = 180; i >= 0; i = i + (-1)) {     //设置变量i来存储舵机位置,从180度到0度，步长为1
    servo_4.write(i);     //告诉舵机转到变量i的位置
    delay(200);          //等待200ms舵机转到变量i的位置
  }

}
