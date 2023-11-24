

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 144, 1);

EthernetServer server(80);

const int LED_PIN = 13;

void setup() {

  pinMode(LED_PIN, INPUT);

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Ethernet WebServer Example");

  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1);
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }


  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Novo cliente conectado!");

    if (client.available()) {
      char c = client.read();
      if (c == 'A') {
        digitalWrite(LED_PIN, HIGH);
      } else if (c == 'B') {

        digitalWrite(LED_PIN, LOW);
      }
    }
  }
}

