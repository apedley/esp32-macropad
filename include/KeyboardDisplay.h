#ifndef __KEYBOARD_DISPLAY_H
#define __KEYBOARD_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "MacroButton.h"

class KeyboardDisplay : public Adafruit_SSD1306 {
public:
    KeyboardDisplay(uint8_t w, uint8_t h, TwoWire *twi, int8_t rst = -1) : Adafruit_SSD1306(w, h, twi, rst)
    {

    }

    void init();
    void test(const char * val = "init");
    void showStatus(bool bleConnected, const char * keyOne, const char * keyTwo, long knobValue);
    void showMacroButton(MacroButton &button, const int16_t y);
    void showMacroButtonsOverview(MacroButton *buttons[], size_t size);
};

#endif