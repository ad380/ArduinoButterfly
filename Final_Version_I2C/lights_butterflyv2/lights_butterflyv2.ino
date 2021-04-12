#include <Servo.h>
#include <Wire.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int LEDPins[] = {13, 10, 9, 8, 7, 6};
int countOFpin = 6; //number of pins 

int tree, bush, mountain, shrub;

void setup() {
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  for (int PIN = 0; PIN < countOFpin; PIN = PIN + 1){
    pinMode(LEDPins[PIN], OUTPUT);  //initialize LED pins as output
  }
}

void loop() {
  int count = inPlace(tree,bush,mountain,shrub);
  lights(count);
}
void receiveEvent(int bytes){
  byte a,b;
  a = Wire.read();
  b = Wire.read();
  int bigNum = a;
  tree = bigNum << 8 | b;
  
  a = Wire.read();
  b = Wire.read();
  bigNum = a;
  bush = bigNum << 8 | b;
  
  a = Wire.read();
  b = Wire.read();
  bigNum = a;
  mountain = bigNum << 8 | b;
  
  a = Wire.read();
  b = Wire.read();
  bigNum = a;
  shrub = bigNum << 8 | b;
  
  Serial.print(tree);
  Serial.print(' ');
  Serial.print(bush);
  Serial.print(' ');
  Serial.print(mountain);
  Serial.print(' ');
  Serial.print(shrub);
  Serial.print('\n');
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

int inPlace(int tree,int bush,int mountain,int shrub){
  int count = 0;
  if (tree >= 30){
    count++;
  }
  if (bush >= 30){
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
