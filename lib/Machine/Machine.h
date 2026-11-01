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

    MachineSettings machineSettings = {
        0,
        0};

    Direction direction = Direction::PLUS;

    uint8_t stepPosition = 0;
    uint8_t speedPosition = 0;

public:
    Machine(GrblController &grbl);

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

float getStepValue(uint8_t index) const;
uint16_t getSpeedValue(uint8_t index) const;

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    Direction getDirection() const { return direction; }

    bool hasValidPosition() const;
};