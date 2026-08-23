#pragma once
#include <Arduino.h>

class Button
{
private:
    uint8_t pin;

    bool currentState = HIGH;
    bool lastState = HIGH;
    bool reading = HIGH;
    bool lastReading = HIGH;

    bool action = false;
    bool longPressedEvent = false;

    const uint8_t timeDebounce = 10;
    uint32_t lastDebounceTime = 0;

    uint32_t pressStartTime = 0;
    uint32_t longPressTime = 2000;

    void debounce();

public:
    Button(uint8_t pin);

    bool wasPressed();
    bool isPressed();
    bool longPressed();

    void update();
    void begin();
};