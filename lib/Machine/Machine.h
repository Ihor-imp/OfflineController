#pragma once
#include "Button.h"

enum class Direction
{
    PLUS,
    MINUS,
};

struct MachineSettings
{
    float step;
    uint16_t speed;
};

class GrblController;

class Machine
{
private:
    GrblController &grbl;

    float positionX = 0;
    float positionY = 0;
    float positionZ = 0;

    MachineSettings machineSettings = {
        0,
        0};

    Direction direction = Direction::PLUS;

    uint8_t stepPosition = 0;
    uint8_t speedPosition = 0;

    float stepValues[4] = {100, 10, 1, 0.1};
    uint16_t speedValue[5] = {1000, 700, 500, 350, 100};

public:
    Machine(GrblController &grbl);

    void workButtonAxis(const char *text, float &position, uint8_t x, uint8_t y);
    void workButtonX();
    void workButtonY();
    void workButtonZ();
    void workButtonPlusOrMinus();
    void workButtonStop();

    void zeroZ();
    void zeroX();
    void zeroY();

    void moveToHome();

    void setStepPosition(uint8_t pos);
    void setSpeedPosition(uint8_t pos);

    float getStep() const { return machineSettings.step; }
    uint16_t getSpeed() const { return machineSettings.speed; }

    uint8_t getStepPosition() const { return stepPosition; }
    uint8_t getSpeedPosition() const { return speedPosition; }

    float getStepValue(uint8_t index) const { return stepValues[index]; }
    uint16_t getSpeedValue(uint8_t index) const { return speedValue[index]; }

    float getPositionX() const { return positionX; }
    float getPositionY() const { return positionY; }
    float getPositionZ() const { return positionZ; }
    Direction getDirection() const { return direction; }
};