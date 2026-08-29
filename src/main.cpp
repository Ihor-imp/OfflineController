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

uint8_t settingPosition = 0;

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

struct MachineSettings
{
    float step;
    uint16_t speed;
};

MachineSettings machineSettings = {
    0,
    0};

uint8_t stepPosition = 2;
uint8_t axisPosition = 1;

uint8_t speedPosition = 0;

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

void workButtonAxis(const char *text, float &position, uint8_t x, uint8_t y)
{
    display.on();
    display.printText(text, x, y);
    if (!minus)
    {
        position += machineSettings.step;
    }
    else
    {
        position -= machineSettings.step;
    }

    display.fillRect(13, y, 35, 8);
    display.printValue(position, 13, y);
    display.update();
    countSleep = millis();
}

void workButtonX()
{
    workButtonAxis("X: ", positionX, 0, 0);
}

void workButtonY()
{
    workButtonAxis("Y: ", positionY, 0, 10);
}

void workButtonZ()
{
    workButtonAxis("Z: ", positionZ, 0, 20);
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
    display.printValue(machineSettings.step, 30, 55);

    display.printText("SPEED: ", 65, 55);
    display.printValue(machineSettings.speed, 100, 55);

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
    display.printText("+/-", 110, 0);
    drawStepAndSpeed();

    display.update();
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

    display.update();
}

void drawSpeed()
{
    display.clear();
    display.printText("SPEED: ", 10, 0);
    display.printValue(machineSettings.speed, 55, 0);

    display.printValue(1000, 10, 10);
    display.printValue(700, 10, 20);
    display.printValue(500, 10, 30);
    display.printValue(350, 10, 40);
    display.printValue(100, 10, 50);

    display.update();
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

    display.update();
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

    display.update();
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

    display.update();
    return position;
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

void handleMenu()
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

void handleSetting()
{
    switch (settingPage)
    {
    case SettingPage::MENU:
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
        break;

    case SettingPage::STEP:
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
                machineSettings.step = stepValues[stepPosition - 2];

                Serial.print("stepPosition = ");
                Serial.println(stepPosition);

                Serial.print("step = ");
                Serial.println(machineSettings.step);
                display.printValue(machineSettings.step, 10, 50);

                display.update();
            }
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
            speedPosition = moveCursorDown(speedPosition, 1, 5);
        }
        if (buttonZ.wasPressed())
        {
            if (speedPosition >= 1 && speedPosition <= 5)
            {
                machineSettings.speed = speedValue[speedPosition - 1];
                display.fillRect(55, 0, 40, 40);
                display.printValue(machineSettings.speed, 55, 0);

                display.update();
            }
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

void loop()
{
    updateButtons();
    handleScreen();
}