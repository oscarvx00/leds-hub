#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>


class Led {
    public:
        Led(Adafruit_NeoPixel &strip) : strip_(strip) {}
        void setStatic(int color);

    private:
        Adafruit_NeoPixel &strip_;
        
};


#endif