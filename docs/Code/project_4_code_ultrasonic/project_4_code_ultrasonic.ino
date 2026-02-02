float checkdistance() {  //测距函数
  // 产生一个10us的高脉冲去触发TrigPin
  digitalWrite(6, LOW);  //设置引脚6的输出电压为低电平
  delayMicroseconds(2);  //延迟2微秒
  digitalWrite(6, HIGH);  //设置引脚6的输出电压为高电平
  delayMicroseconds(10);  //延迟10微秒
  digitalWrite(6, LOW);   //设置引脚6的输出电压为低电平
  // 检测脉冲宽度，并计算出距离
  float distance = pulseIn(7, HIGH) / 58.00;   // 读取引脚7上的高电平脉冲，最大脉冲时间除以58.00，并且把结果以浮动值形式赋值给distance变量
  delay(10);  // 延迟10毫秒
  return distance;  //返回距离值
}

void setup(){
  Serial.begin(9600);  //打开串行端口，将数据传输速率设置为9600bps
  pinMode(6, OUTPUT);  //将数字引脚6初始化为输出模式，接超声波传感器的Trig
  pinMode(7, INPUT);   //将数字引脚7初始化为输入模式，接超声波传感器的Echo
  Serial.begin(9600);  
}

void loop(){
  Serial.println(checkdistance());  //通过串口换行输出checkdistance()值
  delay(200);  //延迟200毫秒

}
