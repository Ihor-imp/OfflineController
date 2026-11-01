
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
    void sendFloat(float value, uint8_t precision);
    void sendRealtime(uint8_t command);
    int available();
    int read();
};
