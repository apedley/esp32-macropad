#ifndef __BLEMACROPAD_H
#define __BLEMACROPAD_H

#include <BleKeyboard.h>

class KeyboardDisplay;

class BleMacropad : public BleKeyboard {

    public: 
    BleMacropad(uint32_t repeatDelay = 3, uint8_t batteryLevel = 100) 
        : BleKeyboard("Macropad", "ESP32", batteryLevel)
    {
        this->setDelay(repeatDelay);
    }

};
#endif