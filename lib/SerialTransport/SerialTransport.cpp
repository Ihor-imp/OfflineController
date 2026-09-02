#include "SerialTransport.h"

SerialTransport::SerialTransport(HardwareSerial &serial)
    : serial(serial)
{
}

void SerialTransport::begin()
{
    serial.begin(115200);
}

void SerialTransport::send(const char *command)
{
    serial.print(command);
}