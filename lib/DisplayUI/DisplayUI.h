#pragma once
#include <Arduino.h>
#include "Machine.h"
#include "Display.h"

class DisplayUI
{
private:
    Display &display;
    Machine &machine;

    uint8_t stepCursorPosition = 0;
    uint8_t speedCursorPosition = 0;

    uint8_t menuPosition = 0;
    uint8_t settingPosition = 0;

    uint8_t axisPosition = 0;

public:
    DisplayUI(Display &display, Machine &machine);

    void drawSetting();
    void drawStepAndSpeed();
    void drawMenu();
    void drawMain();
    void drawStep();
    void drawSpeed();

    void moveMenuCursorDown();
    void moveMenuCursorUp();
    void moveSettingCursorDown();
    void moveSettingCursorUp();

    void selectMenuItem();
    void selectSettingItem();

    void moveAxisCursorDown();
    void moveStepCursorRight();
    void moveSpeedCursorDown();

    uint8_t moveCursorRight(uint8_t index, uint8_t maxIndex, uint8_t startX, uint8_t stepX, uint8_t y);
    uint8_t moveCursorDown(uint8_t index, uint8_t maxIndex, uint8_t startY, uint8_t stepY);
    uint8_t moveCursorUp(uint8_t index, uint8_t maxIndex, uint8_t startY, uint8_t stepY = 10);

    void drawPositionX();
    void drawPositionY();
    void drawPositionZ();
    void drawDirection();
    void drawStepValue();
    void drawSpeedValue();

    uint8_t getMenuPosition() const;
    uint8_t getSettingPosition() const;
    uint8_t getSpeedCursorPosition() const;
    uint8_t getStepCursorPosition() const;
};
