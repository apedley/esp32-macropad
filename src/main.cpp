#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "Bounce2.h"
#include "KeyboardKnob.h"
#include "KeyboardDisplay.h"
#include "BleMacropad.h"
#include "MacroButton.h"
#include "Images.h"

#define DEFAULT_PERIOD 50

#define KEY_1_PIN 15
#define KEY_2_PIN 21
#define KEY_3_PIN 34

// #define KEY_1_CODE 0xCE // PrintScreen
// #define KEY_1_CODE KEY_MEDIA_VOLUME_DOWN
#define KEY_1_CODE KEY_NUM_MINUS
#define KEY_2_CODE KEY_NUM_PLUS
#define KEY_3_CODE KEY_NUM_SLASH
// #define KEY_2_CODE 0xF1 // F14
// #define KEY_2_CODE KEY_MEDIA_VOLUME_UP
// #define KEY_3_CODE 0xF2 // F13
// #define KEY_3_CODE KEY_MEDIA_VOLUME_MUTE

#define ROTARY_DATA_PIN 7
#define ROTARY_CLOCK_PIN 6

BleMacropad bleMacropad;

// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 9, /* data=*/ 8, /* reset=*/ U8X8_PIN_NONE);
KeyboardDisplay disp(128, 64, &Wire, -1);

MacroButton buttonOne = MacroButton(KEY_1_PIN, KEY_1_CODE, 25, "-");
MacroButton buttonTwo = MacroButton(KEY_2_PIN, KEY_2_CODE, 25, "+");
MacroButton buttonThree = MacroButton(KEY_3_PIN, KEY_3_CODE, 25, "/");

MacroButton *buttons[] = {&buttonOne, &buttonTwo, &buttonThree};
uint8_t buttonsCount = 3;

int64_t rotaryEncoderValue = 0;
KeyboardKnob knob(ROTARY_DATA_PIN, ROTARY_CLOCK_PIN);

unsigned long time_now = 0;

bool showAlert = false;
long lastAlertTime = 0;

void setup()
{

  Serial.begin(9600);

  disp.init();

  bleMacropad.begin();

  knob.begin();
  
  for (MacroButton *button : buttons)
  {
    button->begin();
  }

}


void loop()
{
  bool connected = bleMacropad.isConnected();
  
  // rotaryEncoderValue = encoder.getCount() / 2;

  if (knob.update()) {
    rotaryEncoderValue = knob.getValue();
  }

  char keyMessage[80];

  for (MacroButton *button : buttons)
  {
    if (button->update())
    {
      if (connected) {
        uint8_t keycode = button->getKeycode();
        Serial.printf("Sending Key.. %d\n", button->getName());
        snprintf(keyMessage, 80, "Send %s", button->getName());
        bleMacropad.write(keycode);

        if (!showAlert) {//+-+-+-+++-+-
          showAlert = true;
          lastAlertTime = millis();
        }
      }
    }
  }

  if (showAlert) {
    if (millis() - lastAlertTime > 1000) {
      showAlert = false;
    }

    disp.drawAlert(keyMessage);
  } else {
      disp.showOverview(buttons, buttonsCount, connected, rotaryEncoderValue);
  }


  if (millis() - time_now > DEFAULT_PERIOD)
  {

    time_now = millis();
    // Serial.println(rotaryEncoderValue);
  }
}
