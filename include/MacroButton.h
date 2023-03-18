#ifndef __MACRO_BUTTON_H__
#define __MACRO_BUTTON_H__

#include "Bounce2.h"
#include "Printable.h"

class MacroButton : public Bounce2::Button, public Printable {
public:
    MacroButton(uint8_t pin, uint8_t keycode, uint16_t period, const char* name);

    void begin();

    bool update();


    const uint8_t getCount() const
    {
        return count;
    }
    const uint8_t getKeycode() const
    {
        return keycode;
    }

    const bool getCurrentState() const
    {
        return currentState;
    }

    const char* getName() const
    {
        return _name;
    }
    
    virtual size_t printTo(Print& p) const;

protected:
    uint8_t keycode;
    uint8_t pin;
    uint8_t count;
    uint16_t period;
    bool currentState = false;
private:
    const char* _name;
};

#endif