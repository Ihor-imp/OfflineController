
#include "GrblController.h"
#include "SerialTransport.h"
#include <stdlib.h>
#include <string.h>

GrblController::GrblController(SerialTransport &transport)
    : transport(transport)
{
}

void GrblController::jogX(float distance, float feed)
{
    transport.send("$J=G91 X");
    transport.sendFloat(distance, 1);
    transport.send(" F");
    transport.sendFloat(feed, 0);
    transport.send("\n");
}

void GrblController::jogY(float distance, float feed)
{
    transport.send("$J=G91 Y");
    transport.sendFloat(distance, 1);
    transport.send(" F");
    transport.sendFloat(feed, 0);
    transport.send("\n");
}

void GrblController::jogZ(float distance, float feed)
{
    transport.send("$J=G91 Z");
    transport.sendFloat(distance, 1);
    transport.send(" F");
    transport.sendFloat(feed, 0);
    transport.send("\n");
}

void GrblController::requestStatus()
{
    transport.sendRealtime(0x3F);
}

void GrblController::update()
{
    uint32_t now = millis();

    if ((now - lastStatusRequest) >= STATUS_INTERVAL_MS)
    {
        requestStatus();
        lastStatusRequest = now;
    }

    while (transport.available() > 0)
    {
        int readByte = transport.read();

        if (readByte == -1)
        {
            return;
        }

        if (readByte == '<')
        {
            receiving = true;
            rxIndex = 0;
            continue;
        }

        if (!receiving)
        {
            continue;
        }

        if (readByte == '>')
        {
            rxBuffer[rxIndex] = '\0';
            receiving = false;
            parseStatus();
            rxIndex = 0;
            continue;
        }

        if (rxIndex < sizeof(rxBuffer) - 1)
        {
            rxBuffer[rxIndex] = (char)readByte;
            rxIndex++;
        }
        else
        {
            receiving = false;
            rxIndex = 0;
        }
    }
}

void GrblController::parseStatus()
{
    // Machine Position
    char *ptr = strstr(rxBuffer, "MPos:");

    if (ptr != nullptr)
    {
        ptr += 5;
        char *endPtr = nullptr;

        float x = strtod(ptr, &endPtr);

        if (endPtr != ptr && *endPtr == ',')
        {
            ptr = endPtr + 1;
            float y = strtod(ptr, &endPtr);

            if (endPtr != ptr && *endPtr == ',')
            {
                ptr = endPtr + 1;
                float z = strtod(ptr, &endPtr);

                if (endPtr != ptr &&
                    (*endPtr == '|' || *endPtr == '\0'))
                {
                    positionX = x;
                    positionY = y;
                    positionZ = z;
                    positionValid = true;
                }
            }
        }
    }

    // Work Coordinate Offset
    char *ptrWco = strstr(rxBuffer, "WCO:");

    if (ptrWco != nullptr)
    {
        ptrWco += 4;
        char *endPtr = nullptr;

        float x = strtod(ptrWco, &endPtr);

        if (endPtr != ptrWco && *endPtr == ',')
        {
            ptrWco = endPtr + 1;
            float y = strtod(ptrWco, &endPtr);

            if (endPtr != ptrWco && *endPtr == ',')
            {
                ptrWco = endPtr + 1;
                float z = strtod(ptrWco, &endPtr);

                if (endPtr != ptrWco &&
                    (*endPtr == '|' || *endPtr == '\0'))
                {
                    wcoX = x;
                    wcoY = y;
                    wcoZ = z;
                    wcoValid = true;
                }
            }
        }
    }
}

void GrblController::home()
{
    transport.send("$H\n");
}

void GrblController::stop()
{
    transport.sendRealtime(0x85);
}

void GrblController::zeroX()
{
    transport.send("G92 X0\n");
}

void GrblController::zeroY()
{
    transport.send("G92 Y0\n");
}

void GrblController::zeroZ()
{
    transport.send("G92 Z0\n");
}

float GrblController::getPositionX() const
{
    return positionX - wcoX;
}

float GrblController::getPositionY() const
{
    return positionY - wcoY;
}

float GrblController::getPositionZ() const
{
    return positionZ - wcoZ;
}

bool GrblController::hasValidPosition() const
{
    return positionValid && wcoValid;
}
