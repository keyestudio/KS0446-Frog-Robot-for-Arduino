char bluetooth_val;  //字符变量，用于存放蓝牙接收到的值

void setup(){
  Serial.begin(9600);  //打开串行端口，将数据传输速率设置为9600bps
  Serial.begin(9600);
}

void loop(){
  if (Serial.available())  //判断串口缓存区是否有数据
  {
    bluetooth_val = Serial.read();  //读取串口缓存区的数据
    Serial.println(bluetooth_val);  //打印出来
  }

}
