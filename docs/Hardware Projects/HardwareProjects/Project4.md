## Project 4: Ultrasonic Detecting Obstacles

Introduction：

The ultrasonic module will emit the ultrasonic waves after trigger signal. When the ultrasonic waves encounter the object and are reflected back, the module outputs an echo signal, so it can determine the distance of object from the time difference between trigger signal and echo signal.

We can use the ultrasonic sensor to detect whether there is an obstacle ahead. It is commonly used to measure the distance between the front obstacle and robot.

In the process of robot DIY, we can use the measured distance by ultrasonic sensor to build functional robots, such as automatic avoiding, following, etc.

In the experiment, we use the ultrasonic sensor to measure the distance between the robot and front obstacle.

The following picture is an ultrasonic module.

![](media/image-20230413103840181.png)

**Specifications:**

-   Operating voltage: DC 5V

-   Operating current: 15mA

-   Operating frequency: 40khz

-   Maximum detection range: 3-5m

-   Minimum detection range: 2cm

-   Induction Angle: less than 15 degrees

-   High accuracy: up to 3mm

**Wiring：**

![](media/image-20230413103906047.png)

Connect the ultrasonic sensor to NANO shield, VCC pin to 5V(V), Trig pin to digital 6 (S), Echo pin to digital 7 (S), GND pin to GND(G); Then stack the NANO CH340 into the NANO shield.

**Test Code:**

```c
float checkdistance() { //distance measuring function

//Generate a 10us high pulse to trigger TrigPin
	digitalWrite(6, LOW); //Set pin 6 output voltage low
	delayMicroseconds(2); //delay in 20ms
	digitalWrite(6, HIGH); //Set pin 6 output voltage high
	delayMicroseconds(10); //delay in 10ms
	digitalWrite(6, LOW); //Set pin 6 output voltage low

	// Detect pulse width and calculate distance
	float distance = pulseIn(7, HIGH) / 58.00; // Read the high pulse on pin 7,divide the maximum pulse time by 58.00, and assign the result to the distancevariable as a floating value 
    delay(10); // delay in 10ms
	return distance; //return the distance value

}

void setup(){
	Serial.begin(9600); //open the serial port, set the data transmission speed to 9600bps
	pinMode(6, OUTPUT); //Initialize digital pin 6 to output mode, connect to Trigof ultrasonic sensor
	pinMode(7, INPUT); //set the digital 7 to output, and connect the Eco of theultrasonic sensor
	Serial.begin(9600);
}

void loop(){
	Serial.println(checkdistance()); //output checkdistance via the serial port()
	delay(200); //delay in 200ms
}
```

**Test Result**:

Upload the code success, press the Power_Switch on NANO shield.

Open the **Monitor** ![](media/affd123b80bcd2cbfc8ffeba35dc1a3c.png) and set **the baud rate to 9600**.

Move your hand or a large, flat object closer and farther away from the ultrasonic sensor. As the object approaches, the monitor will show the distance (unit:cm) being read from the sensor.

![](media/6b2c5c28ce058f3002ada79749781e2e.png)

**Code explanation**:

float distance = pulseIn(7, HIGH) / 58.00

The pulseIn function is actually a simple function to measure the pulse width, and the default unit is us. That is to say, what pulseIn measures is the time elapsed from transmitting to receiving ultrasonic waves. The divisor of 58 is also well understood, and the speed of sound in dry, 20°C air is about 343 m/s, or 34,300 cm/s. Or, let's do a unit conversion, divide 34,300 by 1,000,000 cm/microsecond. That is: 0.0343 cm/microsecond, and another angle, 1/(0.0343 cm/microsecond) is: 29.15 microseconds/cm. This means that every 291.5 microseconds represents a distance of 10CM. 1 cm is 29.15 microseconds. But after sending to receiving the echo, the sound travels twice the distance.

So the actual distance is 1 cm, which corresponds to 58.3 microseconds. In fact, the entire ranging process is the time from when the sound wave is sent to the time when the echo is received. The first distance in your program is actually the time us. So to change the distance in cm, divide it by 58. Of course dividing by 58.3 may be more accurate. So we can get the measured distance with pulseIn(7, HIGH) / 58.00.

**Extension Practice:**

**You can add new texts or distance unit (cm) on the monitor display**

```c
float checkdistance() { //distance measuring function

//Generate a 10us high pulse to trigger TrigPin
    digitalWrite(6, LOW); //Set pin 6 output voltage low
    delayMicroseconds(2); //delay in 20ms
    digitalWrite(6, HIGH); //Set pin 6 output voltage high
    delayMicroseconds(10); //delay in 10ms
    digitalWrite(6, LOW); //Set pin 6 output voltage low

// Detect pulse width and calculate distance
	float distance = pulseIn(7, HIGH) / 58.00; // Read the high-level pulse on pin7, divide the maximum pulse time by 58.00, and assign the result to the distancevariable as a floating value 
    delay(10); // delay in 10ms
	return distance; //return the distance value
}

void setup(){

    Serial.begin(9600); //open the serial port, set the data transmission speed to9600bps
    pinMode(6, OUTPUT); //Initialize digital pin 6 to output mode, connect to Trigof ultrasonic sensor
    pinMode(7, INPUT); //set the digital 7 to output, and connect the Eco of theultrasonic sensor
}

void loop(){

    Serial.print(checkdistance()); //Output checkdistance() value through serial    port without wrapping()
    Serial.println("cm"); //Output string "cm" through serial line wrapping
    delay(200); //delay in 200ms

}
```

**Change the baud rate and delay time to see the result**

```c
float checkdistance() { //distance measuring function

    //Generate a 10us high pulse to trigger TrigPin
    digitalWrite(6, LOW); //Set pin 6 output voltage low
    delayMicroseconds(2); //delay in 20ms
    digitalWrite(6, HIGH); //Set pin 6 output voltage high
    delayMicroseconds(10); //delay in 10ms
    digitalWrite(6, LOW); //Set pin 6 output voltage low

    // Detect pulse width and calculate distance
    float distance = pulseIn(7, HIGH) / 58.00; // Read the high-level pulse on pin7, divide the maximum pulse time by 58.00, and assign the result to the distancevariable as a floating value 
    delay(10); // delay in 10ms
    return distance; //return the distance value
}

void setup(){

    Serial.begin(9600); //open the serial port, set the data transmission speed to9600bps
    pinMode(6, OUTPUT); //Initialize digital pin 6 to output mode, connect to Trigof ultrasonic sensor
    pinMode(7, INPUT); //set the digital 7 to output, and connect the Eco of theultrasonic sensor
    Serial.begin(9600);

}

void loop(){

    Serial.println(checkdistance()); //output checkdistance via the serial port()value
    delay(1000); //Delay in 1000ms

}
```
