#ifndef API_H
#define API_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include "../led/led.h"

class API {
    public:
        API(ESP8266WebServer &server, Led &led) : server_(server), led_(led) {}
        void setup();

    private:
        ESP8266WebServer &server_;
        Led &led_;
        void handleLed();
        void staticLed();
};

#endif
