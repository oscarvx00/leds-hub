<<<<<<< HEAD
void setup() {
  // put your setup code here, to run once:
=======
#include "src/api/api.h"
#include "src/led/led.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "creds.h"
#include "constants.h"
#include <Adafruit_NeoPixel.h>


ESP8266WebServer server(80);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ400);
Led led(strip);
API api(server, led);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.fill(0x111111, 0, LED_COUNT);
  strip.show();
  digitalWrite(2, HIGH);
  WiFi.begin(ssid, password);
  pinMode(2, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
>>>>>>> 462f843... .

}

void loop() {
  // put your main code here, to run repeatedly:

}
