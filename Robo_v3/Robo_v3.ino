#include <Thread.h>
#include <ThreadController.h>
#include <Ultrasonic.h>

#define trigger 8
#define echo 10

Thread threadUltrassom;
Thread threadMotor;
Thread threadSensor;
Thread threadDebug;
ThreadController main;

int howfar = 0;

//Pins for motor A
const int MotorA1 = 4;
const int MotorA2 = 5;

//Pins for motor B
const int MotorB1 = 6;
const int MotorB2 = 7;

const int pinSensor = A0;
int valueSensor = 0;

const int pinSensor1 = A1;
int valueSensor1 = 0;

void setup() {
  Serial.begin(3500);
  onInit();
  threadUltrassom.setInterval(50);
  threadUltrassom.onRun(readUltrassom);
  threadSensor.setInterval(50);
  threadSensor.onRun(verifyLine);
  threadMotor.setInterval(50);
  threadMotor.onRun(controlRobot);
  threadDebug.setInterval(500);
  threadDebug.onRun(doDebug);

  main.add(&threadUltrassom);
  main.add(&threadMotor);
  main.add(&threadSensor);
  main.add(&threadDebug);
}

void onInit() {
  //Variable inicialization
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pinSensor, INPUT);
  pinMode(pinSensor1, INPUT);
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
  digitalWrite(trigger, LOW);
}

void controlRobot() {
  if (howfar <= 30) {
    /* Verificar sensores de linha e calibrá-los conforme a leitura correta da linha no ring*/
    if(valueSensor < 500 || valueSensor1 < 500){
      backwards();
    }else{
      go();
    }
  }else{
    turnLeft();
    turnRight();
  }
}

void readUltrassom() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigger, LOW);
  howfar = pulseIn(echo, HIGH);
  howfar = howfar * 0.01657;
}

void verifyLine() {
  valueSensor = analogRead(pinSensor);
  valueSensor1 = analogRead(pinSensor1);
}

void go() {
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
}

void backwards() {
  digitalWrite (MotorA1 , LOW);
  digitalWrite (MotorA2, HIGH);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, HIGH);
}

void turnLeft() {
  digitalWrite (MotorA1, LOW);
  digitalWrite (MotorA2, HIGH);
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
}

void turnRight() {
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, HIGH);
}

void stopmove() {
  digitalWrite (MotorA1 , LOW);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, LOW);
}

void doDebug() {
  Serial.print("Distancia em CM (UltraSom): ");
  Serial.println(howfar);

  Serial.print("Sensor InfraVer: ");
  Serial.println(valueSensor);
  Serial.print("Sensor InfraVer1: ");
  Serial.println(valueSensor1);
}
/* Ativar ou desativar debug */
bool ativo = false;
void loop () {
  ativo ? threadDebug.enabled = true : threadDebug.enabled = false;
  main.run();
}

