
#define led 14
#define conectado 12
char caracter = ' ';
String texRecebido = "";
unsigned long tempo = 0;
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;


void setup() {

  Serial.begin(115200);
  SerialBT.begin("Cadeado");  
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
    texRecebido += caracter;
    Serial.println(texRecebido);
    tempo = millis();
  }  

  if (texRecebido == "Waldir") {
    digitalWrite(led, HIGH);
  }

  if ((millis() - tempo) > 500) {
    digitalWrite(led, LOW);
    texRecebido = "";
  }
}
