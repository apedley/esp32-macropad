#include <Arduino.h>
#include <Wire.h>
#include "Bounce2.h"
#include "KeyboardKnob.h"
#include "KeyboardDisplay.h"
#include "BleMacropad.h"
#include "MacroButton.h"
#include "Images.h"

#define DEFAULT_PERIOD 500

#define KEY_REPEAT_DELAY 3

#define KEY_1_PIN 23
#define KEY_2_PIN 5
#define KEY_3_PIN 25
#define KEY_4_PIN 17
#define KEY_5_PIN 16
#define KEY_6_PIN 4

#define KEY_1_CODE KEY_NUM_MINUS
#define KEY_2_CODE KEY_NUM_PLUS
#define KEY_3_CODE KEY_NUM_SLASH
#define KEY_4_CODE KEY_NUM_ASTERISK
#define KEY_5_CODE KEY_NUM_PERIOD
#define KEY_6_CODE KEY_F13

#define ROTARY_CLOCK_PIN 19
#define ROTARY_DATA_PIN 18

BleMacropad bleMacropad;

KeyboardDisplay disp(128, 64, &Wire, -1);

MacroButton buttonOne = MacroButton(KEY_1_PIN, KEY_1_CODE, 25, "-");
MacroButton buttonTwo = MacroButton(KEY_2_PIN, KEY_2_CODE, 25, "+");
MacroButton buttonThree = MacroButton(KEY_3_PIN, KEY_3_CODE, 25, "/");
MacroButton buttonFour = MacroButton(KEY_4_PIN, KEY_4_CODE, 25, "*");
MacroButton buttonFive = MacroButton(KEY_5_PIN, KEY_5_CODE, 25, ".");
MacroButton buttonSix = MacroButton(KEY_6_PIN, KEY_6_CODE, 25, "F13");

MacroButton *buttons[] = {&buttonOne, &buttonTwo, &buttonThree, &buttonFour, &buttonFive, &buttonSix};

uint8_t buttonsCount = 6;

int64_t rotaryEncoderValue = 0;
KeyboardKnob knob(ROTARY_DATA_PIN, ROTARY_CLOCK_PIN);

bool showAlert = false;
long lastAlertTime = 0;

long timeNow = 0;


// cppcheck-suppress unusedFunction
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up...");

  disp.init();

  bleMacropad.begin();

  knob.begin();
  
  for (MacroButton *button : buttons)
  {
    button->begin();
  }
}

// cppcheck-suppress unusedFunction
void loop()
{
  bool connected = bleMacropad.isConnected();

  if (!connected) {
    disp.drawImage(bluetooth_bits, icon_width, icon_height);
    return;
  }

  char alertMessage[80];

  int knobChange = knob.update();

  if (knobChange != 0) {
    rotaryEncoderValue = knob.getValue();

    if (knobChange > 0) {
      bleMacropad.write(KEY_MEDIA_VOLUME_UP);
      disp.drawImage(volume_up_bits, icon_width, icon_height);
    } else {
      bleMacropad.write(KEY_MEDIA_VOLUME_DOWN);
      disp.drawImage(volume_down_bits, icon_width, icon_height);
    }

    
    if (!showAlert) {
      showAlert = true;
      lastAlertTime = millis();
    }
  }

  for (MacroButton *button : buttons)
  {
    if (button->update())
    {
      uint8_t keycode = button->getKeycode();
      snprintf(alertMessage, 80, "Send %s", button->getName());
      disp.drawAlert(alertMessage);

      bleMacropad.write(keycode);

      if (!showAlert) {
        showAlert = true;
        lastAlertTime = millis();
      }
    }
  }

  if (showAlert) {
    if (millis() - lastAlertTime > 1000) {
      showAlert = false;
    }
  } else {
    disp.showOverview(buttons, buttonsCount);
  }

  if (millis() - timeNow > DEFAULT_PERIOD) {
    timeNow = millis();
  }
  
}
