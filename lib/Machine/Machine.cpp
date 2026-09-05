#include "Machine.h"
#include "GrblController.h"

Machine::Machine(GrblController &grbl)
    : grbl(grbl)
{
}

void Machine::workButtonAxis(const char *text, float &position, uint8_t x, uint8_t y)
{
    if (direction == Direction::PLUS)
    {
        position += machineSettings.step;
    }
    if (direction == Direction::MINUS)
    {
        position -= machineSettings.step;
    }
}

void Machine::workButtonX()
{
    float distance = machineSettings.step;
    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    workButtonAxis("X: ", positionX, 0, 0);
    grbl.jogX(distance, 100);
}

void Machine::workButtonY()
{
    float distance = machineSettings.step;
    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    workButtonAxis("Y: ", positionY, 0, 10);
    grbl.jogY(distance, 100);
}

void Machine::workButtonZ()
{
    float distance = machineSettings.step;
    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    workButtonAxis("Z: ", positionZ, 0, 20);
    grbl.jogZ(distance, 100);
}

void Machine::zeroZ()
{
    grbl.zeroZ();
}

void Machine::zeroX()
{
    grbl.zeroX();
}

void Machine::zeroY()
{
    grbl.zeroY();
}

void Machine::moveToHome()
{
    grbl.home();
}

void Machine::workButtonPlusOrMinus()
{
    if (direction == Direction::PLUS)
    {
        direction = Direction::MINUS;
    }
    else if (direction == Direction::MINUS)
    {
        direction = Direction::PLUS;
    }
}

void Machine::workButtonStop()
{
    grbl.stop();
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