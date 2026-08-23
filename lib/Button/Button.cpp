#include "Button.h"

Button::Button(uint8_t pin)
    : pin(pin)
{
}

void Button::begin()
{
    pinMode(pin, INPUT_PULLUP);
}
void Button::debounce()
{
    reading = digitalRead(pin);
    if (reading != lastReading)
    {
        lastDebounceTime = millis();
        lastReading = reading;
    }
}

bool Button::wasPressed()
{
    if (action)
    {
        action = false;
        if (currentState == LOW && lastState == HIGH)
        {
            return true;
        }
    }
    return false;
}

bool Button::isPressed()
{
    return currentState == LOW;
}

bool Button::longPressed()
{
    if (!longPressedEvent)
    {
        if (currentState == LOW && millis() - pressStartTime >= longPressTime)
        {
            longPressedEvent = true;
            return true;
        }
    }
    return false;
}

void Button::update()
{
    debounce();
    if (currentState == HIGH)
    {
        longPressedEvent = false;
    }
    if (millis() - lastDebounceTime >= timeDebounce)
    {
        if (currentState != reading)
        {
            lastState = currentState;
            currentState = reading;
            action = true;

            if (currentState == LOW)
            {
                pressStartTime = millis();
            }
        }
    }
}