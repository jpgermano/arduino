#include <Ultrasonic.h>

//Pins for motor A
const int MotorA1 = 4;
const int MotorA2 = 5;

//Pins for motor B
const int MotorB1 = 6;
const int MotorB2 = 7;

//Pins for ultrasonic sensor
const int trigger = 8;
const int echo = 10;

int pinSensor = A0;
int valueSensor = 0;

int pinSensor1 = A1;
int valueSensor1 = 0;

int pinSensor2 = A2;
int valueSensor2 = 0;

int numcycles = 0;
int oponentDistance;
char choice = 'l';

const int distancelimit = 50; //Distance limit for obstacles in front
char turndirection;
// const int sidedistancelimit = 12; //Minimum distance in cm to obstacles at both sides (the robot will allow a shorter distance sideways)

void setup() {
  //  head.attach(5);
  // head.write(80);
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");

  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pinSensor, INPUT);
  pinMode(pinSensor1, INPUT);

  //Variable inicialization
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
  digitalWrite(trigger, LOW);
}

void go() {
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
}

void backwards(int t) {
  digitalWrite (MotorA1 , LOW);
  digitalWrite (MotorA2, HIGH);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, HIGH);
  delay(t);
}

int watch() {
  long howfar;
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigger, LOW);
  howfar = pulseIn(echo, HIGH);
  howfar = howfar * 0.01657; //how far away is the object in cm
  return round(howfar);
}

void turnleft(int t) {
  digitalWrite (MotorA1, LOW);
  digitalWrite (MotorA2, HIGH);
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
  delay(t);
}

void turnright(int t) {
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, HIGH);
  delay(t);
}

void stopmove() {
  digitalWrite (MotorA1 , LOW);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, LOW);
}

char decide() {
  if (oponentDistance > distancelimit && choice == 'r') {
    choice = 'l';
  }
  else if (oponentDistance > distancelimit && choice == 'l') {
    choice = 'r';
  }
  return choice;
}

void verifyLine() {
  valueSensor = analogRead(pinSensor);
 
  if (valueSensor < 500) {
    Serial.println("--------------------------------------------");
    Serial.print("Linha identificada, Sensor ESQUERDO:");
    Serial.println(valueSensor);
    stopmove();
    backwards(500);
    turnright(800);
    Serial.println("--------------------------------------------");
    Serial.println("");
  } 
  valueSensor1 = analogRead(pinSensor1);
 
  if ( valueSensor1 < 500) {
  Serial.println("--------------------------------------------");
    Serial.print("Linha identificada, Sensor DIREITO:");
    Serial.println(valueSensor1);
    stopmove();
    backwards(500);
    turnleft(800);
  Serial.println("--------------------------------------------");
  Serial.println("");
  } 
//  valueSensor2 = analogRead(pinSensor2);
//  Serial.print("Sensor 2:");
//  Serial.println(valueSensor2);
//  if ( valueSensor2 < 300) {
//    stopmove();
//    go();
//    delay(550);
//    turnleft(800);
//  }
}

int getDistance() {
  int valueDistance = watch();

  Serial.print("Distancia:");
  Serial.println(valueDistance);
  if (valueDistance < 75) {
    oponentDistance = valueDistance;
  }else{
    oponentDistance = 55;
  }
  return oponentDistance;
}

void goAhead() {
  oponentDistance = getDistance();
  while (oponentDistance < distancelimit) {
    Serial.println("--------------------------------------------");
    Serial.println("OPONENTE ENOONTRADO!!!!");
    verifyLine();
    go();
    oponentDistance = getDistance();
    Serial.println("--------------------------------------------");
    Serial.println("");
  }
}

void loop() {
  
  oponentDistance = getDistance();
  while (oponentDistance > distancelimit) {
    goAhead();
    turndirection = decide();
    if (turndirection == 'l') {
      Serial.println("Procurando Oponente à ESQUERDA");
      turnleft(1000);
      goAhead();
      verifyLine();
      } else {
      Serial.println("Procurando Oponente à DIREITA");
      turnright(1000);
      goAhead();
      verifyLine();
    }if(numcycles > 5 && turndirection == 'l'){
      numcycles = 0;
      turndirection = 'r';
    }else if(numcycles > 5 && turndirection == 'r'){
      numcycles = 0;
      turndirection = 'l';
    }
  numcycles++;
  }

}

