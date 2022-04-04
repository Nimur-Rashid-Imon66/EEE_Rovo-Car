#include<LiquidCrystal.h>
#include<AFMotor.h>
#include <Servo.h>



int fontright = 8;
int backright= 7;
int fontleft = 6;
int backleft  = 5;
int servo_pin = 9;
int trig = 13;
int ECHO = 12;
int Enable = 2;
int if_car_stop = 0;
LiquidCrystal lcd(A5,A4,A3,A2,A1,A0); //lcd(RS,E,D4,D5,D6,D7) kon pin kontate connet ace oitar jonno
Servo myServo;

void setup() 
{
  lcd.begin(16,2);

  pinMode(2,OUTPUT); //Enable
  pinMode(5,OUTPUT); //backleft
  pinMode(6,OUTPUT); //fontleft
  pinMode(7,OUTPUT); //backright
  pinMode(8,OUTPUT); //fontright
  pinMode(9,OUTPUT); //servopin
  pinMode(12,INPUT); //Echo
  pinMode(13,OUTPUT); //trigger

  myServo.attach(servo_pin);
 
  lcd.setCursor(0,0);
  lcd.print("Bismillah");
  delay(1000);
  lcd.clear();
  myServo.write(90);
  digitalWrite(Enable,HIGH);
  
}

void loop() 
{
  float dis = distance_cm();
  if(dis>=30)
  {
    lcd.print("Moving Forward");
    delay(10);
    Move_forward();
    lcd.clear();
  }
  else
  {
      Stop();
      if(!if_car_stop) Move_back();
      //left distance
      myServo.write(180);
      float dis_left = distance_cm();
      delay(500);
      
      //right distance
      myServo.write(0);
      float dis_right = distance_cm();
      delay(500);
       
      if(dis_right>=30)
      {
        Turn_right();
      }
      else if(dis_left>=30)
      {
         Turn_left();
      }
      else
      {
        Stop();
        if_car_stop = 1;
      }
      myServo.write(90);
  }
}

float distance_cm() //Ultrasonic sensor
{
  digitalWrite(trig,LOW);
  delay(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  float T = pulseIn(ECHO,HIGH);//time echo ekabar high howar por koto time por low hoise tar duration
  float dis = T * 0.034 ;//(0.034cm is 1 sec e otikkranto durutto)
  dis = dis / 2;
  return dis;
}

/*
   MOTOR DIRECTION
   0 0 = OFF
   1 1 = OFF
   0 1 = FORWARD
   1 0 = BACKWARD
*/

void Move_forward()
{
  //Move Forward 
    digitalWrite(fontleft,LOW); 
    digitalWrite(backleft,HIGH); 
    digitalWrite(fontright,LOW);
    digitalWrite(backright,HIGH);
}
void Move_back()
{
  //Move Back
  lcd.print("Moving Backward");
  digitalWrite(fontleft,HIGH); 
  digitalWrite(backleft,LOW); 
  digitalWrite(fontright,HIGH);
  digitalWrite(backright,LOW);
  delay(2000);
  lcd.clear();
}
void Turn_right()
{
   //TURN RIGHT
  lcd.print("Turning Right");
  digitalWrite(fontleft,LOW); 
  digitalWrite(backleft,HIGH); 
  digitalWrite(fontright,LOW);
  digitalWrite(backright,LOW);
  delay(2000);
  lcd.clear();
}
void Turn_left()
{
  //TURN LEFT
  lcd.print("Turning Left");
  digitalWrite(fontleft,LOW); //  fontleft.run();
  digitalWrite(backleft,LOW); //  backleft.run();
  digitalWrite(fontright,LOW);//  fontright.run();
  digitalWrite(backright,HIGH);//  backright.run();
  delay(2000);
  lcd.clear();
}
void Stop()
{
      //stop
      digitalWrite(fontleft,LOW); //  fontleft.run(RELEASE);
      digitalWrite(backleft,LOW); //  backleft.run(RELEASE);
      digitalWrite(fontright,LOW);//  fontright.run(RELEASE);
      digitalWrite(backright,LOW);//  backright.run(RELEASE);
      lcd.clear();
      lcd.print("Car Stoped");
      delay(200);
      lcd.clear();
      lcd.clear();
}
