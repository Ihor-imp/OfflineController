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
    FEED
};

uint8_t stepPosition = 2;
uint8_t axisPosition = 1;

Screen screen = Screen::MAIN;
SettingPage settingPage = SettingPage::MENU;

float stepValues[] = {100, 10, 1, 0.1};

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

void stepMove()
{
    display.printText("STEP: ", 0, 55);
    display.printValue(step, 35, 55);
}

void drawSetting()
{
    display.clear();
    display.printText("Step", 10, 0);
    display.printText("Speed", 10, 10);
    display.printText("Feed", 10, 20);

    display.printText("Back", 10, 30);
}

void drawMenu()
{
    display.printText("Setting", 10, 0);
    display.printText("Zero Z", 10, 10);
    display.printText("Zero X", 10, 20);
    display.printText("Zero Y", 10, 30);
    display.printText("Home", 10, 40);
    display.printText("Back", 10, 50);
}

void drawMain()
{
    display.printText("X: ", 0, 0);
    display.printText("Y: ", 0, 10);
    display.printText("Z: ", 0, 20);
    display.printText("+/-", 110, 0);
    stepMove();
}

void drawStep()
{
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
        display.clear();
        display.printText(">", 0, 0);
        drawMenu();
    }
    if (screen == Screen::MENU)
    {
        if (buttonX.wasPressed())
        {
            menuPosition = moveCursorDown(menuPosition, 0, 5);
        }

        if (buttonY.wasPressed())
        {
            menuPosition = moveCursorUp(menuPosition, 0, 5);
        }

        if (buttonZ.wasPressed())
        {
            switch (menuPosition)
            {
            case 0:
                drawSetting();
                display.printText(">", 0, settingPosition * 10);
                screen = Screen::SETTING;
                break;

            case 1:
                display.clear();
                break;
            case 2:
                display.clear();
                break;
            case 3:
                display.clear();
                break;
            case 4:
                display.clear();
                break;
            case 5:
                display.clear();
                screen = Screen::MAIN;
                drawMain();
            default:
                break;
            }
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

        stepMove();
    }

    if (screen == Screen::SETTING)
    {
        if (settingPage == SettingPage::MENU)
        {
            if (buttonX.wasPressed())
            {
                settingPosition = moveCursorDown(settingPosition, 0, 3);
            }

            if (buttonY.wasPressed())
            {
                settingPosition = moveCursorUp(settingPosition, 0, 3);
            }

            if (buttonZ.wasPressed())
            {
                switch (settingPosition)
                {
                case 0:
                    settingPage = SettingPage::STEP;
                    display.clear();
                    drawStep();
                    break;

                case 1:
                    settingPage = SettingPage::SPEED;
                    display.clear();
                    // drawSpeed();
                    break;
                case 2:
                    settingPage = SettingPage::FEED;
                    display.clear();
                    // drawFeed();
                    break;
                case 3:
                    display.clear();
                    screen = Screen::MENU;
                    settingPage = SettingPage::MENU;
                    drawMenu();
                default:
                    break;
                }
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
    }

    if (settingPage == SettingPage::SPEED)
    {
    }

    if (settingPage == SettingPage::FEED)
    {
    }
    display.update();
}