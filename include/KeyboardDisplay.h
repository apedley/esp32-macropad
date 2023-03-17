#ifndef __KEYBOARD_DISPLAY_H
#define __KEYBOARD_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "MacroButton.h"

// class KeyboardUI {
// public:
//     KeyboardUI() {
        
//     }
// private:
    
// };

class KeyboardDisplay : public Adafruit_SSD1306 {
public:
    KeyboardDisplay(uint8_t w, uint8_t h, TwoWire *twi, int8_t rst = -1) : Adafruit_SSD1306(w, h, twi, rst)
    {

    }

    void init();
    void showMacroButton(MacroButton &button, const int16_t y);
    void showOverview(MacroButton *buttons[], size_t size, bool bleConnected, long rotaryEncoderValue);
    void drawAlert(const char *message);
    void drawImage(const uint8_t *image, const int16_t w, const int16_t h);


private:
    void drawCenterString(const char *buf, int x, int y);
    bool _alert = false;
    long _alertTime = 0;
};

#endif