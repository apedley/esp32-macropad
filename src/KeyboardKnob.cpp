#include <Arduino.h>
#include "KeyboardKnob.h"

KeyboardKnob::KeyboardKnob(int data, int clock) : ESP32Encoder()
{
  _dataPin = data;
  _clockPin = clock;
}

void KeyboardKnob::begin()
{
  _value = 0;

  attachHalfQuad(_dataPin, _clockPin);
  setCount(_value);
  setFilter(1023);
}

int KeyboardKnob::update()
{
  int64_t newValue = getCount() / 2;
  int changed =  newValue - _value;
  _value = newValue;
  return changed;
}
