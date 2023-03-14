#include "KeyboardDisplay.h"

void KeyboardDisplay::init()
{
      begin(SSD1306_SWITCHCAPVCC, 0x3C);
      clearDisplay();
    }

void KeyboardDisplay::test(const char *val)
{
    clearDisplay();
    setTextSize(1);
    setTextColor(SSD1306_WHITE);
    setCursor(30, 30);
    print(val);
    display();
}

void KeyboardDisplay::showStatus(bool bleConnected, const char * keyOne, const char * keyTwo, long knobValue)
{
    clearDisplay();
    setTextSize(1);
    setTextColor(SSD1306_WHITE);
    setCursor(2, 5);
    std::string val = "Connected: ";

    if (bleConnected) {
        val += "Yes";
    } else {
        val += "No";
    }

    print(val.c_str());

    setCursor(2, 20);

    printf("%s", keyOne);

    setCursor(2, 35);

    printf("%s", keyTwo);

    std::string knob = "Knob:";

    setCursor(2, 50);

    printf("%s %d", knob.c_str(), knobValue);

    display();
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

void KeyboardDisplay::showMacroButtonsOverview(MacroButton *buttons[], size_t size)
{
    clearDisplay();
    setTextSize(1);
    setTextColor(SSD1306_WHITE);

    setCursor(2, 2);
    // Pin Code Count State
    // 123 1234 12345 123456
    println("Pin Code Count State");

    for (int i = 0; i < size; i++)
    {
        setCursor(2, (i + 1) * 12 + 2);
        print(*buttons[i]);
    }
    
    display();
}
