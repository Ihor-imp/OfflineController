#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

struct DisplayConfig
{
    uint8_t address;
    uint8_t width;
    uint8_t height;
    int8_t resetPin;
};

class Display
{
private:
    DisplayConfig config;
    Adafruit_SSD1306 display;

public:
    Display(const DisplayConfig &config);
    void begin();
    void update();
    void clear();

    void on();
    void off();

    void printText(const char *text, uint16_t x, uint16_t y);
    void printValue(const uint16_t value, uint16_t x, uint16_t y);
    void fillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
};