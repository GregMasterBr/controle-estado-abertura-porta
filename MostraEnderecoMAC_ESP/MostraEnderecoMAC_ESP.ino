//Programa: Mostra endereco MAC do modulo ESP8266

#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);

  delay(500);

  Serial.println();
  Serial.print("Endereco MAC: ");
  Serial.println(WiFi.macAddress());
}

void loop() {}
