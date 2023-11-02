#include <Arduino.h>
#include <WifiHandler.h>

#include "config.h"
#include "mdns.h"
#include "ServerHandler.h"
#include "LiquidCrystal_I2C.h"

#include "ThingsboardApp/TBHandler.h" // Import the correct ThingsBoard header
#include "TelemetryPublish.h"
#include "TBCredentials.h"

#include "puzzy.h"

// include sensors library
#include "Sensors/DS18b20.h"
#include "Sensors/DOSensor.h"
#include "Sensors/ECSensor.h"
#include "Sensors/pHSensor.h"
#include "Sensors/TurbSensor.h"
#include "Sensors/JSN.h"
#include "Sensors/tesdo.h"

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

//Fuzzy
FuzzyHandler myfuzzy;

//LCD
LiquidCrystal_I2C mylcd(0x27,20,4);

// connectivity
WifiHandler wifi(CONFIG_MAIN_WIFI_DEFAULT_SSID, CONFIG_MAIN_WIFI_DEFAULT_PASS);
ServerHandler server("myServer");

TBHandler thingsBoard(CONFIG_TB_TOKEN); // Create a ThingsBoard object

// sensor object
DS18B20 tempSensor(CONFIG_SENSOR_TEMPERATURE_PIN);
DOSensor DOsensor(CONFIG_SENSOR_ADS_PIN_DO);
pHSensor pHsensor(CONFIG_SENSOR_ADS_PIN_PH);
ECSensor ecsensor(CONFIG_SENSOR_ADS_PIN_EC);
JSN jarak;

// parameter value object
Temperature_t tempValue;

#define AMOUNT_OF_AVERAGE_DATA 3

// NTP Server
// const char *ntpServer = "pool.ntp.org";

void taskReadPublish(void *pvParameter);
void printSensorValue(Temperature_t tempVal, DO_Value doVal, pH_Value phvalue, EC_Value ecvalue);
void printToPlot(Temperature_t temp);
void fuzzy_task(JSN jarakvalue, DO_Value doVal, pH_Value phvalue, EC_Value ecvalue);

void setup()
{
  Serial.begin(115200);
  generateClientID(clientID); // Generate clientID based on MAC Addr

  //LCD setup
  mylcd.init();
  mylcd.backlight();

  //Fuzzy Setup
  myfuzzy.begin();

  // connectivity setup
  wifi.init();

  // NTP time sync
//   configTime(0, 0, ntpServer);

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
    ecsensor.init(tempValue);
    jarak.init();
    

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
        EC_Value ecvalue;
        JSN jarakvalue;


        tempSensor.measure(tempValue);
        DOsensor.Measure(DOvalue, tempValue);
        pHsensor.measure(phvalue);
        ecsensor.measure(ecvalue, tempValue);
        jarakvalue.measure();


        data.temp = tempValue.temp;
        data.DO = DOvalue.value;
        data.pH = phvalue.value;
        data.EC = ecvalue.value;
        data.jarak = jarak.measure();

        printSensorValue(tempValue, DOvalue, phvalue, ecvalue);
        // fuzzy_task(jarak.measure(),DOvalue,phvalue,ecvalue);
        // printToPlot(tempValue);

    char buff[20];
    sprintf(buff,
            "{"
            "\"DO\": %.2f"
            "}",
            DOvalue.value);

    server.postToClient(buff);

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

        printSensorValue(tempValue, DOvalue, phvalue, ecvalue);
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

void printSensorValue(Temperature_t tempVal, DO_Value doVal, pH_Value phvalue, EC_Value ecvalue)
{
  Serial.println();

    Serial.printf("Temperature (℃) : %4.2f\n", tempVal.temp);
    Serial.printf("DO (mg/L) : %4.2f\n", doVal.value/1000);
    // Serial.printf("DO (mg/L) : %4.2f\n", sensor.data());
    Serial.printf("pH : %4.2f\n", phvalue.value);
    Serial.printf("EC : %f\n", ecvalue.value);
    Serial.printf("Jarak: %d\n", jarak.measure());
    Serial.println("===========================");


    mylcd.setCursor(0,0);
    mylcd.print("Temp :");
    mylcd.setCursor(8,0);
    mylcd.print(tempVal.temp);
    mylcd.setCursor(0,1);
    mylcd.print("DO :");
    mylcd.setCursor(6,1);
    mylcd.print(doVal.value/1000);
    mylcd.setCursor(0,2);
    mylcd.print("Jarak:");
    mylcd.setCursor(8,2);
    mylcd.print(jarak.measure());
    mylcd.setCursor(0,3);
    mylcd.print("pH :");
    mylcd.setCursor(6,3);
    mylcd.print(phvalue.value);

  Serial.println();
}

void printToPlot(Temperature_t tempVal, DO_Value doVal, pH_Value phvalue, EC_Value ecvalue)
{
    Serial.print("temp:");
    Serial.print(tempVal.temp);
    Serial.print(",");
    Serial.print("do:");
    Serial.print(doVal.value/1000);
    Serial.print(",");
    Serial.print("pH:");
    Serial.print(phvalue.value);
    Serial.print(",");
    Serial.print("EC:");
    Serial.print(ecvalue.value);
    Serial.print(",");

  Serial.println();
}

void fuzzy_task(JSN jarakvalue, DO_Value doVal, pH_Value phvalue, EC_Value ecvalue){
  myfuzzy.setinput(1,phvalue.value);
  myfuzzy.setinput(2,doVal.value);
  myfuzzy.setinput(3, jarakvalue.measure());
  myfuzzy.setinput(4, ecvalue.value);

  fuzzy->fuzzify();

  int out = fuzzy->defuzzify(1);
  Serial.print("out fuzzy = ");
  Serial.println(out);
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