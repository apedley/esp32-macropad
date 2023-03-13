#ifndef __BLEMACROPAD_H
#define __BLEMACROPAD_H

#include <BleKeyboard.h>

class KeyboardDisplay;

class BleMacropad : public BleKeyboard {

    public:
    BleMacropad() : BleKeyboard("BLE Macropad", "ESP32", 100)
    {
    }

    void volup();
    void voldown();

};
#endif