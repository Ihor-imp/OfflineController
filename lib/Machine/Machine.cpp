#include "Machine.h"
#include "GrblController.h"
#include <avr/pgmspace.h>

static const float stepValues[4] PROGMEM = {
    100.0f, 10.0f, 1.0f, 0.1f};

static const uint16_t speedValue[5] PROGMEM = {
    1000, 700, 500, 350, 100};

Machine::Machine(GrblController &grbl)
    : grbl(grbl)
{
    machineSettings.step = getStepValue(stepPosition);
    machineSettings.speed = getSpeedValue(speedPosition);
}

void Machine::workButtonX()
{
    float distance = machineSettings.step;

    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    grbl.jogX(distance, machineSettings.speed);
}

void Machine::workButtonY()
{
    float distance = machineSettings.step;

    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    grbl.jogY(distance, machineSettings.speed);
}

void Machine::workButtonZ()
{
    float distance = machineSettings.step;

    if (direction == Direction::MINUS)
    {
        distance = -distance;
    }

    grbl.jogZ(distance, machineSettings.speed);
}

void Machine::zeroX()
{
    grbl.zeroX();
}

void Machine::zeroY()
{
    grbl.zeroY();
}

void Machine::zeroZ()
{
    grbl.zeroZ();
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
        machineSettings.step = getStepValue(stepPosition);
    }
}

void Machine::setSpeedPosition(uint8_t pos)
{
    if (pos < 5)
    {
        speedPosition = pos;
        machineSettings.speed = getSpeedValue(speedPosition);
    }
}

float Machine::getPositionX() const
{
    return grbl.getPositionX();
}

float Machine::getPositionY() const
{
    return grbl.getPositionY();
}

float Machine::getPositionZ() const
{
    return grbl.getPositionZ();
}

bool Machine::hasValidPosition() const
{
    return grbl.hasValidPosition();
}

float Machine::getStepValue(uint8_t index) const
{
    if (index >= 4)
    {
        return 0.0f;
    }

    return pgm_read_float(&stepValues[index]);
}

uint16_t Machine::getSpeedValue(uint8_t index) const
{
    if (index >= 5)
    {
        return 0;
    }

    return pgm_read_word(&speedValue[index]);
}
