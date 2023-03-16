#ifndef __KEYBOARDKNOB_H
#define __KEYBOARDKNOB_H
#include <ESP32Encoder.h>

class KeyboardKnob : public ESP32Encoder {
public:
    KeyboardKnob(int data, int clock);
    
    const int64_t getValue() const {
        return _value;
    }

    void begin();
    bool update();
private:
    int64_t _value;
    int _dataPin;
    int _clockPin;
};

#endif