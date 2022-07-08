#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>
#define N_SERVOS 4
//-- First step: Configure the pins where the servos are attached
/*
         ---------------
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         ---------------
            ||     ||
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
#define EEPROM_TRIM false

//调整开始舵机的角度 (注意：这里必须调整)
#define TRIM_RR (-5)  //right02
#define TRIM_RL 5  //left02
#define TRIM_YR (-5)  //right01
#define TRIM_YL 0  //left01

//舵机引脚
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2
#define INTERVALTIME 10.0
Oscillator servo[N_SERVOS];

#include "SR04.h"
#define TRIG_PIN 6    //超声波发送引脚
#define ECHO_PIN 7    //超声波接收引脚
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int i = 0;
int val = 0;

//各函数声明
void goingUp(int tempo);
void drunk (int tempo);
void noGravity(int tempo);
void kickLeft(int tempo);
void kickRight(int tempo);
void run(int steps, int T=500);
void walk(int steps, int T=1000);
void backyard(int steps, int T=3000);
void backyardSlow(int steps, int T=5000);
void turnLeft(int steps, int T=3000);
void turnRight(int steps, int T=3000);
void moonWalkLeft(int steps, int T=1000);
void moonWalkRight(int steps, int T=1000);
void crusaito(int steps, int T=1000);
void swing(int steps, int T=1000);
void upDown(int steps, int T=1000);
void flapping(int steps, int T=1000);
int t=495;
double pause=0;

volatile int distance;  //整数变量，用于存放超声波传感器接收到的距离值
volatile int flag;      //设置整数变量flag

//机器人停止
void Stop()
{
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}

//机器人后退
 void backyard(int steps, int T)
{
  int A[4]= {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

char bluetooth_val;   //字符变量，用于存放蓝牙接收到的值

//机器人左转
 void turnLeft(int steps, int T)
{
  int A[4]= {20, 20, 10, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

//机器人右转
 void turnRight(int steps, int T)
{
  int A[4]= {20, 20, 30, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

//机器人前进
 void walk(int steps, int T)
{
  int A[4]= {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS];
int oldPosition[]={90,90,90,90};

void moveNServos(int time, int  newPosition[]){
  for(int i=0;i<N_SERVOS;i++) increment[i] = ((newPosition[i])-oldPosition[i])/(time/INTERVALTIME);
  final_time =  millis() + time;
  iteration = 1;
  while(millis() < final_time){ //Javi del futuro cambia esto
      interval_time = millis()+INTERVALTIME;
      oneTime=0;
      while(millis()<interval_time){
          if(oneTime<1){
              for(int i=0;i<N_SERVOS;i++){
                  servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
              }
              iteration++;
              oneTime++;
          }
      }
  }

  for(int i=0;i<N_SERVOS;i++){
    oldPosition[i] = newPosition[i];
  }
}

float checkdistance() {    //测距函数
  // 产生一个10us的高脉冲去触发TrigPin
  digitalWrite(6, LOW);    //设置引脚6的输出电压为低电平
  delayMicroseconds(2);    //延迟2微秒
  digitalWrite(6, HIGH);   //设置引脚6的输出电压为高电平
  delayMicroseconds(10);   //延迟10微秒
  digitalWrite(6, LOW);    //设置引脚6的输出电压为低电平
  // 检测脉冲宽度，并计算出距离
  float distance = pulseIn(7, HIGH) / 58.00;  // 读取引脚7上的高电平脉冲，最大脉冲时间除以58.00，并且把结果以浮动值形式赋值给distance变量
  delay(10);  // 延迟10毫秒
  return distance;  //返回距离值
}

//机器人滑步
void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {- 15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

//机器人跳舞
void dance() {
  flag = 1;              //变量flag=1         
  while (flag == 1) {    //当变量flag=1时
    goingUp(2*t);        //以2*t的速度慢慢踮起脚
    for (int i = 0; i <= 2; i = i + (1)) { //设置变量i来存储摩擦次数,从0到2，步长为1
      segunda1();  // 机器人摩擦摩擦
    }
    for (int i = 0; i <= 2; i = i + (1)) {  //设置变量i来存储跳动次数,从0到2，步长为1
      jump();  // 机器人跳动
    }
    walk(3,2*t);      //以2*t的速度前进3步
    backyard(3,2*t);  //以2*t的速度后退3步
    crusaito(1,5*t);  //以5*t是速度滑步1步
    crusaito(1,1*t);  //以1*t的速度滑步1步
    crusaito(1,3*t);  //以3*t的速度滑步1步
    for (int i = 0; i <= 2; i = i + (1)) {  //设置变量i来存储摆动次数,从0到2，步长为1
      drunk(4*t);  //以4*t的速度摆动
    }
    moonLEFT(5,2*t);   //以2*t的速度走左太空步5步
    noGravity(2*t);    //以2*t的速度执行失重状态
    swing(5,2*t);      //以2*t速度游泳姿势5步
    moonRight(5,2*t);  //以2*t的速度走右太空步5步
    Stop();            //停止
    kickLeft(t);       //左快步
    for (int i = 0; i <= 2; i = i + (1)) {  //设置变量i来存储跳动次数,从0到2，步长为1
      jump();      //跳动
    } 
    Stop();        //停止
    kickRight(t);  //右快步
    for (int i = 0; i <= 2; i = i + (1)) {  //设置变量i来存储跳动次数,从0到2，步长为1
      jump();  //跳动
    }
    Stop();   //停止
    flag = 0;  //变量flag=0
    bluetooth_val = 'S';  //变量bluetooth_val的值为‘S’
  }
}

//机器人摆动
void drunk (int tempo){
  pause=millis();
  int move1[] = {60,70,90,90};
  int move2[] = {110,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {110,120,90,90};
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  while(millis()<(pause+tempo));
}

//机器人跟随
void follow() {
  flag = 1;              //变量flag=1
  while (flag == 1) {    //当变量flag=1时
    distance = checkdistance();  //将checkdistance()值赋给于变量distance
    if (distance > 20 && distance < 60) {  //如果条件distance > 20且distance < 60成立时
      walk(1,2*t);  //以2*t的速度前进1步

    } else if (distance > 10 && distance < 20) {  //否则如果条件distance > 10且distance <= 20成立时
      Stop();     //停止
    } else if (distance <= 10) {  //否则如果条件distance <= 10 成立时
      backyard(1,2*t);  //以2*t的速度后退1步
    } else {    //否则以上条件都未成立时
      Stop();   //停止

    }
    if (Serial.available())  //判断串口缓存区是否有数据
    {
      bluetooth_val = Serial.read();  //读取串口缓存区的数据
      if (bluetooth_val == 'S') {  //如果变量bluetooth_val的值为‘S’
        flag = 0;  //变量flag = 0

      }
    }
  }
}

//机器人慢慢踮起脚
void goingUp(int tempo){
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      delay(tempo);
      servo[0].SetPosition(80);
      servo[1].SetPosition(100);
      delay(tempo);
      servo[0].SetPosition(70);
      servo[1].SetPosition(110);
      delay(tempo);
      servo[0].SetPosition(60);
      servo[1].SetPosition(120);
      delay(tempo);
      servo[0].SetPosition(50);
      servo[1].SetPosition(130);
      delay(tempo);
      while(millis()<pause+8*t);
}

//机器人跳动
void jump()
{
int move5[4] = {70,110,80,100};
  int move6[4] = {70,110,100,80};
  int move7[4] = {90,90,80,100};
  int move8[4] = {90,90,100,80};
pause=millis();
    moveNServos(t*0.15,move5);
    moveNServos(t*0.15,move6);
    moveNServos(t*0.15,move7);
    moveNServos(t*0.15,move8);
    while(millis()<(pause+t));
  }
  
//机器人左快步
void kickLeft(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
}

//机器人右快步
void kickRight(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

//机器人左太空步
 void moonLEFT(int steps, int T)
{
  int A[4]= {25, 25, 0, 0};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

//机器人右太空步
 void moonRight(int steps, int T)
{
  int A[4]= {25, 25, 0, 0};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

//机器人失重状态
void noGravity(int tempo){
  int move1[4] = {120,140,90,90};
  int move2[4] = {140,140,90,90};
  int move3[4] = {120,140,90,90};
  int move4[4] = {90,90,90,90};
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  for(int i=0;i<N_SERVOS;i++) oldPosition[i]=90;
  moveNServos(tempo*2,move1);
  moveNServos(tempo*2,move2);
  delay(tempo*2);
  moveNServos(tempo*2,move3);
  moveNServos(tempo*2,move4);
}

//机器人在地上摩擦摩擦 
void segunda1()
{
int move1[4] = {90,90,80,100};
  int move2[4] = {90,90,100,80};
  int move3[4] = {90,90,80,100};
  int move4[4] = {90,90,100,80};
     pause=millis();
      moveNServos(t*0.15,move1);
      moveNServos(t*0.15,move2);
      moveNServos(t*0.15,move3);
      moveNServos(t*0.15,move4);
      while(millis()<(pause+t));
    }

//机器人游泳姿势
void swing(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void setup(){
  distance = 0;
  flag = 0;
  Serial.begin(9600);
  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);
  int trim;
  if(EEPROM_TRIM){
    for(int x=0;x<4;x++){
      trim=EEPROM.read(x);
      if(trim>128)trim=trim-256;
      Serial.print("TRIM ");
      Serial.print(x);
      Serial.print(" en ");
      Serial.println(trim);
      servo[x].SetTrim(trim);
    }
  }
  else{
    servo[0].SetTrim(TRIM_RR);
    servo[1].SetTrim(TRIM_RL);
    servo[2].SetTrim(TRIM_YR);
    servo[3].SetTrim(TRIM_YL);
  }
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  Serial.begin(9600);
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
}

void loop(){
  if (Serial.available())  //判断串口缓存区是否有数据
  {
    bluetooth_val = Serial.read();  //读取串口缓存区的数据
    Serial.println(bluetooth_val);  //打印出来
  }
  switch (bluetooth_val) {  //变量bluetooth_val的值与各个case逐个进行比较
   case 'F':    //当变量bluetooth_val的值是'F'时
    walk(1,2*t);  //以2*t的速度前进1步
    break;       //退出switch-case语句体
   case 'B':  //当变量bluetooth_val的值是'B'时
    backyard(1,2*t);  //以2*t的速度后退1步
    break;    
   case 'L':  //当变量bluetooth_val的值是'L'时
    turnLeft(1,2*t);  //以2*t的速度左转1步
    break;  
   case 'R':  //当变量bluetooth_val的值是'R'时
    turnRight(1,2*t);  //以2*t的速度右转1步
    break;  
   case 'S':  //当变量bluetooth_val的值是'S'时
    Stop();  //停止
    break;
   case '1':  //当变量bluetooth_val的值是'1'时
    moonLEFT(1,2*t);  //以2*t的速度走左太空步1步
    break;
   case '2':  //当变量bluetooth_val的值是'2'时
    moonRight(1,2*t);  //以2*t的速度走右太空步1步
    break;
   case '3':   //当变量bluetooth_val的值是'3'时
    kickRight(t);  //右快步
    break;
   case '4':  //当变量bluetooth_val的值是'4'时
    kickLeft(t);  //左快步
    break;
   case '6':  //当变量bluetooth_val的值是'6'时
    noGravity(2*t);  //以2*t的速度失重状态中
    break;
   case '7':    //当变量bluetooth_val的值是'7'时
    crusaito(1,5*t);  //以5*t的速度滑步1步
    crusaito(1,1*t);  //以1*t的速度滑步1步
    crusaito(1,3*t);  //以3*t的速度滑步1步
    break;
   case '8':  //当变量bluetooth_val的值是'8'时
    segunda1();  // 机器人摩擦摩擦
    break;
   case 'G':  //当变量bluetooth_val的值是'G'时
    drunk(4*t);  //以4*t的速度摆动
    break;
   case '9':  //当变量bluetooth_val的值是'9'时
    jump();  //跳动
    break;
   case 'H':  //当变量bluetooth_val的值是'H'时
    swing(1,2*t);  //以2*t的速度走游泳姿势1步
    break;
   case 'J':  //当变量bluetooth_val的值是'J'时
    goingUp(2*t);  //以2*t的速度慢慢踮起脚
    break;
   case 'P':  //当变量bluetooth_val的值是'P'时
    dance();  //机器人跳舞
    break;
   case 'U':  //当变量bluetooth_val的值是'U'时
    follow();  //机器人跟随
    break;  
  }

}
