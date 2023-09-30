#pragma once
#include <Arduino.h>
#include "DO.h"
#include "Turbidity.h"
#include "EC.h"
#include "pH.h"
#include "puzzy.h"

#include <WifiHandler.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
#include <ThingsBoard.h>

#include "ServerHandler.h"

WifiHandler wifi("eFisheryPlus", "123123123");
ServerHandler myServer("myServer");
FuzzyHandler myFuzzy;

const char *thingsboardToken = "Ojz6j6cfFJgIJmz1ZIyh";
const char *thingsboardServer = "thingsboard.cloud";
const uint16_t thingsboardPort = 1883;

WebServer server(80);
WiFiClient client;
ThingsBoard tb(client);

float DOdata;
// float turbiditydata;
// float ecdata;
// float phdata;

void DO_task(void *pvParameters);
// void turbidity_task(void *pvParameters);
// void EC_task(void *pvParameters);
// void pH_task(void *pvParameters);

void setup()
{
  sensor.setup();
  // turbidity.setup();
  // ecMeasurement.setup();
  // phMeasurement.setup();

  //  Connect to Wi-Fi network
  wifi.init();
  String paramToSend;
  myServer.postToClient(paramToSend); //perlu validasi
  myServer.begin();

  // Connect to ThingsBoard server
  Serial.print("Connecting to ThingsBoard...");
  if (!tb.connect(thingsboardServer, thingsboardToken, thingsboardPort))
  {
    Serial.println("Failed to connect to ThingsBoard!");
  }
  else
  {
    Serial.println("Connected to ThingsBoard!");
  }

  // xTaskCreatePinnedToCore(DO_task, "DO task", 1024 * 2 , NULL, 5, NULL, 1);
  // xTaskCreatePinnedToCore(turbidity_task, "Turbidity task", 1024 * 2, NULL, 5, NULL, 1);
  // xTaskCreatePinnedToCore(EC_task, "EC task", 1024 * 2 , NULL, 5, NULL, 1);
  // xTaskCreatePinnedToCore(pH_task, "pH task", 1024 * 2 , NULL, 5, NULL, 1);
  // xTaskCreatePinnedToCore(server_task, "Server task", 1024 * 4 , NULL, 15, NULL, 1);
}

void loop()
{
  vTaskDelete(NULL);
}

// void DO_task(void *pvParameters)
// {
//   (void)pvParameters;
//   while (1)
//   {
//     DOdata = sensor.readDO();
//     Serial.println("DO:\t" + String(DOdata / 1000) + "\t");
//     vTaskDelay(500);
//   }
// }

// void turbidity_task(void *pvParameters)
// {
//   (void)pvParameters;
//   while (1)
//   {
//     turbiditydata = turbidity.read_sensor();
//     Serial.printf("Nilai Tegangan Turbidity = %f\n", turbidity.read_sensor());
//     vTaskDelay(500);
//   }
// }

// void EC_task(void *pvParameters)
// {
//   (void)pvParameters;
//   while (1)
//   {
//     ecdata = ecMeasurement.read();
//     vTaskDelay(500);
//   }
// }

// void pH_task(void *pvParameters)
// {
//   (void)pvParameters;
//   while (1)
//   {
//     phdata = phMeasurement.read();
//     Serial.println("pH:\t" + String(phdata) + "\t");
//     vTaskDelay(500);
//   }
// }

// void server_task(void *pvParameters)
// {
//   (void)pvParameters;
//   while (1)
//   {
//     server.handleClient();
//     receivedData = String(DOdata / 1000);
//     tb.sendTelemetryFloat("data DO", DOdata);
//     tb.sendTelemetryFloat("data EC", ecdata);
//     tb.sendTelemetryFloat("data pH", phdata);
//     // tb.sendTelemetryInt("data turbidity", turbiditydata);
//     vTaskDelay(5000);
//   }
// }