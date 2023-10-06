#include <Arduino.h>
#include <WifiHandler.h>
#include "ThingsboardApp/TBHandler.h" // Import the correct ThingsBoard header
#include "TelemetryPublish.h"

WifiHandler wifi("eFisheryPlus", "123123123");

const String THINGSBOARD_TOKEN = "mip3v4418qaz8weeaqg9";
size_t MSG_BUFFER_SIZE = 8192;

TBHandler thingsBoard(THINGSBOARD_TOKEN); // Create a ThingsBoard object

TelemetryPublish publishData("ESP32-macca", MSG_BUFFER_SIZE);
WaterQuality_t data;

void setup()
{
    Serial.begin(115200);
    wifi.init();
    thingsBoard.setup("demo.thingsboard.io", 1883U, MSG_BUFFER_SIZE); // Initialize the ThingsBoard object
    thingsBoard.addPublishSource(&publishData);
}

void loop()
{
    // Read sensor data or collect other information here
    // For example, you can use publishData.sendTelemetryFloat("temperature", temperatureValue);
    // Replace "temperature" and temperatureValue with your actual data.

    data.DO = 10.00;
    publishData.writeSensorData(data);

    delay(5000);
}
