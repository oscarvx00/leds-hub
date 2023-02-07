#include <Adafruit_NeoPixel.h>
#include "../../constants.h"
#include "led.h"

class Section {
    public:
    Section(int start_, int end_) {
        start = start_;
        end = end_;
    }
    int start;
    int end;
};

Section sections[] = {
    Section(0, 30),
    Section(30,60),
    Section(60, 90)
};

void Led::setStatic(int color, int section) {
    strip_.fill(color, sections[section].start, sections[section].end);
    strip_.show();
}

void Led::setStaticFade3(int col1, int col2, int col3) {
    int fadeLength = 15;
    int m1 = LED_COUNT / 3;
    int m2 = 2 * m1;

    struct Color *fadeArray1 = getGradientArray(col1, col2, fadeLength);
    struct Color *fadeArray2 = getGradientArray(col2, col3, fadeLength);

    strip_.fill(col1, 0, m1);
    strip_.fill(col2, m1, m2);
    strip_.fill(col3, m2, LED_COUNT);

    putFadeArray(fadeArray1, m1, fadeLength);
    putFadeArray(fadeArray2, m2, fadeLength);


    free(fadeArray1);
    free(fadeArray2);

    strip_.show();
}



struct Color * Led::getGradientArray(uint32_t col1, uint32_t col2, int gradientLength){

  struct Color *colorArray;
  
  struct Color color1, color2;

  float pColorR, pColorG, pColorB;

  color1 = getColorStruct(col1);
  color2 = getColorStruct(col2);

  float rFadeValue, gFadeValue, bFadeValue;

  rFadeValue = ((float)(max(color1.r, color2.r) - min(color1.r, color2.r)))/gradientLength;
  gFadeValue = ((float)(max(color1.g, color2.g) - min(color1.g, color2.g)))/gradientLength;
  bFadeValue = ((float)(max(color1.b, color2.b) - min(color1.b, color2.b)))/gradientLength;

  colorArray = (struct Color *) malloc(sizeof(struct Color) * gradientLength);

  for(int i=0;i<gradientLength;i++){

    color1.r < color2.r? pColorR = color1.r + (rFadeValue * i) : pColorR = color1.r - (rFadeValue * i);
    color1.g < color2.g? pColorG = color1.g + (gFadeValue * i) : pColorG = color1.g - (gFadeValue * i);
    color1.b < color2.b? pColorB = color1.b + (bFadeValue * i) : pColorB = color1.b - (bFadeValue * i);

    colorArray[i].r = (byte) pColorR;
    colorArray[i].g = (byte) pColorG;
    colorArray[i].b = (byte) pColorB;
  }

  return colorArray;
}

void Led::putFadeArray(struct Color * fadeArray, int startPos, int length){

  int halfFade = length/2;
  int ledP, ledCalc;

  int limitBottom = startPos - halfFade;

  for(int i=0; i<length; i++){
    ledCalc = limitBottom + i;
    if(ledCalc >= LED_COUNT){
      ledP = ledCalc - LED_COUNT;
    } else if(ledCalc < 0){
      ledP = LED_COUNT + ledCalc;
    }
    else{
      ledP = ledCalc;
    }
    strip_.setPixelColor(ledP, fadeArray[i].r, fadeArray[i].g, fadeArray[i].b);
  }
}

struct Color Led::getColorStruct(uint32_t col){

  Color color;

  color.r = col >> 16;
  color.g = col >> 8;

  color.b = col;

  #ifdef DEBUG
  printSerialColorStruct(color);
  #endif

  return color;
}