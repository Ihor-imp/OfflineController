
#pragma once
#include <Arduino.h>

class SerialTransport;

class GrblController
{
private:
    SerialTransport &transport;

    char rxBuffer[64] = {0};
    bool receiving = false;
    uint8_t rxIndex = 0;

    float positionX = 0.0f;
    float positionY = 0.0f;
    float positionZ = 0.0f;

    float wcoX = 0.0f;
    float wcoY = 0.0f;
    float wcoZ = 0.0f;

    bool positionValid = false;
    bool wcoValid = false;

    uint32_t lastStatusRequest = 0;
    static constexpr uint32_t STATUS_INTERVAL_MS = 250;

    void parseStatus();

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

    void update();
    void requestStatus();

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    bool hasValidPosition() const;
};
