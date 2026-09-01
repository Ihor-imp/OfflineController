#include "DisplayUI.h"

DisplayUI::DisplayUI(Display &display, Machine &machine)
    : display(display), machine(machine)
{
}

void DisplayUI::drawPositionX()
{
    display.on();
    display.fillRect(13, 0, 35, 8);
    display.printValue(machine.getPositionX(), 13, 0);
    display.update();
}

void DisplayUI::drawPositionY()
{
    display.on();
    display.fillRect(13, 10, 35, 8);
    display.printValue(machine.getPositionY(), 13, 10);
    display.update();
}

void DisplayUI::drawPositionZ()
{
    display.on();
    display.fillRect(13, 20, 35, 8);
    display.printValue(machine.getPositionZ(), 13, 20);
    display.update();
}

void DisplayUI::drawDirection()
{
    display.on();
    display.fillRect(110, 0, 20, 8);
    if (machine.getDirection() == Direction::PLUS)
    {
        display.printText("+", 120, 0);
    }
    else
    {
        display.printText("-", 120, 0);
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
    display.printText(">", 0, 0);
    display.printText("Step", 10, 0);
    display.printText("Speed", 10, 10);

    display.update();
}

void DisplayUI::drawStepAndSpeed()
{
    display.printText("STEP: ", 0, 55);
    display.printValue(machine.getStep(), 30, 55);

    display.printText("SPEED: ", 65, 55);
    display.printValue(machine.getSpeed(), 100, 55);
}

void DisplayUI::drawMenu()
{
    display.clear();
    display.printText(">", 0, 0);
    display.printText("Setting", 10, 0);
    display.printText("Zero Z", 10, 10);
    display.printText("Zero X", 10, 20);
    display.printText("Zero Y", 10, 30);
    display.printText("Home", 10, 40);

    display.update();
}

void DisplayUI::drawMain()
{
    display.clear();
    display.printText("X: ", 0, 0);
    display.printText("Y: ", 0, 10);
    display.printText("Z: ", 0, 20);
    display.printText("+", 120, 0);
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
            display.printText("|", j, i);
        }
    }

    display.printText("100", 25, 10);
    display.printText("10", 51, 10);
    display.printText("1", 77, 10);
    display.printText("0.1", 95, 10);

    display.printText("|", 32 + (stepCursorPosition * 23), 0);

    display.printValue(machine.getStep(), 10, 50);

    display.update();
}

void DisplayUI::drawSpeed()
{
    display.clear();

    speedCursorPosition = machine.getSpeedPosition();

    display.printText("SPEED: ", 10, 0);
    display.printValue(machine.getSpeed(), 55, 0);
    display.printText(">", 0, 10);

    display.printValue(1000, 10, 10);
    display.printValue(700, 10, 20);
    display.printValue(500, 10, 30);
    display.printValue(350, 10, 40);
    display.printValue(100, 10, 50);

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
    display.printText(">", 0, startY + (index * stepY));

    display.update();
    return index;
}
uint8_t DisplayUI::moveCursorUp(uint8_t index, uint8_t maxIndex, uint8_t startY, uint8_t stepY = 10)
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

    display.printText(">", 0, startY + (index * stepY));
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

    display.printText("|", startX + (index * stepX), y);
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

void DisplayUI::moveAxisCursorDown()
{
    axisPosition = moveCursorDown(axisPosition, 2, 20, 10);
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
// Geter-s

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
