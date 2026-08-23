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

float step = 0;

bool minus = false;
bool inMenu = false;

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

void menu()
{
    display.printText("Setting", 10, 0);
    display.printText("Zero Z", 10, 10);
    display.printText("Zero X", 10, 20);
    display.printText("Zero Y", 10, 30);
    display.printText("Home", 10, 40);
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
        display.clear();
        menu();
        display.printText(">", 0, menuPosition * 10);
        inMenu = !inMenu;
    }

    if (inMenu)
    {

        if (buttonX.wasPressed())
        {
            display.fillRect(0, menuPosition * 10, 10, 10);
            if (menuPosition < 4)
            {
                menuPosition++;
            }
            else
            {
                menuPosition = 0;
            }
            display.printText(">", 0, menuPosition * 10);
        }

        if (buttonY.wasPressed())
        {
            display.fillRect(0, menuPosition * 10, 10, 10);
            if (menuPosition > 0)
            {
                menuPosition--;
            }
            else
            {
                menuPosition = 4;
            }
            display.printText(">", 0, menuPosition * 10);
        }

        if (buttonZ.wasPressed())
        {
            // selected
        }
    }
    else
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
    display.update();
}