
#include <WiFi.h>

const char *ssid = "Thuliv2.4G";
const char *password = "90Iojknm@";
unsigned long tempo = 0;
#define solenoide 12
#define conected 13
#define rele_1 14
#define rele_2 27
#define rele_3 26
#define rele_4 25
#define rele_5 33
#define rele_6 32
#define rele_7 15
#define rele_8 4

IPAddress local_IP(192, 168, 0, 249);
IPAddress gateway(192, 168, 0, 249);
IPAddress subnet(255, 255, 0, 0);

NetworkServer server(80);

void setup() {

  Serial.begin(115200);

  pinMode(solenoide, OUTPUT);  
  pinMode(conected, OUTPUT);  
  pinMode(rele_1, OUTPUT); 
  pinMode(rele_2, OUTPUT);
  pinMode(rele_3, OUTPUT);
  pinMode(rele_4, OUTPUT);
  pinMode(rele_5, OUTPUT);
  pinMode(rele_6, OUTPUT);
  pinMode(rele_7, OUTPUT);
  pinMode(rele_8, OUTPUT);

  digitalWrite(solenoide, LOW);
  digitalWrite(conected, LOW);
  digitalWrite(rele_1, HIGH);
  digitalWrite(rele_2, HIGH);
  digitalWrite(rele_3, HIGH);
  digitalWrite(rele_4, HIGH);
  digitalWrite(rele_5, HIGH);
  digitalWrite(rele_6, HIGH);
  digitalWrite(rele_7, HIGH);
  digitalWrite(rele_8, HIGH);

  ConectaWiFi();
}


void ConectaWiFi() {

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite (conected, LOW);
  } 
  
  digitalWrite (conected, HIGH);

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}


void loop() {

  NetworkClient client = server.accept();  

  if (client) {                     
    Serial.println("New Client.");  
    String currentLine = "";        
    while (client.connected()) {    
      if (client.available()) {     
        char c = client.read();     
        Serial.write(c);            
        if (c == '\n') {            

          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("<h1>Click <a href=\"/Waldir\">aqui</a> para abrir a fechadura.<br></h1>");
            client.print("<h1>Click <a href=\"/Leiliane\">aqui</a> para ligar rele 1.<br></h1>");
            client.print("<h1>Click <a href=\"/Tatizinha\">aqui</a> para desligar rele 1.<br></h1>");
            client.print("<h1>Click <a href=\"/Ana\">aqui</a> para ligar rele 2.<br></h1>");
            client.print("<h1>Click <a href=\"/Arthur\">aqui</a> para desligar rele 2.<br></h1>");
            client.print("<h1>Click <a href=\"/Livia\">aqui</a> para ligar rele 3.<br></h1>");
            client.print("<h1>Click <a href=\"/Sara\">aqui</a> para desligar rele 3.<br></h1>");
            client.print("<h1>Click <a href=\"/Roberta\">aqui</a> para ligar rele 4.<br></h1>");
            client.print("<h1>Click <a href=\"/Carlinha\">aqui</a> para desligar rele 4.<br></h1>");
            client.print("<h1>Click <a href=\"/Paulinha\">aqui</a> para ligar rele 5.<br></h1>");
            client.print("<h1>Click <a href=\"/Lea\">aqui</a> para desligar rele 5.<br></h1>");
            client.print("<h1>Click <a href=\"/Vitoria\">aqui</a> para ligar rele 6.<br></h1>");
            client.print("<h1>Click <a href=\"/Camila\">aqui</a> para desligar rele 6.<br></h1>");
            client.print("<h1>Click <a href=\"/Angelica\">aqui</a> para ligar rele 7.<br></h1>");
            client.print("<h1>Click <a href=\"/Monica\">aqui</a> para desligar rele 7.<br></h1>");
            client.print("<h1>Click <a href=\"/Lexa\">aqui</a> para ligar rele 8.<br></h1>");
            client.print("<h1>Click <a href=\"/Anitta\">aqui</a> para desligar rele 8.<br></h1>");

            client.println();
            
            break;
          } else {  
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }

        if (currentLine.endsWith("GET /Waldir")) {
          tempo = millis();
          digitalWrite(solenoide, HIGH);
        }

        else if (currentLine.endsWith("GET /Leiliane")) {
          digitalWrite(rele_1, LOW);
        }

        else if (currentLine.endsWith("GET /Tatizinha")) {
          digitalWrite(rele_1, HIGH);
        }

        else if (currentLine.endsWith("GET /Ana")) {
          digitalWrite(rele_2, LOW);
        }

        else if (currentLine.endsWith("GET /Arthur")) {
          digitalWrite(rele_2, HIGH);
        }

        else if (currentLine.endsWith("GET /Livia")) {
          digitalWrite(rele_3, LOW);
        }

        else if (currentLine.endsWith("GET /Sara")) {
          digitalWrite(rele_3, HIGH);
        }

        else if (currentLine.endsWith("GET /Roberta")) {
          digitalWrite(rele_4, LOW);
        }

        else if (currentLine.endsWith("GET /Carlinha")) {
          digitalWrite(rele_4, HIGH);
        }

        else if (currentLine.endsWith("GET /Paulinha")) {
          digitalWrite(rele_5, LOW);
        }

        else if (currentLine.endsWith("GET /Lea")) {
          digitalWrite(rele_5, HIGH);
        }

        else if (currentLine.endsWith("GET /Vitoria")) {
          digitalWrite(rele_6, LOW);
        }

        else if (currentLine.endsWith("GET /Camila")) {
          digitalWrite(rele_6, HIGH);
        }

        else if (currentLine.endsWith("GET /Angelica")) {
          digitalWrite(rele_7, LOW);
        }

        else if (currentLine.endsWith("GET /Monica")) {
          digitalWrite(rele_7, HIGH);
        }

        else if (currentLine.endsWith("GET /Lexa")) {
          digitalWrite(rele_8, LOW);
        }

        else if (currentLine.endsWith("GET /Anitta")) {
          digitalWrite(rele_8, HIGH);
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }

  if ((millis() - tempo) > 500) {
    digitalWrite(solenoide, LOW);  
  }

  if(WiFi.status() != WL_CONNECTED) {
    ConectaWiFi();
  }
}
