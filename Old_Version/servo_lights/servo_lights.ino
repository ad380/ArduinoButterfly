#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int treeSensor = A0;
const int bushSensor = A1;
const int mountainSensor = A2;
const int shrubSensor = A3;
int LEDPins[] = {14, 13, 12, 11, 10, 9, 8};
int countOFpin = 6; //number of pins 

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo1.attach(7);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);  // attaches the servo on pin 8 to the servo object
  pinMode(treeSensor,INPUT);
  pinMode(bushSensor,INPUT);

  for (int PIN = 0; PIN < countOFpin; PIN = PIN + 1){
    pinMode(LEDPins[PIN], OUTPUT);  //initialize LED pins as output
  }
}

void loop() {
  int count = inPlace();
  moveServo(count);
  lights(count);
}

void moveServo(int objCount) {
  int wingSpeed = map(objCount, 0,4,15,5);
  for (pos = 90; pos <= 175; pos += 1) { // goes from 0 degrees to 85 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    delay(wingSpeed);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 175; pos >= 90; pos -= 1) { // goes from 85 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    delay(wingSpeed);                       // waits 15ms for the servo to reach the position
  }
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
  if (tree >= 60){
    count++;
  }
  if (bush >= 60){
    count++;
  }
  if (mountain >= 60){
    count++;
  }
  if (shrub >= 60){
    count++;
  }
  return count;
}
