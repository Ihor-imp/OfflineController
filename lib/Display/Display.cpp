
#include "Display.h"

Display::Display(const DisplayConfig &config)
    : config(config),
      display(config.width, config.height, &Wire, config.resetPin)
{
}

void Display::begin()
{
    Wire.begin();

    if (!display.begin(SSD1306_SWITCHCAPVCC, config.address))
    {
        pinMode(LED_BUILTIN, OUTPUT);

        while (true)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
        }
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("DISPLAY OK"));
    display.display();
}

void Display::printText(const __FlashStringHelper *text, uint16_t x, uint16_t y)
{
    display.setCursor(x, y);
    display.println(text);
}

void Display::off()
{
    display.ssd1306_command(SSD1306_DISPLAYOFF);
}

void Display::on()
{
    display.ssd1306_command(SSD1306_DISPLAYON);
}

void Display::clear()
{
    display.clearDisplay();
}

void Display::update()
{
    display.display();
}

void Display::printText(const char *text, uint16_t x, uint16_t y)
{
    display.setCursor(x, y);
    display.println(text);
}

void Display::printValue(const float value, uint16_t x, uint16_t y)
{
    display.setCursor(x, y);
    display.println(value);
}

void Display::fillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    display.fillRect(x, y, width, height, SSD1306_BLACK);
}
