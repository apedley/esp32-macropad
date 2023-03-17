#ifndef __BLEMACROPAD_H
#define __BLEMACROPAD_H

#include <BleKeyboard.h>

class KeyboardDisplay;

class BleMacropad : public BleKeyboard {

    public:
    BleMacropad(uint32_t repeatDelay) : BleKeyboard("BLE Macro Pad", "Arduino", 82)
    {
        this->setDelay(repeatDelay);
    }

    void volup();
    void voldown();

};
#endif