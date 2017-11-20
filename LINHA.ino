void setup()
{
 Serial.begin(9600); // Inicia a Serial
 Serial.println("LOJA ARDUINO / MODULOS GKB"); // Envia a mensagem de Inicio para a porta Serial
 Serial.println("Sensor de Obstaculos"); // Envia a mensagem de Inicio para a porta Serial
 Serial.println(" ");

 pinMode(A0, INPUT); //Pino ligado ao coletor do fototransistor

 pinMode(A1, INPUT); //Pino ligado ao coletor do fototransistor

// pinMode(A2, INPUT); //Pino ligado ao coletor do fototransistor
}
void loop()
{
 double sAnalogico = analogRead(A0);

 Serial.print("Sinal Analogico: ");
 Serial.println(sAnalogico);

  double sAnalogico1 = analogRead(A1);

 Serial.print("Sinal Analogico 1: ");
 Serial.println(sAnalogico1);
 
// double sAnalogico2 = analogRead(A2);
//
// Serial.print("Sinal Analogico 2: ");
// Serial.println(sAnalogico2);

 Serial.println("-------------------------------------------------------------");

 delay(1000);
}
