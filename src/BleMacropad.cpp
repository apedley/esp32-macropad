#include "BleMacropad.h"
#include <Arduino.h>

void BleMacropad::volup()
{
    if (isConnected()) {
        write(KEY_MEDIA_VOLUME_UP);
    }
}

void BleMacropad::voldown()
{
}
