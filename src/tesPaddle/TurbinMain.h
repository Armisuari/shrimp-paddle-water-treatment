#include <Arduino.h>
#include <RBDdimmer.h>
#include "fuzzy_motor.h"
// #include "fuzzy_speed.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "LCDHandler.h"

const char* ssid = "ESP-SoftAP";
const char* password = "";
const char* targetIP = "192.168.4.1"; // IP address of the other ESP
const int targetPort = 80; // Port to access

const int zeroCrossPin  = 15;
const int acdPin  = 4;
//Variables
int power=10;
//Objects
dimmerLamp acd(acdPin,zeroCrossPin);

#define relay 13

FuzzyHandler fz;
LCDHandler lcdhandler;

int hasil;
int state=1;
int motor;
int inputFuzzy;

void fz_task(void *pvParameters);
void bt_task(void *pvParameters);
void mn_task(void *pvParameters);
void cl_task(void *pvParameters);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  fz.begin();
  acd.begin(NORMAL_MODE, ON);
  lcdhandler.init();

  pinMode(23, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(relay, OUTPUT);

  //
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");
  //

  xTaskCreatePinnedToCore(fz_task, "Fuzzy Task", 1024 * 2, NULL, 10, NULL, 1);
  // xTaskCreatePinnedToCore(bt_task, "Button Task", 1024 * 2, NULL, 5, NULL, 1);
  // xTaskCreatePinnedToCore(mn_task, "Manual Task", 1024 * 2, NULL, 10, NULL, 1);
  // xTaskCreatePinnedToCore(cl_task, "Client Task", 1024 * 4, NULL, 15, NULL, 1);
}

void loop() {
  // Serial.print(digitalRead(23));
  // Serial.println(digitalRead(22));
  // delay(10);
vTaskDelete(NULL);
}

void fz_task(void *pvParameters){
  (void) pvParameters;
  while (1) {
    if (state==1){
      int dataDO = Serial.parseInt();
      if (dataDO > 0){
        inputFuzzy = dataDO;
      }
      fz.setinput(1, inputFuzzy); // Mengatur input untuk logika fuzzy
      fz.fuzify(); // Menghitung keluaran logika fuzzy
      hasil = fz.output(); // Mendapatkan nilai keluaran logika fuzzy
      Serial.printf("output Fuzzy: %d\n", hasil);
      lcdhandler.cetak(0,0,"output Fuzzy:");
      lcdhandler.cetak(0,1,String(hasil));
      digitalWrite(relay,hasil);
      // acd.setPower(hasil);
      // Serial.print("Motor Value -> ");
      // Serial.print(acd.getPower());
      // Serial.println("%");
    // Serial.println(dataDO);
      vTaskDelay(10);
    }
  }
}

void bt_task(void *pvParameters){
  (void) pvParameters;
  for(;;){
    Serial.printf("State = %d\n",state);
    Serial.printf("tombol = %d\n", digitalRead(23));
    if (digitalRead(23)==0 && state==0){
      state=1;
    }

    else if (digitalRead(23)==0 && state==1){
      state=0;
    }
    vTaskDelay(10);
  }
}

void mn_task(void *pvParameters){
  (void) pvParameters;
  for(;;){
    Serial.printf("motor = %d\n",motor);
    Serial.printf("button motor = %d\n", digitalRead(22));
    if (state == 0){
      if (digitalRead(22)==0 && motor == 0){
        digitalWrite(relay,LOW);
        vTaskDelay(10);
        motor=1;
      }
      if(digitalRead(22)==0 && motor == 1){
        digitalWrite(relay,HIGH);
        vTaskDelay(10);
        motor=0;
      }
    }
    vTaskDelay(10);
  }
}

// void cl_task(void *pvParameters){
//   (void) pvParameters;
//   for(;;){
//       if (WiFi.status() == WL_CONNECTED) {
//       HTTPClient http;

//     String url = "http://" + String(targetIP) + ":" + String(targetPort) + "/tes"; // Adjust the URL accordingly

//     Serial.print("Connecting to ");
//     Serial.println(url);

//     http.begin(url);
//     int httpCode = http.GET();

//     if (httpCode > 0) {
//       String payload = http.getString();
//       Serial.println("HTTP response code: " + String(httpCode));
//       Serial.println("Received data: " + payload);
//     } else {
//       Serial.println("HTTP request failed");
//     }

//     http.end();
//   }

//   vTaskDelay(3000); // Wait for a while before making the next request
//   }
// }


