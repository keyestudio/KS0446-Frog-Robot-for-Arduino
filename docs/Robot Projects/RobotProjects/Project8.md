## Project 8: Bluetooth Control

![](media/image-20230413134448491.png)

We are now ready to give the frog robot capability -- Bluetooth remote control!

For a smart robot, there should be a control terminal and a controlled terminal.

In the course, we use the mobile phone as the console (host), and the HM-10 Bluetooth module (slave) connected to the robot as the controlled terminal.

When using, we need to install an APP on the phone, and connect the HM-10 Bluetooth module, then we tap the buttons on the Bluetooth APP to navigate the multiple style movement of robot.

![](media/image-20230413134457498.png)

HM-10 Bluetooth Module

![](media/7eae5f117b0a233315d747d51ff658d1.png)

**Description**

Bluetooth technology is a wireless standard technology that enables short-distance data exchange between fixed devices, mobile devices, and building personal area networks (using UHF radio waves in the ISM band of 2.4 to 2.485
GHz).

The robot kit is equipped with the Keyestudio HM-10 Bluetooth-4.0 V3 module, which is a master-slave machine. When use as the Host, it can send commands to the slave actively; when use as the Slave, it can only receive commands from the host.

The HM-10 Bluetooth module supports the Bluetooth 4.0 protocol, which not only supports Android mobile, but also supports iOS system.

**Technical Details**

1.  Bluetooth protocol: Bluetooth Specification V4.0 BLE

2.  No byte limit in serial port Transceiving

3.  In open environment, realize 100m ultra-distance communication with iphone4s

4.  USB protocol: USB V2.0

5.  Working frequency: 2.4GHz ISM band

6.  Modulation method: GFSK(Gaussian Frequency Shift Keying)

7.  Transmission power: -23dbm, -6dbm, 0dbm, 6dbm, can be modified by AT command.

8.  Sensitivity: ≤-84dBm at 0.1% BER

9.  Transmission rate: Asynchronous: 6K bytes ; Synchronous: 6k Bytes

10.  Security feature: Authentication and encryption

11.  Supporting service: Central & Peripheral UUID FFE0, FFE1

12.  Power consumption: Auto sleep mode, stand by current 400uA\~800uA, 8.5mA during transmission.

13.  Power supply: 5V DC

14.  Working temperature: –5 to +65 Centigrade

**Pins Description**

![](media/995696dcbc16f527a6ed619757fa792e.png)

| **Pins**  | **Description**                                              |
| :-------: | ------------------------------------------------------------ |
|  **BRK**  | Input pin; short press for control, or input a low-level single pulse of about 1000ms, you can implement the following features: In sleep state: The module will be woken up to normal status. If AT+NOTI is turned on, the serial port will receive OK+WAKE In connected state: The module will initiate a disconnect request In standby state: The module will return to the factory default state. |
|  **RXD**  | Serial data input                                            |
|  **TXD**  | Serial data output                                           |
|  **GND**  | ground                                                       |
|  **VCC**  | Power positive input 5V                                      |
| **STATE** | Output pin Indicates the working states: Slow flash in standby mode - repeat 500ms pulse; Long bright in connection state - high level. You can also set it to no flashing in the standby state, and long bright in the connection state. |

In the experiment, we default use the HM-10 Bluetooth module as a Slave and the cellphone Bluetooth as a Host.

We install the Bluetooth APP on the mobile phone, connecting the Bluetooth module; finally use the Bluetooth APP to control the robot move, displaying the control character of each key on the serial monitor.

Using Bluetooth APP

**For Android system:**

Click the Frog_Otto compression package to direct install the Frog_Otto APP; installed well, appear the icon below on your mobile phone:

![](media/397d9bbd5521ee509e69d6a87ab9150c.jpeg)

Download the Frog_Otto package from the link below:

<https://drive.google.com/open?id=1pymZOlVBVBWJ4s-1buKP3q5T1uM_b-tj>

Or you can download the keyestudio Frog_Otto APP direct from the Google Play:

<https://play.google.com/store/apps/details?id=com.keyestudio.frogotto>

![](media/67f411feb459f8be4b79cc4e52ab0aa0.png)

Tap the Frog_Otto icon to enter the Bluetooth APP. As shown below.

![](media/bda41b60dd076825032d18264270f6b8.png)

Done uploading the code to control board, connect the Bluetooth module, the LED on the Bluetooth module will flash.

Then tap the option CONNECT on the APP, searching the Bluetooth.

![](media/6b9596a31d5f44ba6a563cba447a78ab.png)

