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


void KeyboardDisplay::showOverview(MacroButton *buttons[], size_t size)
{
    clearDisplay();
    setTextSize(1);
    setTextColor(SSD1306_WHITE);

    // println("Pin Code Count State");
    // 123 1234 12345 123456
    
    for (int i = 0; i < size; i++)
    {
        setCursor(0, i * 10 + 2);
        print(*buttons[i]);
    }
    
    display();   
}

void KeyboardDisplay::drawAlert(const char *message)
{
    clearDisplay();
    setTextSize(2);
    setTextColor(SSD1306_WHITE);
    // int16_t x1, y1;
    // uint16_t w, h;
    // getTextBounds(message, 2, 2, &x1, &y1, &w, &h);

    // // setCursor(x1 - w / 2, y1);

    // Serial.printf("x1 %d y1 %d w %d h %d\r\n", x1, y1, w, h);
    // Serial.printf("new: %d %d\r\n", 64 - (w / 2), 32 - (h / 2));
    // // int length = strlen(message);
    // // setCursor(64 - (length * 6), 2);

    // setCursor(64 - (w / 2), 32 - (h / 2));
    // print(message);
    drawCenterString(message, 2, 2);
    display();
}

void KeyboardDisplay::drawImage(const uint8_t *image, const int16_t w, const int16_t h)
{
    clearDisplay();
    drawXBitmap(64 - int(w/2), 32 - int(h/2), image, w, h, SSD1306_WHITE);
    display();
}

void KeyboardDisplay::drawCenterString(const char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    getTextBounds(buf, x, y, &x1, &y1, &w, &h);

    // Serial.printf("x1 %d y1 %d w %d h %d\r\n", x1, y1, w, h);
    // Serial.printf("new: %d %d\r\n", 64 - (w / 2), 32 - (h / 2));
    // int length = strlen(message);
    // setCursor(64 - (length * 6), 2);

    setCursor(64 - (w / 2), 32 - (h / 2));
    print(buf);
}

