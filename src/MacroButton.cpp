#include "MacroButton.h"


size_t MacroButton::printTo(Print &p) const
{
    char buff[22];
    // snprintf(buff, sizeof(buff), "pin: %d, keycode: %d, period: %d, count: %d, state: %s", pin, keycode, period, count, isPressed() ? "true" : "false");
    // snprintf(buff, sizeof(buff), "P%d, CT: %d, %s", pin, count, isPressed() ? "ON" : "OFF");
    snprintf(buff, sizeof(buff), "%s %02d 0x%02x %03d %s", _name, pin, keycode, count, isPressed() ? "ON" : "OFF");
    return p.print(buff);
}

bool MacroButton::update()
{
    Bounce2::Button::update();
    bool fell = Bounce2::Button::fell();
    currentState = Bounce2::Button::isPressed();
    if (fell) {
        count++;
    }
    return fell;
}

MacroButton::MacroButton(uint8_t pin, uint8_t keycode, uint16_t period, const char* name) : Bounce2::Button(), _name(name)
{
    this->keycode = keycode;
    this->pin = pin;
    this->period = period;
    count = 0;
}

void MacroButton::begin()
{

    Bounce2::Button::attach(pin, INPUT_PULLUP);
    Bounce2::Button::interval(period);
    Bounce2::Button::setPressedState(LOW);
}