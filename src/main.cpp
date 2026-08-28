#include "Button.h"
#include "Display.h"

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

float positionX = 0;
float positionY = 0;
float positionZ = 0;

uint32_t countSleep = 0;
uint32_t timeSleep = 100000;

uint8_t menuPosition = 0;

float stepValue = 0;
uint8_t settingPosition = 0;

float step = 0;

bool minus = false;

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

uint8_t stepPosition = 2;
uint8_t axisPosition = 1;

uint8_t speedPosition = 0;
uint16_t speed = 0;

Screen screen = Screen::MAIN;
SettingPage settingPage = SettingPage::MENU;

float stepValues[] = {100, 10, 1, 0.1};

uint16_t speedValue[] = {1000, 700, 500, 350, 100};

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
    display.printText("+/-", 110, 0);
    display.update();
    countSleep = millis();
}

void workButtonX()
{
    display.on();
    display.printText("X: ", 0, 0);
    if (!minus)
    {
        positionX += step;
    }
    else
    {
        positionX -= step;
    }

    display.fillRect(13, 0, 35, 8);
    display.printValue(positionX, 13, 0);
    display.update();
    countSleep = millis();
}

void workButtonY()
{
    display.on();
    display.printText("Y: ", 0, 10);
    if (!minus)
    {
        positionY += step;
    }
    else
    {
        positionY -= step;
    }

    display.fillRect(13, 10, 35, 8);
    display.printValue(positionY, 13, 10);
    display.update();
    countSleep = millis();
}

void workButtonZ()
{
    display.on();
    display.printText("Z: ", 0, 20);
    if (!minus)
    {
        positionZ += step;
    }
    else
    {
        positionZ -= step;
    }

    display.fillRect(13, 20, 35, 8);
    display.printValue(positionZ, 13, 20);
    display.update();
    countSleep = millis();
}

void workButtonPlusOrMinus()
{
    display.on();
    minus = !minus;

    if (minus)
    {
        display.fillRect(110, 0, 20, 8);
        display.printText("-", 120, 0);
    }
    else
    {
        display.fillRect(110, 0, 20, 8);
        display.printText("+", 120, 0);
    }
    countSleep = millis();
    display.update();
}

void workButtonStop()
{
    // STOP ALL MOVE
}

void drawStepAndSpeed()
{
    display.printText("STEP: ", 0, 55);
    display.printValue(step, 30, 55);

    display.printText("SPEED: ", 65, 55);
    display.printValue(speed, 100, 55);
}

void drawSetting()
{
    display.clear();
    display.printText(">", 0, 0);
    display.printText("Step", 10, 0);
    display.printText("Speed", 10, 10);
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
}

void drawMain()
{
    display.clear();
    display.printText("X: ", 0, 0);
    display.printText("Y: ", 0, 10);
    display.printText("Z: ", 0, 20);
    display.printText("+/-", 110, 0);
    drawStepAndSpeed();
}

void drawStep()
{
    display.clear();
    for (uint8_t j = 25; j < 128; j += 23)
    {
        for (uint8_t i = 10; i < 50; i += 8)
        {
            display.printText("|", j, i);
        }
    }

    display.printText("100", 30, 10);
    display.printText("10", 55, 10);
    display.printText("1", 82, 10);
    display.printText("0.1", 100, 10);

    display.printText("X: ", 10, 20);
    display.printText("Y: ", 10, 30);
    display.printText("Z: ", 10, 40);
}

void drawSpeed()
{
    display.clear();
    display.printText("SPEED: ", 10, 0);
    display.printValue(speed, 55, 0);

    display.printValue(1000, 10, 10);
    display.printValue(700, 10, 20);
    display.printValue(500, 10, 30);
    display.printValue(350, 10, 40);
    display.printValue(100, 10, 50);
}

uint8_t moveCursorDown(uint8_t position, uint8_t minPosition, uint8_t maxPosition)
{
    display.fillRect(0, position * 10, 10, 10);
    if (position < maxPosition)
    {
        position++;
    }
    else
    {
        position = minPosition;
    }
    display.printText(">", 0, position * 10);

    return position;
}

uint8_t moveCursorUp(uint8_t position, uint8_t minPosition, uint8_t maxPosition)
{
    display.fillRect(0, position * 10, 10, 10);
    if (position > minPosition)
    {
        position--;
    }
    else
    {
        position = maxPosition;
    }
    display.printText(">", 0, position * 10);

    return position;
}

uint8_t moveCursorRight(uint8_t position, uint8_t minPosition, uint8_t maxPosition)
{
    display.fillRect(position * 20, 0, 10, 10);

    if (position < maxPosition)
    {
        position++;
    }
    else
    {
        position = minPosition;
    }

    display.printText("|", position * 20, 0);

    return position;
}

void loop()
{
    buttonX.update();
    buttonY.update();
    buttonZ.update();
    buttonSTOP.update();
    buttonPLUS_MINUS.update();

    if (buttonPLUS_MINUS.longPressed())
    {
        screen = Screen::MENU;
        drawMenu();
    }
    if (screen == Screen::MENU)
    {
        if (buttonX.wasPressed())
        {
            menuPosition = moveCursorDown(menuPosition, 0, 4);
        }

        if (buttonY.wasPressed())
        {
            menuPosition = moveCursorUp(menuPosition, 0, 4);
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
    if (screen == Screen::MAIN)
    {
        if (millis() - countSleep >= timeSleep)
        {
            display.off();
        }

        if (buttonX.wasPressed())
        {
            workButtonX();
        }

        if (buttonY.wasPressed())
        {
            workButtonY();
        }

        if (buttonZ.wasPressed())
        {
            workButtonZ();
        }

        if (buttonPLUS_MINUS.wasPressed())
        {
            workButtonPlusOrMinus();
        }

        drawStepAndSpeed();
    }

    if (screen == Screen::SETTING)
    {
        if (settingPage == SettingPage::MENU)
        {
            if (buttonX.wasPressed())
            {
                settingPosition = moveCursorDown(settingPosition, 0, 1);
            }

            if (buttonY.wasPressed())
            {
                settingPosition = moveCursorUp(settingPosition, 0, 1);
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
        }
    }

    if (settingPage == SettingPage::STEP)
    {
        if (buttonX.wasPressed())
        {
            axisPosition = moveCursorDown(axisPosition, 2, 4);
        }

        if (buttonY.wasPressed())
        {
            stepPosition = moveCursorRight(stepPosition, 2, 5);
        }
        if (buttonZ.wasPressed())
        {
            if (stepPosition >= 2 && stepPosition <= 5)
            {
                step = stepValues[stepPosition - 2];

                Serial.print("stepPosition = ");
                Serial.println(stepPosition);

                Serial.print("step = ");
                Serial.println(step);
                display.printValue(step, 10, 50);
            }
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            settingPage = SettingPage::MENU;
            drawSetting();
        }
    }

    if (settingPage == SettingPage::SPEED)
    {
        if (buttonX.wasPressed())
        {
            speedPosition = moveCursorDown(speedPosition, 1, 5);
        }
        if (buttonZ.wasPressed())
        {
            if (speedPosition >= 1 && speedPosition <= 5)
            {
                speed = speedValue[speedPosition - 1];
                display.fillRect(55, 0, 40, 40);
                display.printValue(speed, 55, 0);
            }
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            settingPage = SettingPage::MENU;
            drawSetting();
        }
    }
    display.update();
}