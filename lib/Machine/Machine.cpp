#include "Machine.h"

Machine::Machine()
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
    workButtonAxis("X: ", positionX, 0, 0);
}

void Machine::workButtonY()
{
    workButtonAxis("Y: ", positionY, 0, 10);
}

void Machine::workButtonZ()
{
    workButtonAxis("Z: ", positionZ, 0, 20);
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
    // STOP ALL MOVE
}

void Machine::setStepPosition(uint8_t pos)
{
     if (pos < 4)
    {
    stepPosition = pos;
    machineSettings.step = stepValues[stepPosition]; // Одразу оновлюємо крок!
}
}

void Machine::setSpeedPosition(uint8_t pos)
{
     if (pos < 5)
    {
    speedPosition = pos;
    machineSettings.speed = speedValue[speedPosition]; // Одразу оновлюємо швидкість!
}
}