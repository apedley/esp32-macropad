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

  attachHalfQuad(7, 6);
  setCount(_value);
  setFilter(1023);
}

bool KeyboardKnob::update()
{
  int64_t newValue = getCount() / 2;
  bool changed = newValue == _value;
  _value = newValue;
  return changed;
}
