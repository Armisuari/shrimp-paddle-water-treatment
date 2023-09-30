#include <Arduino.h>
#include <WifiHandler.h>

#include "config.h"
#include "mdns.h"
#include "ServerHandler.h"

// include sensors library
#include "Sensors/DS18b20.h"
#include "Sensors/DOSensor.h"
#include "Sensors/ECSensor.h"
#include "Sensors/pHSensor.h"
#include "Sensors/TurbSensor.h"

#define KALMAN_FILTER

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

// sensor object
DS18B20 tempSensor(CONFIG_SENSOR_TEMPERATURE_PIN);

// parameter value object
Temperature_t tempValue;

#define AMOUNT_OF_AVERAGE_DATA 3

// NTP Server
const char *ntpServer = "pool.ntp.org";

void printSensorValue(Temperature_t temp);
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
    configTime(0, 0, ntpServer);
    delay(2000);

    // DS18B20::getValue();

    tempSensor.begin();
}

void loop()
{
    // vTaskDelete(NULL);

    // parameter value object
    Temperature_t tempValue;

    tempSensor.measure(tempValue);

#ifdef KALMAN_FILTER
    Temperature_t filTemp;
    tempSensor.filter(kFilter.updateEstimate(tempValue.temp), filTemp);
#endif

    // printSensorValue(tempValue);
    printToPlot(tempValue);
    vTaskDelay(1000);
}

void generateClientID(char *idBuff)
{
    const char *clientIdPrefix = CONFIG_MAIN_CLIENT_ID_PREFIX;
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    sprintf(idBuff, "%s%02X%02X%02X", clientIdPrefix, mac[3], mac[4], mac[5]);
}

void printSensorValue(Temperature_t value)
{
    Serial.println(" -----------------------");
    Serial.printf("| Temperature | %4.2f ℃ |\n", value.temp);
    Serial.println(" -----------------------");
}

void printToPlot(Temperature_t value)
{
    Serial.print("temp:");
    Serial.print(value.temp);
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