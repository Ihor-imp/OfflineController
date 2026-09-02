#include "GrblController.h"
#include "SerialTransport.h"

GrblController::GrblController(SerialTransport &transport)
    : transport(transport)
{
}

void GrblController::jogX(float distance, float feed)
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$J=G91 X%.1f F%.0f\n", distance, feed);
    transport.send(commandBuffer);
}
void GrblController::jogY(float distance, float feed)
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$J=G91 Y%.1f F%.0f\n", distance, feed);
    transport.send(commandBuffer);
}
void GrblController::jogZ(float distance, float feed)
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$J=G91 Z%.1f F%.0f\n", distance, feed);
    transport.send(commandBuffer);
}

void GrblController::home()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$H\n");
    transport.send(commandBuffer);
}

void GrblController::stop()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "!");
    transport.send(commandBuffer);
}

void GrblController::zeroX()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "G92 X0\n");
    transport.send(commandBuffer);
}

void GrblController::zeroY()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "G92 Y0\n");
    transport.send(commandBuffer);
}

void GrblController::zeroZ()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "G92 Z0\n");
    transport.send(commandBuffer);
}