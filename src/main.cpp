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

int16_t positionX = 0;
int16_t positionY = 0;
int16_t positionZ = 0;

uint32_t countSleep = 0;
uint32_t timeSleep = 100000;

uint32_t longPressed = 0;
uint32_t timeLongPressed = 2000;

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

Screen screen = Screen::MAIN;

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
        positionX++;
    }
    else
    {
        positionX--;
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
        positionY++;
    }
    else
    {
        positionY--;
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
        positionZ++;
    }
    else
    {
        positionZ--;
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

void drawMain()
{
    display.printText("X: ", 0, 0);
    display.printText("Y: ", 0, 10);
    display.printText("Z: ", 0, 20);
    display.printText("+/-", 110, 0);
    stepMove();
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
        drawMenu();
    }
    if (screen == Screen::MENU)
    {
        display.printText(">", 0, menuPosition * 10);

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
                display.clear();
                // open step
                break;

            case 1:
                display.clear();
                // open speed
                break;
            case 2:
                display.clear();
                // open feed
                break;
            case 3:
                display.clear();
                screen = Screen::MENU;
                drawMenu();
            default:
                break;
            }
        }
    }
    display.update();
}