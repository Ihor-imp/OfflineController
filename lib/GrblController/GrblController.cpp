#include "GrblController.h"

GrblController::GrblController()
{
}

const char *GrblController::jogX(float distance, float feed)
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$J=G91 X%.1f F%.0f\n", distance, feed);
    return commandBuffer;
}
const char *GrblController::jogY(float distance, float feed)
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$J=G91 Y%.1f F%.0f\n", distance, feed);
    return commandBuffer;
}
const char *GrblController::jogZ(float distance, float feed)
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$J=G91 Z%.1f F%.0f\n", distance, feed);
    return commandBuffer;
}

const char *GrblController::home()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "$H\n");
    return commandBuffer;
}

const char *GrblController::stop()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "!");
    return commandBuffer;
}

const char *GrblController::zeroX()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "G92 X0\n");
    return commandBuffer;
}

const char *GrblController::zeroY()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "G92 Y0\n");
    return commandBuffer;
}

const char *GrblController::zeroZ()
{
    snprintf(commandBuffer, sizeof(commandBuffer), "G92 Z0\n");
    return commandBuffer;
}