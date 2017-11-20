#include <Thread.h>
#include <ThreadController.h>
#include <Ultrasonic.h>

#define trigger 8
#define echo 10

Thread threadUltrassom;
Thread threadMotor;
Thread threadSensorLinha;

void setup() {
  Serial.begin(3500);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  threadUltrassom.setInterval(1300);
  threadUltrassom.onRun(lerUltrassom);

}

void loop () {
  threadUltrassom.run();
}

void lerUltrassom()
{
  //seta o pino 8 com um pulso baixo "LOW" ou desligado ou ainda 0
  digitalWrite(trigger, LOW);
  // delay de 2 microssegundos : ANTIGO 5
  delayMicroseconds(2);
  //seta o pino 8 com pulso alto "HIGH" ou ligado ou ainda 1
  digitalWrite(trigger, HIGH);
  //delay de 10 microssegundos ANTIGO 15
  delayMicroseconds(10);
  //seta o pino 8 com pulso baixo novamente
  digitalWrite(trigger, LOW);
  //pulseIn lê o tempo entre a chamada e o pino entrar em high
  int howfar = pulseIn(echo, HIGH);
  howfar = howfar * 0.01657; //how far away is the object in cm
  //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado
  //porque é o tempo de ida e volta do ultrassom
  // int howfar = duration / 29 / 2 ;

  Serial.print("Distancia em CM: ");
  Serial.println(howfar);
  delay (500);
  if (howfar <= 20)
  {
    threadMotor.run();
  }
}



