#include "Button.h"
#include "Display.h"
#include "Machine.h"
#include "DisplayUI.h"
#include "SerialTransport.h"
#include "GrblController.h"

SerialTransport transporter(Serial);
GrblController controller(transporter);
Machine machine(controller);

DisplayConfig displayConfig = {
    0x3C,
    128,
    64,
    -1};

Display display(displayConfig);

DisplayUI displayUI(display, machine);

Button buttonX(3);
Button buttonY(4);
Button buttonZ(5);
Button buttonSTOP(6);
Button buttonPLUS_MINUS(2);

uint32_t countSleep = 0;
uint32_t timeSleep = 100000;

enum class Screen
{
    MAIN,
    MENU,
    SETTING,
    ZERO_Z,
    ZERO_X,
    ZERO_Y,
    HOME
};

enum class SettingPage
{
    MENU,
    STEP,
    SPEED,
};

Screen screen = Screen::MAIN;
SettingPage settingPage = SettingPage::MENU;

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
        displayUI.drawMenu();
        return;
    }
    if (millis() - countSleep >= timeSleep)
    {
        display.off();
    }

    if (buttonX.wasPressed())
    {
        machine.workButtonX();
        displayUI.drawPositionX();
        countSleep = millis();
    }

    if (buttonY.wasPressed())
    {
        machine.workButtonY();
        displayUI.drawPositionY();
        countSleep = millis();
    }

    if (buttonZ.wasPressed())
    {
        machine.workButtonZ();
        displayUI.drawPositionZ();
        countSleep = millis();
    }

    if (buttonPLUS_MINUS.wasPressed())
    {
        machine.workButtonPlusOrMinus();
        displayUI.drawDirection();
        countSleep = millis();
    }
}

void handleMenu()
{
    if (buttonX.wasPressed())
    {
        displayUI.moveMenuCursorDown();
    }

    if (buttonY.wasPressed())
    {
        displayUI.moveMenuCursorUp();
    }

    if (buttonZ.wasPressed())
    {
        switch (displayUI.getMenuPosition())
        {
        case 0:
            displayUI.drawSetting();
            screen = Screen::SETTING;
            break;

        case 1:
            displayUI.drawConfirmWindow("Zero axis");
            screen = Screen::ZERO_Z;
            break;
        case 2:
            displayUI.drawConfirmWindow("Zero axis");
            screen = Screen::ZERO_X;
            break;
        case 3:
            displayUI.drawConfirmWindow("Zero axis");
            screen = Screen::ZERO_Y;
            break;
        case 4:
            displayUI.drawConfirmWindow("Move home");
            screen = Screen::HOME;
            break;
        default:
            break;
        }
    }
    if (buttonPLUS_MINUS.wasPressed())
    {
        screen = Screen::MAIN;
        displayUI.drawMain();
    }
}

void handleZeroAxis()
{
    switch (screen)
    {
    case Screen::ZERO_Z:
        if (buttonX.wasPressed())
        {
            displayUI.drawMenu();
            screen = Screen::MENU;
        }

        if (buttonZ.wasPressed())
        {
            machine.zeroZ();
            screen = Screen::MENU;
            displayUI.drawMenu();
        }
        break;
    case Screen::ZERO_X:
        if (buttonX.wasPressed())
        {
            displayUI.drawMenu();
            screen = Screen::MENU;
        }

        if (buttonZ.wasPressed())
        {
            machine.zeroX();
            screen = Screen::MENU;
            displayUI.drawMenu();
        }
        break;
    case Screen::ZERO_Y:
        if (buttonX.wasPressed())
        {
            displayUI.drawMenu();
            screen = Screen::MENU;
        }

        if (buttonZ.wasPressed())
        {
            machine.zeroY();
            screen = Screen::MENU;
            displayUI.drawMenu();
        }
        break;
    case Screen::HOME:
        if (buttonX.wasPressed())
        {
            displayUI.drawMenu();
            screen = Screen::MENU;
        }

        if (buttonZ.wasPressed())
        {
            machine.moveToHome();
            screen = Screen::MENU;
            displayUI.drawMenu();
        }
        break;
    default:
        break;
    }
}

void handleSetting()
{
    switch (settingPage)
    {
    case SettingPage::MENU:
        if (buttonX.wasPressed())
        {
            displayUI.moveSettingCursorDown();
        }

        if (buttonY.wasPressed())
        {
            displayUI.moveSettingCursorUp();
        }

        if (buttonZ.wasPressed())
        {
            switch (displayUI.getSettingPosition())
            {
            case 0:
                settingPage = SettingPage::STEP;
                displayUI.drawStep();
                break;

            case 1:
                settingPage = SettingPage::SPEED;
                displayUI.drawSpeed();
                break;
            default:
                break;
            }
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            screen = Screen::MENU;
            displayUI.drawMenu();
        }
        break;

    case SettingPage::STEP:
        if (buttonX.wasPressed())
        {
            displayUI.moveStepCursorRight();
        }
        if (buttonZ.wasPressed())
        {
            machine.setStepPosition(displayUI.getStepCursorPosition());
            displayUI.drawStepValue();
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            settingPage = SettingPage::MENU;
            displayUI.drawSetting();
        }
        break;
    case SettingPage::SPEED:
        if (buttonX.wasPressed())
        {
            displayUI.moveSpeedCursorDown();
        }

        if (buttonZ.wasPressed())
        {
            machine.setSpeedPosition(displayUI.getSpeedCursorPosition());
            displayUI.drawSpeedValue();
        }
        if (buttonPLUS_MINUS.wasPressed())
        {
            settingPage = SettingPage::MENU;
            displayUI.drawSetting();
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
    case Screen::ZERO_Z:
    case Screen::ZERO_X:
    case Screen::ZERO_Y:
    case Screen::HOME:
        handleZeroAxis();
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

    displayUI.drawStepAndSpeed();

    display.update();
    countSleep = millis();
}

void loop()
{
    updateButtons();
    handleScreen();
}