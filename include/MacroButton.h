#ifndef __MACRO_BUTTON_H__
#define __MACRO_BUTTON_H__

#include "Bounce2.h"
#include "Printable.h"

class MacroButton : public Bounce2::Button, public Printable {
    public:
    MacroButton(uint8_t pin, uint8_t keycode, uint16_t period);

    void begin();

    bool update();

    const bool pressed() const
    {
        return Bounce2::Button::pressed();
    }

    const bool isPressed() const
    {
        return Bounce2::Button::isPressed();
    }

    const uint8_t getCount() const
    {
        return count;
    }

    virtual size_t printTo(Print& p) const;

    protected:
    uint8_t keycode;
    uint8_t pin;
    uint8_t count;
    uint16_t period;
    bool currentState;
};

#endif