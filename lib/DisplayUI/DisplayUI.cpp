
#include "DisplayUI.h"

DisplayUI::DisplayUI(Display &display, Machine &machine)
    : display(display), machine(machine)
{
}

void DisplayUI::drawPositionX()
{
    display.on();
    display.fillRect(13, 0, 45, 8);
    display.printValue(machine.getPositionX(), 13, 0);
    display.update();
}

void DisplayUI::drawPositionY()
{
    display.on();
    display.fillRect(13, 10, 45, 8);
    display.printValue(machine.getPositionY(), 13, 10);
    display.update();
}

void DisplayUI::drawPositionZ()
{
    display.on();
    display.fillRect(13, 20, 45, 8);
    display.printValue(machine.getPositionZ(), 13, 20);
    display.update();
}

void DisplayUI::drawDirection()
{
    display.on();
    display.fillRect(110, 0, 20, 8);

    if (machine.getDirection() == Direction::PLUS)
    {
        display.printText(F("+"), 120, 0);
    }
    else
    {
        display.printText(F("-"), 120, 0);
    }

    display.update();
}

void DisplayUI::drawStepValue()
{
    display.fillRect(10, 50, 40, 10);
    display.printValue(machine.getStep(), 10, 50);
    display.update();
}

void DisplayUI::drawSpeedValue()
{
    display.fillRect(55, 0, 40, 40);
    display.printValue(machine.getSpeed(), 55, 0);
    display.update();
}

void DisplayUI::drawSetting()
{
    display.clear();

    display.printText(F(">"), 0, 0);
    display.printText(F("Step"), 10, 0);
    display.printText(F("Speed"), 10, 10);

    display.update();
}

void DisplayUI::drawStepAndSpeed()
{
    display.printText(F("STEP: "), 0, 55);
    display.printValue(machine.getStep(), 30, 55);

    display.printText(F("SPEED: "), 65, 55);
    display.printValue(machine.getSpeed(), 100, 55);
}

void DisplayUI::drawMenu()
{
    display.clear();

    display.printText(F(">"), 0, menuPosition * 10);
    display.printText(F("Setting"), 10, 0);
    display.printText(F("Zero Z"), 10, 10);
    display.printText(F("Zero X"), 10, 20);
    display.printText(F("Zero Y"), 10, 30);
    display.printText(F("Home"), 10, 40);

    display.update();
}

void DisplayUI::drawMain()
{
    display.clear();

    display.printText(F("X: "), 0, 0);
    display.printText(F("Y: "), 0, 10);
    display.printText(F("Z: "), 0, 20);
    display.printText(F("+"), 120, 0);

    drawStepAndSpeed();

    display.update();
}

void DisplayUI::drawStep()
{
    display.clear();

    stepCursorPosition = machine.getStepPosition();

    for (uint8_t j = 20; j < 128; j += 23)
    {
        for (uint8_t i = 10; i < 50; i += 8)
        {
            display.printText(F("|"), j, i);
        }
    }

    display.printText(F("100"), 25, 10);
    display.printText(F("10"), 51, 10);
    display.printText(F("1"), 77, 10);
    display.printText(F("0.1"), 95, 10);

    display.printText(F("|"), 32 + (stepCursorPosition * 23), 0);

    display.printValue(machine.getStep(), 10, 50);

    display.update();
}

void DisplayUI::drawSpeed()
{
    display.clear();

    speedCursorPosition = machine.getSpeedPosition();

    display.printText(F("SPEED: "), 10, 0);
    display.printValue(machine.getSpeed(), 55, 0);
    display.printText(F(">"), 0, 10);

    display.printValue(1000, 10, 10);
    display.printValue(700, 10, 20);
    display.printValue(500, 10, 30);
    display.printValue(350, 10, 40);
    display.printValue(100, 10, 50);

    display.update();
}

void DisplayUI::drawConfirmWindow(const char *message)
{
    display.clear();

    display.printText(message, 40, 10);
    display.printText(F("Confirm?"), 45, 20);
    display.printText(F("X: NO    Z: YES"), 20, 40);

    display.update();
}

uint8_t DisplayUI::moveCursorDown(uint8_t index, uint8_t maxIndex, uint8_t startY, uint8_t stepY)
{
    display.fillRect(0, startY + (index * stepY), 10, 10);

    if (index < maxIndex)
    {
        index++;
    }
    else
    {
        index = 0;
    }

    display.printText(F(">"), 0, startY + (index * stepY));

    display.update();
    return index;
}

uint8_t DisplayUI::moveCursorUp(uint8_t index, uint8_t maxIndex, uint8_t startY, uint8_t stepY)
{
    display.fillRect(0, startY + (index * stepY), 10, 10);

    if (index > 0)
    {
        index--;
    }
    else
    {
        index = maxIndex;
    }

    display.printText(F(">"), 0, startY + (index * stepY));

    display.update();
    return index;
}

uint8_t DisplayUI::moveCursorRight(uint8_t index, uint8_t maxIndex, uint8_t startX, uint8_t stepX, uint8_t y)
{
    display.fillRect(startX + (index * stepX), y, 10, 10);

    if (index < maxIndex)
    {
        index++;
    }
    else
    {
        index = 0;
    }

    display.printText(F("|"), startX + (index * stepX), y);

    display.update();
    return index;
}

void DisplayUI::moveMenuCursorDown()
{
    menuPosition = moveCursorDown(menuPosition, 4, 0, 10);
}

void DisplayUI::moveMenuCursorUp()
{
    menuPosition = moveCursorUp(menuPosition, 4, 0, 10);
}

void DisplayUI::moveSettingCursorDown()
{
    settingPosition = moveCursorDown(settingPosition, 1, 0, 10);
}

void DisplayUI::moveSettingCursorUp()
{
    settingPosition = moveCursorUp(settingPosition, 1, 0, 10);
}

void DisplayUI::moveStepCursorRight()
{
    stepCursorPosition = moveCursorRight(stepCursorPosition, 3, 32, 23, 0);
}

void DisplayUI::moveSpeedCursorDown()
{
    speedCursorPosition = moveCursorDown(speedCursorPosition, 4, 10, 10);
}

//-----------------------------------------------------------------
// Getters

uint8_t DisplayUI::getMenuPosition() const
{
    return menuPosition;
}

uint8_t DisplayUI::getSettingPosition() const
{
    return settingPosition;
}

uint8_t DisplayUI::getSpeedCursorPosition() const
{
    return speedCursorPosition;
}

uint8_t DisplayUI::getStepCursorPosition() const
{
    return stepCursorPosition;
}
