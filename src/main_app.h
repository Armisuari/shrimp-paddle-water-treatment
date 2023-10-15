#include <Arduino.h>
#include <WifiHandler.h>

#include "config.h"
#include "mdns.h"
#include "ServerHandler.h"

#include "ThingsboardApp/TBHandler.h" // Import the correct ThingsBoard header
#include "TelemetryPublish.h"
#include "TBCredentials.h"

// include sensors library
#include "Sensors/DS18b20.h"
#include "Sensors/DOSensor.h"
#include "Sensors/ECSensor.h"
#include "Sensors/pHSensor.h"
#include "Sensors/TurbSensor.h"

// for smoothie reading purposes
#ifdef KALMAN_FILTER
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter kFilter(2, 2, 0.01);
#endif

// mdns setup
const char *version = CONFIG_MAIN_FW_VERSION_STRING;
char clientID[sizeof(CONFIG_MAIN_CLIENT_ID_PREFIX) + 6];

void generateClientID(char *idBuff);
void setupMDNSResponder(char *hostname);

// connectivity
WifiHandler wifi(CONFIG_MAIN_WIFI_DEFAULT_SSID, CONFIG_MAIN_WIFI_DEFAULT_PASS);
ServerHandler server("myServer");

TBHandler thingsBoard(CONFIG_TB_TOKEN); // Create a ThingsBoard object

// sensor object
DS18B20 tempSensor(CONFIG_SENSOR_TEMPERATURE_PIN);
DOSensor DOsensor(CONFIG_SENSOR_ADS_PIN_DO);
pHSensor pHsensor(CONFIG_SENSOR_ADS_PIN_PH);

// parameter value object
Temperature_t tempValue;

#define AMOUNT_OF_AVERAGE_DATA 3

// NTP Server
const char *ntpServer = "pool.ntp.org";

void taskReadPublish(void *pvParameter);
void printSensorValue(Temperature_t tempVal, DO_Value doVal, pH_Value phvalue);
void printToPlot(Temperature_t temp);

void setup()
{
    Serial.begin(115200);
    generateClientID(clientID); // Generate clientID based on MAC Addr

    // connectivity setup
    wifi.init();

    // NTP time sync
    configTime(0, 0, ntpServer);

    server.begin();

    // MDNS
    setupMDNSResponder(clientID);

    // NTP time sync
    // configTime(0, 0, ntpServer);

    // thingsboard
    thingsBoard.setup("demo.thingsboard.io", 1883U, CONFIG_TB_MSG_BUFF); // Initialize the ThingsBoard object

    delay(2000);

    // sensor begin
    tempSensor.begin();
    DOsensor.init();
    pHsensor.init();

    xTaskCreate(
        taskReadPublish,
        "task for read and publish",
        4096,
        NULL,
        1,
        NULL);
}

void loop()
{
    vTaskDelete(NULL);
}

void taskReadPublish(void *pvParameter)
{
    TelemetryPublish publishData("ESP32-macca", CONFIG_TB_MSG_BUFF);
    thingsBoard.addPublishSource(&publishData);
    WaterQuality_t data;

    while (1)
    {

#ifndef KALMAN_FILTER
        Temperature_t tempValue;
        DO_Value DOvalue;
        pH_Value phvalue;

        tempSensor.measure(tempValue);
        DOsensor.Measure(DOvalue, tempValue);
        pHsensor.measure(phvalue);


        data.temp = tempValue.temp;
        data.DO = DOvalue.value;
        data.pH = phvalue.value;

        printSensorValue(tempValue, DOvalue, phvalue);
        // printToPlot(tempValue);

#else
        Temperature_t filTemp;
        DO_Value filDO;

        tempSensor.filter(kFilter.updateEstimate(tempValue.temp), filTemp);
        DOsensor.filter(kFilter.updateEstimate(filDO.value), filDO);

        data.temp = filTemp.temp;
        data.DO = filDO.value;

        printSensorValue(filTemp, filDO);
        // printToPlot(filTemp);
#endif

        printSensorValue(tempValue, DOvalue, phvalue);
        // printToPlot(tempValue);

        publishData.writeSensorData(data);

        vTaskDelay(5000);
    }
}

void generateClientID(char *idBuff)
{
    const char *clientIdPrefix = CONFIG_MAIN_CLIENT_ID_PREFIX;
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    sprintf(idBuff, "%s%02X%02X%02X", clientIdPrefix, mac[3], mac[4], mac[5]);
}

void printSensorValue(Temperature_t tempVal, DO_Value doVal, pH_Value phvalue)
{
    Serial.println();

    Serial.printf("Temperature (℃) : %4.2f\n", tempVal.temp);
    Serial.printf("DO (mg/L) : %4.2f\n", doVal.value);
    Serial.printf("pH : %4.2f\n", phvalue.value );
    Serial.println("===========================");

    Serial.println();
}

void printToPlot(Temperature_t tempVal, DO_Value doVal, pH_Value phvalue)
{
    Serial.print("temp:");
    Serial.print(tempVal.temp);
    Serial.print(",");
    Serial.print("do:");
    Serial.print(doVal.value);
    Serial.print(",");
    Serial.print("pH:");
    Serial.print(phvalue.value);
    Serial.print(",");

    Serial.println();
}

void setupMDNSResponder(char *hostname)
{
    // Serial.printf("hosname: %s\n", hostname);
    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_init());
    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_hostname_set(hostname));
    ESP_LOGI("MAIN", "MDNS hostname: %s", hostname);

    // OTA Service decription
    mdns_txt_item_t serviceTxtData[4] = {
        {"HW version", "v1"},
        {"FW version", CONFIG_MAIN_FW_VERSION_STRING},
        {"Device", "WQMD"},
        {"path", "/"}};

    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_service_add(NULL, "_http", "_tcp", 80, serviceTxtData, 3));
}