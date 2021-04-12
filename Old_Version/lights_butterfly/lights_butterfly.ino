#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int treeSensor = A0;
const int bushSensor = A1;
const int mountainSensor = A2;
const int shrubSensor = A3;
int LEDPins[] = {12, 11, 10, 9, 8, 7};
int countOFpin = 6; //number of pins 

void setup() {
  Serial.begin(9600);
  pinMode(treeSensor,INPUT);
  pinMode(bushSensor,INPUT);

  for (int PIN = 0; PIN < countOFpin; PIN = PIN + 1){
    pinMode(LEDPins[PIN], OUTPUT);  //initialize LED pins as output
  }
}

void loop() {
  int count = inPlace();
  lights(count);
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

int inPlace(){
  int count = 0;
  int tree = analogRead(treeSensor);
  Serial.print("\nTree reading = ");
  Serial.print(tree);
  int bush = analogRead(bushSensor);
  Serial.print("\nBush reading = ");
  Serial.print(bush);
  int mountain = analogRead(mountainSensor);
  Serial.print("\nMountain reading = ");
  Serial.print(mountain);
  int shrub = analogRead(shrubSensor);
  Serial.print("\nShrub reading = ");
  Serial.print(shrub);
  if (tree >= 325){
    count++;
  }
  if (bush >= 325){
    count++;
  }
  if (mountain >= 325){
    count++;
  }
  if (shrub >= 325){
    count++;
  }
  return count;
}
