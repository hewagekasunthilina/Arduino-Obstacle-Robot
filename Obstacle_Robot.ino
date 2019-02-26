#include <Servo.h>
#include <NewPing.h>

const int LeftMoterForward = 5;
const int LeftMoterBackward = 4;
const int RightMoterForward = 3;
const int RightMoterBackward = 2;

#define trig_pin A1
#define echo_pin A2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance);
Servo servo_moter;

void setup(){
  pinMode(RightMoterForward, OUTPUT);
  pinMode(LeftMoterForward, OUTPUT);
  pinMode(LeftMoterBackward, OUTPUT);
  pinMode(RightMoterBackward, OUTPUT);

  servo_moter.attach(11);

  servo_moter.write(90);
  delay(2000);

  distance = readPing();
  delay(100);

  distance = readPing();
  delay(100);

   distance = readPing();
  delay(100);

  distance = readPing();
  delay(100);
}

void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if(distance <= 20){
    moveStop();
    delay(300);

    moveBackward();
    delay(400);

    moveStop();
    delay(300);

    distanceRight = lookRight();
    delay(300);

    distanceLeft = lookLeft();
    delay(300);

    if(distance >= distanceLeft){
      turnRight();
      moveStop();
    }

    else{
      turnLeft();
      moveStop();
    }
  }

  else{
    moveForward();
  }
  distance = readPing();
}

int lookRight(){
  servo_moter.write(10);
  delay(500);

  int distance = readPing();
  delay(100);

  servo_moter.write(90);
  return distance; 
}

int lookLeft(){
  servo_moter.write(170);
  delay(500);

  int distance = readPing();
  delay(100);

  servo_moter.write(90);
  return distance;
  delay(100);  
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();

  if(cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  digitalWrite(RightMoterForward, LOW);
  digitalWrite(LeftMoterForward, LOW);
  digitalWrite(RightMoterBackward, LOW);
  digitalWrite(LeftMoterBackward, LOW);
}

void moveForward(){
  if(!goesForward){
    goesForward = true;

    digitalWrite(LeftMoterForward, HIGH);
    digitalWrite(RightMoterForward, HIGH);

    digitalWrite(LeftMoterBackward, LOW);
    digitalWrite(RightMoterBackward, LOW);
  }
}

void moveBackward(){

  goesForward = false;

  digitalWrite(LeftMoterBackward, HIGH);
  digitalWrite(RightMoterBackward, HIGH);

  digitalWrite(LeftMoterForward, LOW);
  digitalWrite(RightMoterForward, LOW);
}

void turnRight(){

  digitalWrite(LeftMoterForward, HIGH);
  digitalWrite(RightMoterBackward, HIGH);

  digitalWrite(LeftMoterBackward, LOW);
  digitalWrite(LeftMoterForward, LOW);

  delay(500);

  digitalWrite(LeftMoterForward, HIGH);
  digitalWrite(RightMoterForward, HIGH);

  digitalWrite(LeftMoterBackward, LOW);
  digitalWrite(RightMoterBackward, LOW);
}

void turnLeft(){

  digitalWrite(LeftMoterBackward, HIGH);
  digitalWrite(RightMoterForward, HIGH);

  digitalWrite(LeftMoterForward, LOW);
  digitalWrite(RightMoterBackward, LOW);

  delay(500);

  digitalWrite(LeftMoterForward, HIGH);
  digitalWrite(RightMoterForward, HIGH);

  digitalWrite(LeftMoterBackward, LOW);
  digitalWrite(RightMoterBackward, LOW);
}
