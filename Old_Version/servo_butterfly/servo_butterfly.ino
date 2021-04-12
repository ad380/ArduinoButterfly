#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int treeSensor = A0;
const int bushSensor = A1;
const int mountainSensor = A2;
const int shrubSensor = A3;

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo1.attach(7);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);  // attaches the servo on pin 8 to the servo object
  pinMode(treeSensor,INPUT);
  pinMode(bushSensor,INPUT);
  pinMode(mountainSensor,INPUT);
  pinMode(shrubSensor,INPUT);
}

void loop() {  
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
  
  int count = inPlace(tree,bush,mountain,shrub);
  
  moveServo(count);
}

void moveServo(int objCount) {
  int wingSpeed = map(objCount, 0,4,15,5);
  for (pos = 80; pos <= 160; pos += 1) { // goes from 0 degrees to 85 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    delay(wingSpeed);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 160; pos >= 80; pos -= 1) { // goes from 85 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    delay(wingSpeed);                       // waits 15ms for the servo to reach the position
  }
}

int inPlace(int tree,int bush,int mountain,int shrub){
  int count = 0;
  if (tree >= 30){
    count++;
  }
  if (bush >= 20){
    count++;
  }
  if (mountain >=25){
    count++;
  }
  if (shrub >= 25){
    count++;
  }
  return count;
}
