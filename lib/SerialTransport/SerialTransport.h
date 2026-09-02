#pragma once
#include <Arduino.h>

class SerialTransport
{
private:
HardwareSerial &serial;
public:
    SerialTransport(HardwareSerial &serial);

    void begin();
    void send(const char *command);
};