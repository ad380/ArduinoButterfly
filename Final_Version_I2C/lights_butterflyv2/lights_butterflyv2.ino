#include <Servo.h>
#include <Wire.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int LEDPins[] = {13, 10, 9, 8, 7, 6};
int countOFpin = 6; //number of pins 

int count;
void setup() {
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  for (int PIN = 0; PIN < countOFpin; PIN = PIN + 1){
    pinMode(LEDPins[PIN], OUTPUT);  //initialize LED pins as output
  }
}

void loop() {
  lights(count);
}

void receiveEvent(int bytes){
  byte b = Wire.read();
  count = (int)b;
  Serial.println(count);
}

void lights(int objCount){
  
  int lightSpeed = map(objCount,0,4,800,50);
  if(lightSpeed <= 400){
    for (int PIN = 0; PIN < countOFpin; PIN++) {  //FAST blink from lowest pin to highest
      digitalWrite(LEDPins[PIN], HIGH);
      delay(lightSpeed);
      digitalWrite(LEDPins[PIN], LOW);  
    }
    for (int PIN = countOFpin - 1; PIN >= 0; PIN--)  { //FAST blink from highest pin to lowest
      digitalWrite(LEDPins[PIN], HIGH);
      delay(lightSpeed);
      digitalWrite(LEDPins[PIN], LOW);
    }
  }
  else{
    for (int PIN = 0; PIN < countOFpin; PIN++) {  //FAST blink from lowest pin to highest
      digitalWrite(LEDPins[PIN], HIGH);
      delay(lightSpeed);
      digitalWrite(LEDPins[PIN], LOW);  
    }
  }
}
