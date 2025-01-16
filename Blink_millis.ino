#define led 14
unsigned long tempo = 0;


void setup() {

  pinMode(led, OUTPUT);

}



void loop() {

  if ((millis() - tempo) < 2000) {
    digitalWrite(led, HIGH);
  } 

  if ((millis() - tempo) > 2000) {
    digitalWrite(led, LOW); 
  }                  

  if ((millis() - tempo) == 4000) {
      tempo = millis();
  }                          
}
