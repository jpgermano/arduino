#include <Thread.h>
#include <ThreadController.h>
#include <Ultrasonic.h>

Thread threadMotor;
Thread threadSensor;
Thread threadDebug;
ThreadController controller;

const int trigger = 8;
const int echo = 10;

int ESQ_HORARIO = 2 ;
int ESQ_ANTE_HORARIO = 4 ;
int RODA_DIREITA = 5;

int DIR_HORARIO = 6 ;
int DIR_ANTE_HORARIO = 7 ;
int RODA_ESQUERDA = 3;

//variavel auxiliar
int speed = 0;

int MAX = 300;
int MED = 150;
int MIN = 20;

const int pinSensor = A1;
int valueSensor = 0;

const int pinSensor1 = A1;
int valueSensor1 = 0;

bool line = false;
bool choice = false;
long set = 500;
long outset = 0;
int cicle = 1;

Ultrasonic ultrasonic(trigger, echo);

void setup() {
  Serial.begin(5500);
  onInit();
  threadMotor.setInterval(85);
  threadMotor.onRun(controlRobot);
  threadSensor.setInterval(150);
  threadSensor.onRun(verifyLine);
//  threadDebug.setInterval(300);
//  threadDebug.onRun(doDebug);

  controller.add(&threadMotor);
  controller.add(&threadSensor);
//  controller.add(&threadDebug);
}

void onInit() {
  pinMode(DIR_HORARIO, OUTPUT);
  pinMode(DIR_ANTE_HORARIO, OUTPUT);
  pinMode(ESQ_HORARIO, OUTPUT);
  pinMode(ESQ_ANTE_HORARIO, OUTPUT);
  pinMode(RODA_DIREITA, OUTPUT);
  pinMode(RODA_ESQUERDA, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pinSensor, INPUT);
  pinMode(pinSensor1, INPUT);
  digitalWrite(trigger, LOW);
}

void controlRobot() {
  if (ultrasonic.distanceRead() < 40 && line == false && ultrasonic.distanceRead() != 0) {
    speed = MAX;
    go();
  } else if (line == false && ultrasonic.distanceRead() != 0) {
    speed = MIN;
    turnRight();
  }
}

void verifyLine() {
  valueSensor = analogRead(pinSensor);
  valueSensor1 = analogRead(pinSensor1);
  
  if (valueSensor <= 150 || valueSensor1 <= 150) { 
    speed = MED;
    backwards();
    line = true;
  } else{  
    line = false;
  }
}

void turnAround() {
  choice ? turnLeft() : turnRight();
}

void go() {
  digitalWrite (DIR_HORARIO, HIGH);
  digitalWrite (DIR_ANTE_HORARIO, LOW);
  digitalWrite (ESQ_HORARIO, HIGH);
  digitalWrite (ESQ_ANTE_HORARIO, LOW);
  analogWrite (RODA_ESQUERDA, speed);
  analogWrite (RODA_DIREITA, speed);
}

void backwards() {
  digitalWrite (DIR_HORARIO , LOW);
  digitalWrite (DIR_ANTE_HORARIO, HIGH);
  digitalWrite (ESQ_HORARIO, LOW);
  digitalWrite (ESQ_ANTE_HORARIO, HIGH);
  analogWrite (RODA_ESQUERDA, speed);
  analogWrite (RODA_DIREITA, speed);
}

void turnLeft() {
  digitalWrite (DIR_HORARIO, LOW);
  digitalWrite (DIR_ANTE_HORARIO, HIGH);
  digitalWrite (ESQ_HORARIO, HIGH);
  digitalWrite (ESQ_ANTE_HORARIO, LOW);
  analogWrite (RODA_ESQUERDA, speed);
  analogWrite (RODA_DIREITA, speed);
}

void turnRight() {
  digitalWrite (DIR_HORARIO, HIGH);
  digitalWrite (DIR_ANTE_HORARIO, LOW);
  digitalWrite (ESQ_HORARIO, LOW);
  digitalWrite (ESQ_ANTE_HORARIO, HIGH);
  analogWrite (RODA_ESQUERDA, speed);
  analogWrite (RODA_DIREITA, speed);
}

void stopmove() {
  digitalWrite (DIR_HORARIO , LOW);
  digitalWrite (DIR_ANTE_HORARIO, LOW);
  digitalWrite (ESQ_HORARIO, LOW);
  digitalWrite (ESQ_ANTE_HORARIO, LOW);
  analogWrite (RODA_ESQUERDA, speed);
  analogWrite (RODA_DIREITA, speed);
}

void doDebug() {
  Serial.println("Distancia em CM: ");
  Serial.println(ultrasonic.distanceRead());

  Serial.println("Sensor InfraVer: ");
  Serial.println(valueSensor);
  Serial.println("Sensor InfraVer1: ");
  Serial.println(valueSensor1);
}
/* Ativar ou desativar debug */
bool ativo = false;
void loop () {
  ativo ? threadDebug.enabled = true : threadDebug.enabled = false;
  controller.run();
}