Click to connect the Bluetooth. HMSoft connected, Bluetooth LED will turn on normally.

![](media/6ca7165b9667331ecd1c313d3871cd87.png)

**For iOS system:**

Open the APP store

![](media/eeccf6fd30106842b44464a3dc598f0c.png)

Click to search the APP - Frog Otto

![](media/ef5c55343d214c9b6be0e7147fb43b54.png)

Tap to open the Frog Otto

![](media/43c9b8665ff7498dcf8fe90c506430c2.png)

Done uploading the code, connect the Bluetooth module, the LED on the Bluetooth module will flash. To open Bluetooth, click the “Connect” on the APP upper left corner, searching and connecting Bluetooth.

![](media/71f79c7e082ef783460a88411c902203.png)

![](media/6b9596a31d5f44ba6a563cba447a78ab.png)

Click to connect the Bluetooth. HMSoft connected, Bluetooth LED will turn on normally.

![](media/6ca7165b9667331ecd1c313d3871cd87.png)

Bluetooth Test

**Wiring**

Stack the Nano ch340 on the Nano shield and plug in the Bluetooth module to pin TX, RX, GND, 5V.

![](media/b3f4dd7689185cafc91faa4d2ecdac90.png)

**Code**

Downloaded the APP, and connected well the Bluetooth module and power supply, we need to write the program code to know what signal the Bluetooth module sent.

```c
char bluetooth_val; //Character variable, used to store the value received byBluetooth

void setup(){
	Serial.begin(9600); //open the serial port, set the data transmission speed to 9600bps
}

void loop(){

	if (Serial.available()) //Determine whether there is data in the serial portbuffer
	{

        bluetooth_val = Serial.read(); //Read data from serial port buffer
        Serial.println(bluetooth_val); //print out
	}
}
```

**Result**

1.  Upload the code to keyestudio nano ch340 success;

2.  Stack keyestudio nano ch340 onto Nano Shield;

3.  Connect Keyestudio nano ch340 to computer with a mini USB cable.

4.  Install well the Bluetooth APP;

5.  Powered on, press down the Power_Switch on Nano Shield. The indicator on Bluetooth module flashes. So you can open mobile Bluetooth APP to connect the Bluetooth module;

6.  Once Bluetooth connected, open the serial monitor and set the baud rate to 9600.

7.  Aimed at the Bluetooth module, tap the key on the Bluetooth APP, we can see the control character of each key. As the figure shown below.

![](media/ce9d3b7ef40230c2e98e30ad3c72959c.png)

## Bluetooth Control Robot

**Circuit Design:**

We can combine the control character of each key on APP and extend to control the angle of 4 servos, so as to make the robot move.

The Bluetooth APP interface is shown below:

![](media/bda41b60dd076825032d18264270f6b8.png)

| Butt                                                         | Control character                             | Function                                                     |
| ------------------------------------------------------------ | --------------------------------------------- | ------------------------------------------------------------ |
| ![image-20230510180058985](media/image-20230510180058985.png) |                                               | pair and connect HM-10 Bluetooth module                      |
| ![image-20230510180107260](media/image-20230510180107260.png) |                                               | enter Bluetooth control interface                            |
| ![image-20230510180114040](media/image-20230510180114040.png) |                                               | disconnect the Bluetooth                                     |
| ![img](media/image-20230413132829074.png)                    | Press: F<br />Release: S                      | Press the button, robot goes front; release to stop          |
| ![img](media/wps4.jpg)                                       | Press: B <br />Release: S                     | Press the button, robot goes back; release to stop           |
| ![img](media/wps21.jpg)                                      | Press: L<br />Release: S                      | Press the button, robot turns left; release to stop          |
| ![img](media/wps22.jpg)                                      | Press: R<br />Release: S                      | Press the button, robot turns right; release to stop         |
| ![img](media/wps23.jpg)                                      | Press: 1<br />Release: S                      | Press to moonwalk to the left; release to stop               |
| ![img](media/wps24.jpg)                                      | Press: 2<br />Release: S                      | Press to moonwalk to the right; release to stop              |
| ![img](media/wps25.jpg)                                      | Press: 3<br />Release: S                      | Press to galop to the right; release to stop                 |
| ![img](media/wps26.jpg)                                      | Press: 4<br />Release: S                      | Press to galop to the left; release to stop                  |
| ![img](media/wps27.jpg)                                      | Press: 6<br />Release: S                      | Tap to tilt right, then slowly turn back                     |
| ![img](media/wps28.jpg)                                      | Press: 7<br />Release: S                      | Tap for crusaito step once                                   |
| ![img](media/wps29.jpg)                                      | Press: 8<br />Release: S                      | Press to start friction pace; release to stop                |
| ![img](media/wps30.jpg)                                      | Press: G<br />Release: S                      | Press to flapping left and right                             |
| ![img](media/wps31.jpg)                                      | Press: 9<br />Release: S                      | Press to jump; release to stop                               |
| ![img](media/wps32.jpg)                                      | Press: H<br />Release: S                      | Press to start swing motion; release to stop                 |
| ![img](media/wps33.jpg)                                      | Press: J<br />Release: S                      | Tap to slowly going up feet, then going down                 |
| ![img](media/wps34.jpg)                                      | Press: P<br />Release: S                      | Tap to dance                                                 |
| ![img](media/wps35.jpg)                                      | Tap once to send: UTap <br />again to send: S | Start ultrasonic avoiding function                           |
| ![img](media/wps36.jpg)                                      | /                                             | Tap once to start the mobile gesture control; tap again to close |



