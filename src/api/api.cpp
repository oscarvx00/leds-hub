#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "api.h"
#include <Adafruit_NeoPixel.h>
#include "../../constants.h"
#include "../led/led.h"



/*
void handleRoot(ESP8266WebServer &server) {
  server.send(200, "text/plain", "Welcome to my REST API");
}

void handleSensor(ESP8266WebServer &server) {
  int sensorValue = analogRead(A0);
  String response = "{\"value\":" + String(sensorValue) + "}";
  server.send(200, "application/json", response);
}*/

void API::setup() {
  server_.on("/led", HTTP_POST, [this]() { handleLed(); });
  server_.on("/led/static", HTTP_POST, [this]() { staticLed(); });
  server_.on("/led/staticFade3", HTTP_POST, [this]() { staticFade3(); });
}

void API::handleLed() {
  StaticJsonDocument<200> jsonDoc;

  if (server_.hasArg("plain") && server_.arg("plain").length() > 0) {
    DeserializationError error = deserializeJson(jsonDoc, server_.arg("plain"));

    if (error) {
      server_.send(400, "text/plain", "Invalid JSON");
      return;
    }

    if (jsonDoc.containsKey("state")) {
      String state = jsonDoc["state"];
      if (state == "on") {
        digitalWrite(2, LOW);
        //strip_.fill(0x000011, 0, LED_COUNT);
        //strip_.show();
        Serial.println("ON...");
        server_.send(200, "text/plain", "LED turned on");
      } else if (state == "off") {
        digitalWrite(2, HIGH);
        //strip_.fill(0x001100, 0, LED_COUNT);
        //strip_.show();
        Serial.println("OFF...");
        server_.send(200, "text/plain", "LED turned off");
      } else {
        server_.send(400, "text/plain", "Invalid state argument");
      }
    } else {
      server_.send(400, "text/plain", "Missing state argument");
    }
  } else {
    server_.send(400, "text/plain", "Missing request body");
  }
}


void API::staticLed() {
  StaticJsonDocument<400> jsonDoc;

  if (server_.hasArg("plain") && server_.arg("plain").length() > 0) {
    DeserializationError error = deserializeJson(jsonDoc, server_.arg("plain"));

    if (error) {
      server_.send(400, "text/plain", "Invalid JSON");
      return;
    }

    for(int index = 0; index<3; index++){
      int strip = jsonDoc["request"][index]["strip"];
      const char* color = jsonDoc["request"][index]["color"]; // "0x110000"

      int colorInt = 0;
      sscanf(color, "%x", &colorInt);

      led_.setStatic(colorInt, strip);
    }

    server_.send(200, "text/plain", "OK");

    /*if (jsonDoc.containsKey("color")) {
      String color = jsonDoc["color"];
      int colorInt = 0;
      sscanf(color.c_str(), "%x", &colorInt);
      led_.setStatic(colorInt);
      server_.send(200, "text/plain", "OK");
    } else {
      server_.send(400, "text/plain", "Missing color argument");
    }*/
  } else {
    server_.send(400, "text/plain", "Missing request body");
  }
}


void API::staticFade3() {
  StaticJsonDocument<400> jsonDoc;

  if (server_.hasArg("plain") && server_.arg("plain").length() > 0) {
    DeserializationError error = deserializeJson(jsonDoc, server_.arg("plain"));

    if (error) {
      server_.send(400, "text/plain", "Invalid JSON");
      return;
    }

    int colors[] = {0,0,0};

    for(int index = 0; index<3; index++){
      const char* color = jsonDoc["request"][index]["color"]; // "0x110000"

      int colorInt = 0;
      sscanf(color, "%x", &colorInt);

      colors[index] = colorInt;
    }

    led_.setStaticFade3(colors[0], colors[1], colors[2]);

    server_.send(200, "text/plain", "OK");

    /*if (jsonDoc.containsKey("color")) {
      String color = jsonDoc["color"];
      int colorInt = 0;
      sscanf(color.c_str(), "%x", &colorInt);
      led_.setStatic(colorInt);
      server_.send(200, "text/plain", "OK");
    } else {
      server_.send(400, "text/plain", "Missing color argument");
    }*/
  } else {
    server_.send(400, "text/plain", "Missing request body");
  }
}
