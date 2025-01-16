
#define led 14
#define conectado 12
char caracter = ' ';
unsigned long tempo = 0;
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;


void setup() {

  Serial.begin(115200);
  SerialBT.begin("Waldir");  
  Serial.println("Agora é só parear");

  pinMode(led, OUTPUT);
  pinMode(conectado, OUTPUT);

  digitalWrite(led, LOW);
  digitalWrite(conectado, LOW);

  }



void Conexao(){

  if (SerialBT.connected()) {
    digitalWrite(conectado, HIGH);
  }

  else {
    digitalWrite(conectado, LOW);
  }
}



void loop() {
  
  Conexao();
  
  if (SerialBT.available()) {
    caracter = SerialBT.read();
  }  

  if (caracter == 'P') {
    digitalWrite(led, HIGH);
    tempo = millis();
  }

  if ((millis() - tempo) > 1000) {
    digitalWrite(led, LOW);
  }
}
