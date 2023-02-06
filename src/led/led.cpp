#include <Adafruit_NeoPixel.h>
#include "../../constants.h"
#include "led.h"

void Led::setStatic(int color) {
    strip_.fill(color, 0, LED_COUNT);
    strip_.show();
}