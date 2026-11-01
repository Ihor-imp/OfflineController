
#include "Machine.h"
#include "GrblController.h"

Machine::Machine(GrblController &grbl)
    : grbl(grbl)
{
    machineSettings.step = stepValues[stepPosition];
    machineSettings.speed = speedValue[speedPosition];
}

void Machine::workButtonAxis(const char *text, float &position,
                             uint8_t x, uint8_t y)
{
    float distance = machineSettings.step;

    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    position += distance;
}

void Machine::workButtonX()
{
    float distance = machineSettings.step;

    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    grbl.jogX(distance, machineSettings.speed);
    positionX += distance;
}

void Machine::workButtonY()
{
    float distance = machineSettings.step;

    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    grbl.jogY(distance, machineSettings.speed);
    positionY += distance;
}

void Machine::workButtonZ()
{
    float distance = machineSettings.step;

    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    grbl.jogZ(distance, machineSettings.speed);
    positionZ += distance;
}

void Machine::zeroX()
{
    grbl.zeroX();
    positionX = 0;
}

void Machine::zeroY()
{
    grbl.zeroY();
    positionY = 0;
}

void Machine::zeroZ()
{
    grbl.zeroZ();
    positionZ = 0;
}

void Machine::moveToHome()
{
    grbl.home();
}

void Machine::workButtonStop()
{
    grbl.stop();
}

void Machine::workButtonPlusOrMinus()
{
    if (direction == Direction::PLUS)
    {
        direction = Direction::MINUS;
    }
    else
    {
        direction = Direction::PLUS;
    }
}

void Machine::setStepPosition(uint8_t pos)
{
    if (pos < 4)
    {
        stepPosition = pos;
        machineSettings.step = stepValues[stepPosition];
    }
}

void Machine::setSpeedPosition(uint8_t pos)
{
    if (pos < 5)
    {
        speedPosition = pos;
        machineSettings.speed = speedValue[speedPosition];
    }
}
