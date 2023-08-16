#include<Servo.h>
Servo servo1;
int pos;

int IRSensor = 4; // connect ir sensor to arduino pin 2
int LED = 13; // connect Led to arduino pin 13
int led2=12;
int moisture = A4;

const int trigPinR = 47;
const int echoPinR = 45;
const int trigPinG = 33;
const int echoPinG = 35;
const int led_green = 10;
const int led_red = 9;
const int buzzer=51;
float durationR=0, distanceR=0,durationG=0, distanceG=0;

void setup() 
{
  // ultrasonic
 pinMode(trigPinR, OUTPUT);
 pinMode(trigPinG, OUTPUT);
 pinMode(echoPinR, INPUT);
 pinMode(echoPinG, INPUT);
 pinMode(led_green, OUTPUT);
 pinMode(led_red, OUTPUT);
 Serial.begin(9600);

  // ir and moisture
  servo1.attach(2);
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (led2, OUTPUT);
  pinMode (LED, OUTPUT); // Led pin OUTPUT
  pinMode (moisture, INPUT);
}

void loop()
{
   // ultrasonic
   digitalWrite(trigPinG, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPinG, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinG, LOW);
   durationG = pulseIn(echoPinG, HIGH);
   distanceG = (durationG*.0343)/2;
   delay(10);
   digitalWrite(trigPinR, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPinR, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinR, LOW);
   durationR = pulseIn(echoPinR, HIGH);
   distanceR = (durationR*.0343)/2;
   delay(10);
   if(distanceG<=5 || distanceR<=5 ){
     tone(buzzer, 500);
     if(distanceG<=5){
      digitalWrite(led_red,LOW);
      digitalWrite(led_green,HIGH);
      
     }
     else{
      digitalWrite(led_green,LOW);
      digitalWrite(led_red,HIGH);
      
     }
     }
    
   else{
    
         int value = analogRead(moisture);
         int statusSensor = digitalRead (IRSensor);
         if (statusSensor == 0){
            delay(1000);
             if (value<=300) {
               digitalWrite(led2, LOW);
               digitalWrite(LED, HIGH); 
               delay(500);
               servo1.write(80); // resets to initial position
               delay(1000);
              } else {
              digitalWrite(LED, LOW);
              digitalWrite(led2, HIGH);
              delay(500);
              servo1.write(300); // resets to initial position
              delay(1000);
              }
    }}
   delay(10);
   
  
 
}
