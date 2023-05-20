#define STOP      0 //停止
#define RUN       1 //前进
#define BACK      2 //后退
#define LEFT      3 //左转
#define RIGHT     4 //右转
int a1 = 6;//左电机1
int a2 = 7;//左电机2
int b1 = 4;//右电机1
int b2 = 5;//右电机2
int sensor1 = 8; //从车头方向的最右边开始排序 探测器
int sensor2 = 9; 
int leftPWM = 2;//L298N使能端左
int rightPWM = 3с;//L298N使能端右
void setup()
{
  Serial.begin(9600);//电机控制引脚初始化
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  pinMode(sensor1, INPUT);//寻迹模块引脚初始化
  pinMode(sensor2, INPUT);
}
void loop() 
{
  tracing();       
}
void Work(int c,int value)
{
  analogWrite(leftPWM, value);  //设置PWM输出，设置速度
  analogWrite(rightPWM, value);
  switch(c)
  {
     case RUN:
      Serial.println("RUN"); //前进输出状态
      digitalWrite(a1, HIGH);
      digitalWrite(a2, LOW);
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      break;
     case BACK:
      Serial.println("BACK"); //后退输出状态
      digitalWrite(a1, LOW);
      digitalWrite(a2, HIGH);
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      break;
     case LEFT:
      Serial.println("LEFT"); //左转输出状态
      digitalWrite(a1, HIGH);
      digitalWrite(a2, LOW);
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      break;
     case RIGHT:
      Serial.println("RIGHT"); //右转弯输出状态
      digitalWrite(a1, LOW);
      digitalWrite(a2, HIGH);
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      break;
     default:
      Serial.println("STOP"); //停止输出状态
      digitalWrite(a1, LOW);
      digitalWrite(a2, LOW);
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
  }
}
void tracing()
{
  int d[2];
  d[0] = digitalRead(3);
  d[1] = digitalRead(2);
  if(!d[0] && !d[1]) //左右都没有检测到黑线
  {
    Work(RUN, 200);
  }
  if(d[0]) //右边检测到黑线
  {
    Work(RIGHT, 150);
  }
  if(d[1]) //左边检测到黑线
  {
    Work(LEFT, 150);
  }
  if(d[0] && d[1]) //左右都检测到黑线是停止
  {
    Work(STOP, 0);
    while(1);
  }
  Serial.print(d[0]);
  Serial.print("---");
  Serial.print(d[1]);
}
