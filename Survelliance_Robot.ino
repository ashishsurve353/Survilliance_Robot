#include<Servo.h>

Servo serv_t;
int angle=0;
int left_sensor_state=0;
int right_sensor_state=0;
char getstr;
long distance;
const int left_sensor_pin =A0;
const int right_sensor_pin =A1;
const int servo=9;
const int trig=3;
const int echo=2;
const int IR=4;
const int LeftMotorForward = 5;
const int LeftMotorBackward = 6;
const int RightMotorForward = 10;
const int RightMotorBackward = 11;

void _mForward()
{ 
  
     digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    Serial.println("go forward!");
}
void _mBack()
{
  
    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);
  
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorForward, LOW);
    Serial.println("go back!");
}
void _mleft()
{
  
    digitalWrite(LeftMotorBackward, LOW); // did change to move only ryt motor forward
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  
    Serial.println("go left!");
}
void _mright()
{
  
     digitalWrite(LeftMotorForward, HIGH);
     digitalWrite(RightMotorBackward, LOW); // did change to move only left motor forward
  
     digitalWrite(LeftMotorBackward, LOW);
     digitalWrite(RightMotorForward, LOW);
  
  
}
void _mStop()
{
     digitalWrite(RightMotorForward, LOW);
     digitalWrite(LeftMotorForward, LOW);
     digitalWrite(RightMotorBackward, LOW);
     digitalWrite(LeftMotorBackward, LOW);
     Serial.println("Stop!");
}
int Distance(){
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);  //sending 8 pulse at 40KHz
    digitalWrite(trig,LOW);
    long duration=pulseIn(echo,HIGH);//wait until echo become high give time in microseconds
    int cm = duration*0.034/2;
  
     return cm;
}
void setup()
{ 
  
  Serial.begin(9600);
  serv_t.attach(servo);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(IR,INPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
 
}
void loop()
  { 
      serv_t.write(90);//   Servo in front
      distance = Distance();
      delay(100);
  if (distance <= 20){
      _mStop();
      delay(300);
      serv_t.write(1);  //Servo at left
      distance=Distance();
      serv_t.write(179); //Servo at Right
      long distance2=Distance();
  if(distance <= 20&&distance2>20)
      {
      _mright();
      delay(200);
      }
   else if(distance > 20&&distance2<=20)
    {
      _mleft();
      delay(200);
    }
   else{
     _mStop();
    }
    
  }

     else{ 
     getstr=Serial.read();
 if(getstr=='F')
  {
     _mForward();
  }
  else if(getstr=='B')
  {
      _mBack();
       delay(200);
  }
  else if(getstr=='R')
  {
       _mright();
       delay(200);
  }
  else if(getstr=='L') 
  {
     _mleft();
   
      delay(200);
  }
  else if(getstr=='X')
  {
     _mStop();     
  }
   }
    left_sensor_state = analogRead(left_sensor_pin);
    right_sensor_state = analogRead(right_sensor_pin);

if(right_sensor_state > 500 && left_sensor_state < 500)
{
    Serial.println("turning right");
    _mright();
    delay(10); 
  }
if(right_sensor_state < 500 && left_sensor_state > 500)
{
    Serial.println("turning left");
  
     _mleft();
      delay(10);
  }

if(right_sensor_state > 500 && left_sensor_state > 500)
{
    Serial.println("going forward");

    _mForward();

    delay(10);
  
  }

if(right_sensor_state < 500 && left_sensor_state < 500)
{ 
    Serial.println("stop");
  
    _mStop();
  
  }


}

