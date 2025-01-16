
#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>

#define led 12  

const char *ssid = "AAA";
const char *password = "90iojknm";

NetworkServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
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

            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            client.println();
            
            break;
          } else {  
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;     
        }

        
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);  
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);  
        }
      }
    }
    
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
