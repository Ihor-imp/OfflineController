
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

void SerialTransport::sendFloat(float value, uint8_t precision)
{
    serial.print(value, precision);
}

void SerialTransport::sendRealtime(uint8_t command)
{
    serial.write(command);
}
