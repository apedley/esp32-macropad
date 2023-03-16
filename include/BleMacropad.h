#ifndef __BLEMACROPAD_H
#define __BLEMACROPAD_H

#include <BleKeyboard.h>

class KeyboardDisplay;

class BleMacropad : public BleKeyboard {

    public:
    BleMacropad() : BleKeyboard("BLE Macro Pad", "Arduino", 82)
    {
    }

    void volup();
    void voldown();

};
#endif