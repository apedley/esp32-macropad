#include "KeyboardDisplay.h"

void KeyboardDisplay::init()
{
      begin(SSD1306_SWITCHCAPVCC, 0x3C);
      clearDisplay();
      
}


void KeyboardDisplay::showMacroButton(MacroButton &button, const int16_t y)
{
    clearDisplay();
    setTextSize(1);
    setTextColor(SSD1306_WHITE);
    setCursor(2, y);
    print(button);
    display();
}


void KeyboardDisplay::showOverview(MacroButton *buttons[], size_t size, bool bleConnected, long rotaryEncoderValue)
{
    clearDisplay();
    setTextSize(1);
    setTextColor(SSD1306_WHITE);

    setCursor(2, 2);
    printf("BLE: %s R: %d", bleConnected ? "Yes" : "No", rotaryEncoderValue);

    // setCursor(2, 20);
    // Pin Code Count State
    // println("Pin Code Count State");
    // 123 1234 12345 123456

    for (int i = 0; i < size; i++)
    {
        setCursor(2, (i + 1) * 10 + 2);
        print(*buttons[i]);
    }
    
    display();   
}

void KeyboardDisplay::drawAlert(const char *message)
{
    clearDisplay();
    setTextSize(2);
    setTextColor(SSD1306_WHITE);
    setCursor(2, 24);
    print(message);
    display();
}