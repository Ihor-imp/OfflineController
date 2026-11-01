
#include "GrblController.h"
#include "SerialTransport.h"

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
