#include "TelemetryPublish.h"

TelemetryPublish::TelemetryPublish(const char *clientID, size_t buffersize) : TBPublishSource(buffersize)
{
    strncpy(_clientID, clientID, 23);
    _clientID[23] = '\0';
}

bool TelemetryPublish::writeSensorData(WaterQuality_t data)
{
    return writeRawData(&data, sizeof(WaterQuality_t)) == sizeof(WaterQuality_t);
}

std::string TelemetryPublish::readPayload()
{
    WaterQuality_t data;
    std::string payload;
    if (readRawData(&data, sizeof(WaterQuality_t)) > 0)
    {
        payload = _formatSensorDataJson(data);
    }

    return payload;
}

size_t TelemetryPublish::readPayload(uint8_t *buff, size_t length)
{
    WaterQuality_t data;
    size_t resLen = 0;
    std::string payload;
    if (readRawData(&data, sizeof(WaterQuality_t)) == sizeof(WaterQuality_t))
    {
        payload = _formatSensorDataJson(data);
        if (payload.length() < length)
        {
            resLen = payload.length();
            payload.copy(reinterpret_cast<char *>(buff), resLen);
        }
    }

    return resLen;
}

std::string TelemetryPublish::_formatSensorDataJson(WaterQuality_t data)
{
    char buffer[512];
    sprintf(buffer,
            "{"
            "\"DO\": %.2f,"
            "\"EC\": %.2f,"
            "\"PH\": %.2f,"
            "\"turb\": %.2f,"
            "\"temp\": %.2f,"
            "\"jarak\": %d"
            "}",
            data.DO/1000, data.EC, data.pH,
            data.turbidity, data.temp, data.jarak);

    return std::string(buffer);
}