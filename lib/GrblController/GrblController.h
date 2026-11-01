
#pragma once
#include <Arduino.h>

class SerialTransport;

class GrblController
{
private:
    SerialTransport &transport;

public:
    GrblController(SerialTransport &transport);

    void jogX(float distance, float feed);
    void jogY(float distance, float feed);
    void jogZ(float distance, float feed);

    void zeroX();
    void zeroY();
    void zeroZ();

    void home();
    void stop();
};
