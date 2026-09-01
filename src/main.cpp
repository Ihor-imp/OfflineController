#include "Button.h"
#include "Display.h"
#include "Machine.h"

Machine machine;

Button buttonX(3);
Button buttonY(4);
Button buttonZ(5);
Button buttonSTOP(6);
Button buttonPLUS_MINUS(2);

DisplayConfig displayConfig = {
    0x3C,
    128,
    64,
    -1};

Display display(displayConfig);

uint32_t countSleep = 0;
uint32_t timeSleep = 100000;

uint8_t menuPosition = 0;

uint8_t settingPosition = 0;

enum class Screen
{
    MAIN,
    MENU,
    SETTING
};

enum class SettingPage
{
    MENU,
    STEP,
    SPEED,
};

uint8_t axisPosition = 0;

uint8_t stepCursorPosition = 0;
uint8_t speedCursorPosition = 0;

Screen screen = Screen::MAIN;
SettingPage settingPage = SettingPage::MENU;

void drawStepAndSpeed()
{
    display.printText("STEP: ", 0, 55);
    display.printValue(machine.getStep(), 30, 55);

    display.printText("SPEED: ", 65, 55);
    display.printValue(machine.getSpeed(), 100, 55);

    display.update();
}

void drawSetting()
{
    display.clear();
    display.printText(">", 0, 0);
    display.printText("Step", 10, 0);
    display.printText("Speed", 10, 10);

    display.update();
}

void drawMenu()
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

void drawMain()
{
    display.clear();
    display.printText("X: ", 0, 0);
    display.printText("Y: ", 0, 10);
    display.printText("Z: ", 0, 20);
    display.printText("+", 120, 0);
    drawStepAndSpeed();

    display.update();
}

void drawStep()
{
    display.clear();
    display.printText(">", 0, 20);
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

    display.printText("X: ", 10, 20);
    display.printText("Y: ", 10, 30);
    display.printText("Z: ", 10, 40);

    uint8_t currentPos = machine.getStepPosition();
    display.printText("|", 32 + (currentPos * 23), 0);

    display.printValue(machine.getStep(), 10, 50);

    display.update();
}

void drawSpeed()
{
    display.clear();
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

uint8_t moveCursorDown(uint8_t index, uint8_t maxIndex, uint8_t startY, uint8_t stepY)
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
uint8_t moveCursorUp(uint8_t index, uint8_t maxIndex, uint8_t startY, uint8_t stepY = 10)
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

uint8_t moveCursorRight(uint8_t index, uint8_t maxIndex, uint8_t startX, uint8_t stepX, uint8_t y)
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

void updateButtons()
{
    buttonX.update();
    buttonY.update();
    buttonZ.update();
    buttonSTOP.update();
    buttonPLUS_MINUS.update();
}

void handleMain()
{
    if (buttonPLUS_MINUS.longPressed())
    {
        screen = Screen::MENU;
        drawMenu();
        return;
    }
    if (millis() - countSleep >= timeSleep)
    {
        display.off();
    }

    if (buttonX.wasPressed())
    {
        display.on();
        machine.workButtonX();

        display.fillRect(13, 0, 35, 8);
        display.printValue(machine.getPositionX(), 13, 0);
        display.update();
        countSleep = millis();
    }

    if (buttonY.wasPressed())
    {
        display.on();
        machine.workButtonY();
        display.fillRect(13, 10, 35, 8);
        display.printValue(machine.getPositionY(), 13, 10);
        display.update();
        countSleep = millis();
    }

    if (buttonZ.wasPressed())
    {
        display.on();
        machine.workButtonZ();
        display.fillRect(13, 20, 35, 8);
        display.printValue(machine.getPositionZ(), 13, 20);
        display.update();
        countSleep = millis();
    }

    if (buttonPLUS_MINUS.wasPressed())
    {
        display.on();
        machine.workButtonPlusOrMinus();

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
        countSleep = millis();
    }
}

void handleMenu()
{
    if (buttonX.wasPressed())
    {
        menuPosition = moveCursorDown(menuPosition, 4, 0, 10);
    }

    if (buttonY.wasPressed())
    {
        menuPosition = moveCursorUp(menuPosition, 4, 0, 10);
    }

    if (buttonZ.wasPressed())
    {
        switch (menuPosition)
        {
        case 0:
            drawSetting();
            screen = Screen::SETTING;
            break;

        case 1:
            display.clear();
            // Z
            break;
        case 2:
            display.clear();
            // X
            break;
        case 3:
            display.clear();
            // Y
            break;
        case 4:
            display.clear();
            // HOME
            break;
        default:
            break;
        }
    }
    if (buttonPLUS_MINUS.wasPressed())
    {
        screen = Screen::MAIN;
        drawMain();
    }
}

void handleSetting()
{
    switch (settingPage)
    {
    case SettingPage::MENU:
        if (buttonX.wasPressed())
        {
            settingPosition = moveCursorDown(settingPosition, 1, 0, 10);
        }

        if (buttonY.wasPressed())
        {
            settingPosition = moveCursorUp(settingPosition, 1, 0, 10);
        }

        if (buttonZ.wasPressed())
        {
            switch (settingPosition)
            {
            case 0:
                settingPage = SettingPage::STEP;
                drawStep();
                break;

            case 1:
                settingPage = SettingPage::SPEED;
                drawSpeed();
                break;
            default:
                break;
            }
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            screen = Screen::MENU;
            drawMenu();
        }
        break;

    case SettingPage::STEP:
        if (buttonX.wasPressed())
        {
            axisPosition = moveCursorDown(axisPosition, 2, 20, 10);
        }

        if (buttonY.wasPressed())
        {
            stepCursorPosition = moveCursorRight(stepCursorPosition, 3, 32, 23, 0);
        }
        if (buttonZ.wasPressed())
        {
            machine.setStepPosition(stepCursorPosition);

            display.fillRect(10, 50, 40, 10);
            display.printValue(machine.getStep(), 10, 50);
            display.update();
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            settingPage = SettingPage::MENU;
            drawSetting();
        }
        break;
    case SettingPage::SPEED:
        if (buttonX.wasPressed())
        {
            uint8_t newPos = moveCursorDown(machine.getSpeedPosition(), 4, 10, 10);
            machine.setSpeedPosition(newPos);
        }

        if (buttonX.wasPressed())
        {
            speedCursorPosition = moveCursorDown(speedCursorPosition, 4, 10, 10);
        }

        if (buttonZ.wasPressed())
        {
            machine.setSpeedPosition(speedCursorPosition);
            display.fillRect(55, 0, 40, 40);
            display.printValue(machine.getSpeed(), 55, 0);

            display.update();
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            settingPage = SettingPage::MENU;
            drawSetting();
        }
        break;
    default:
        break;
    }
}

void handleScreen()
{
    switch (screen)
    {
    case Screen::MAIN:
        handleMain();
        break;
    case Screen::MENU:
        handleMenu();
        break;
    case Screen::SETTING:
        handleSetting();
        break;
    }
}

void setup()
{
    Serial.begin(9600);
    buttonX.begin();
    buttonY.begin();
    buttonZ.begin();
    buttonSTOP.begin();
    buttonPLUS_MINUS.begin();
    display.begin();
    display.printText("X: ", 0, 0);
    display.printText("Y: ", 0, 10);
    display.printText("Z: ", 0, 20);
    display.printText("+", 120, 0);

    drawStepAndSpeed();

    display.update();
    countSleep = millis();
}

void loop()
{
    updateButtons();
    handleScreen();
}