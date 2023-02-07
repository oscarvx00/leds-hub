#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>


class Led {
    public:
        Led(Adafruit_NeoPixel &strip) : strip_(strip) {}
        void setStatic(int color, int section);
        void setStaticFade3(int color1, int color2, int color3);

    private:
        Adafruit_NeoPixel &strip_;
        struct Color * getGradientArray(uint32_t col1, uint32_t col2, int gradientLength);
        void putFadeArray(struct Color * fadeArray, int startPos, int length);
        struct Color getColorStruct(uint32_t col);
        
};

struct Color{
  byte r;
  byte g;
  byte b;
};


#endif