#include <Arduino.h>
#include <BleKeyboard.h>
#include <Wire.h>
#include "Bounce2.h"
#include "AiEsp32RotaryEncoder.h"
#include "KeyboardDisplay.h"
#include "BleMacropad.h"
#include "MacroButton.h"
#define DEFAULT_PERIOD 80

#define KEY_1_PIN 15
#define KEY_2_PIN 21
#define KEY_3_PIN 34

#define KEY_1_CODE 0xCE // PrintScreen
#define KEY_2_CODE 0xF0 // F13
#define KEY_3_CODE 0xF1 // F14

// #define CLK_PIN 6
// #define DT_PIN 7
// #define SW_PIN 34

// #define ROTARY_ENCODER_A_PIN 6
// #define ROTARY_ENCODER_B_PIN 7
// #define ROTARY_ENCODER_BUTTON_PIN 34
// #define ROTARY_ENCODER_VCC_PIN 36
// #define ROTARY_ENCODER_VCC_PIN -1 /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

// depending on your encoder - try 1,2 or 4 to get expected behaviour
// #define ROTARY_ENCODER_STEPS 1
// #define ROTARY_ENCODER_STEPS 2
// #define ROTARY_ENCODER_STEPS 4

// AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
unsigned long time_now = 0;

BleMacropad bleMacropad;

KeyboardDisplay disp(128, 64, &Wire, -1);




MacroButton buttonOne = MacroButton(KEY_1_PIN, KEY_1_CODE, 25);
MacroButton twoButton = MacroButton(21, KEY_2_CODE, 25);
MacroButton buttonThree = MacroButton(KEY_3_PIN, KEY_3_CODE, 25);
MacroButton *buttons[] = {&buttonOne, &twoButton, &buttonThree};


// void rotary_onButtonClick()
// {
//   static unsigned long lastTimePressed = 0;
//   // ignore multiple press in that time milliseconds
//   if (millis() - lastTimePressed < 500)
//   {
//     return;
//   }
//   lastTimePressed = millis();
//   Serial.print("button pressed ");
//   Serial.print(millis());
//   Serial.println(" milliseconds after restart");
// }

// void rotary_loop()
// {
//   if (rotaryEncoder.encoderChanged())
//   {
//     Serial.println(rotaryEncoder.readEncoder());
//   }
//   if (rotaryEncoder.isEncoderButtonClicked())
//   {
//     Serial.println("button pressed");
//   }
// }

// void IRAM_ATTR readEncoderISR()
// {
//   rotaryEncoder.readEncoder_ISR();
// }

void setup()
{

//   pinMode(ROTARY_ENCODER_A_PIN, INPUT_PULLUP);
//   pinMode(ROTARY_ENCODER_B_PIN, INPUT_PULLUP);
  Serial.begin(9600);

  disp.init();

  bleMacropad.begin();


  // rotaryEncoder.begin();
  // rotaryEncoder.setup(readEncoderISR);
  // rotaryEncoder.setBoundaries(0, 1000, false); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  // rotaryEncoder.setAcceleration(250);


  buttonOne.begin();
  twoButton.begin();
  buttonThree.begin();
}


void loop()
{
  buttonOne.update();
  twoButton.update();
  buttonThree.update();


  if (millis() - time_now > DEFAULT_PERIOD)
  {

    time_now = millis();

    bool connected = bleMacropad.isConnected();
    char status_buff[80];

    disp.showMacroButtonsOverview(buttons, 3);

    bleMacropad.volup();

    // rotary_loop();
  }
}
