#ifndef __MACROKEY_H_
#define __MACROKEY_H_
#include <Arduino.h>
#include <string>
#include "Printable.h"

template <uint8_t pin>
class MacroKey : public Printable {
private:
    static volatile bool buttonState;
    static volatile int buttonCount;
    static volatile bool buttonChanged;
    static volatile unsigned long button_time;  
    static volatile unsigned long last_button_time;
    static volatile uint8_t keycode;

public:
    // MacroKey(BleMacropad& pad): pad(pad) {}
    static void begin(uint8_t code)
    {
        buttonState - false;
        buttonCount = 0;
        buttonChanged = false;
        button_time = 0;
        last_button_time = 0;
        keycode = code;
        pinMode(pin, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(pin), pressed, FALLING);
        
    }   
    static void pressed()
    {
        button_time = millis();
        if (button_time - last_button_time > 250)
        {
            buttonCount++;
            buttonChanged = true;
            last_button_time = button_time;
        }

    }
    static int getCount()
    {
        return buttonCount;
    }
    static bool getState()
    {
        bool reading = digitalRead(pin);
        return !reading;
    }
    static bool getButtonChanged()
    {
        return buttonChanged;
    }

    std::string getStatus()
    {
        
        char buff[80];
        snprintf(buff, sizeof(buff), "%s #: %d", getState() ? "true" : "false", buttonCount);
        return std::string(buff);
    }

    virtual size_t printTo(Print& p) const
    {
        size_t n = 0;

        n += p.print(getState() ? "true" : "false");
        n += p.print(" Count: ");
        n += p.print(buttonCount, DEC);

        return n;
    }

    static uint8_t getKeycode() {
        return keycode;
    }
};
#endif