Based on the circuit design, we can start building Bluetooth remote control robot. Follow the wiring diagram and test code below.

**Hookup Guide:**

Stack the Nano ch340 on the Nano shield and plug in the Bluetooth module to pin TX, RX, GND, 5V. (RXD to TX, TXD to RX, GND to GND, VCC to 5V)

Connect 4 servo motors to digital pin5,4,3,2 separately.

![](media/image-20230413134615864.png)

**Coding:**

```c
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

//adjust the initial angles of servos
#define TRIM_RR (-5)  //right02
#define TRIM_RL 5  //left02
#define TRIM_YR (-5)  //right01
#define TRIM_YL 0  //left01

//pins of the servo
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2
#define INTERVALTIME 10.0
Oscillator servo[N_SERVOS];

#include "SR04.h"
#define TRIG_PIN 6  //sending pins of the ultrasonic sensor
#define ECHO_PIN 7  //sending pins of the ultrasonic sensor
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int i = 0;
int val = 0;

//each function declaration
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

//stop
void Stop()
{
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}

//go back
 void backyard(int steps, int T)
{
  int A[4]= {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

char bluetooth_val;   //Character variable, used to store the value received by Bluetooth

//turn left
 void turnLeft(int steps, int T)
{
  int A[4]= {20, 20, 10, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

//turn right
 void turnRight(int steps, int T)
{
  int A[4]= {20, 20, 30, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
  for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

//go forward
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

void setup(){
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
}

void loop(){
  if (Serial.available())  //Determine whether there is data in the serial port buffer
  {
    bluetooth_val = Serial.read();  //Read data from serial port buffer
    Serial.println(bluetooth_val);  //print out
  }
  switch (bluetooth_val) {  //The value of the variable bluetooth_val is compared with each case one by one
   case 'F':                //when the variable bluetooth_val is 'F'
    walk(1,2*t);            //move forward for 1 step in 2*t
    break;                  //exit the switch-case statement
   case 'B':                //when the variable bluetooth_val is 'B'
    backyard(1,2*t);        //go back for 1 step in 2*t
    break;                   
   case 'L':                //when the variable bluetooth_val is 'L'
    turnLeft(1,2*t);        //turn left for 1 step in 2*t
    break;                   
   case 'R':                 //When the value of the variable bluetooth_val is 'R'
    turnRight(1,2*t);        //move to right for 1 step in 2*t 
    break;                  
   case 'S':                //When the value of the variable bluetooth_val is 'S'
    Stop();                 //stop
    break;                   
  }

}
```

**Note:** should upload the code success first, then plug in Bluetooth module. Otherwise, code upload fails.

**Result**

1.  Upload the code to keyestudio nano ch340 success;
2.  Stack keyestudio nano ch340 onto Nano Shield;
3.  Connect Keyestudio nano ch340 to computer with a mini USB cable.
4.  Install well the Bluetooth APP;
5.  Powered on, press down the Power_Switch on Nano Shield. The indicator on Bluetooth module flashes. So you can open mobile Bluetooth APP to connect the Bluetooth module;
6.  Once Bluetooth connected, aim at the Bluetooth module, tap the key on the Bluetooth APP to command the robot.
7.  Tap the key ![](media/image-20230413132829074.png), the frog robot willgo forward; tap![](media/image-20230413132834844.png), go back; tap![](media/image-20230413132840700.png), turn left; tap ![](media/image-20230413132846171.png), turn right; release all the keys, robot stands still.

![](media/image-20230413134634111.png)

