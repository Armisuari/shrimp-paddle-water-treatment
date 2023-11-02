#pragma once

#include <ArduinoJson.h>
#include "ThingsboardApp/TBPublishSource.h"

typedef struct
{
    float temp;
    float DO;
    float EC;
    float pH;
    float turbidity = 0;
    int jarak;

} WaterQuality_t;

class TelemetryPublish : public TBPublishSource
{
public:
    TelemetryPublish(const char *clientID, size_t bufferSize);
    bool writeSensorData(WaterQuality_t data);

protected:
    virtual std::string readPayload();
    virtual size_t readPayload(uint8_t *buff, size_t length);

private:
    std::string _formatSensorDataJson(WaterQuality_t data);
    char _clientID[24];
};