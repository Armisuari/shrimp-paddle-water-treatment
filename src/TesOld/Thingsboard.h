#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ThingsBoard.h>

constexpr char WIFI_SSID[] PROGMEM = "YOUR_WIFI_SSID";
constexpr char WIFI_PASSWORD[] PROGMEM = "YOUR_WIFI_PASSWORD";

constexpr char TOKEN[] PROGMEM = "Ojz6j6cfFJgIJmz1ZIyh";

constexpr char THINGSBOARD_SERVER[] PROGMEM = "demo.thingsboard.io";
constexpr uint16_t THINGSBOARD_PORT PROGMEM = 1883U;
constexpr uint32_t MAX_MESSAGE_SIZE PROGMEM = 128U;
constexpr uint32_t SERIAL_DEBUG_BAUD PROGMEM = 115200U;
constexpr char TEMPERATURE_KEY[] PROGMEM = "temperature";
constexpr char HUMIDITY_KEY[] PROGMEM = "humidity";

WiFiClient espClient;
ThingsBoard tb(espClient, MAX_MESSAGE_SIZE);

void InitWiFi() {
  Serial.println(F("Connecting to AP ..."));
  // Attempting to establish a connection to the given WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    // Delay 500ms until a connection has been succesfully established
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F("Connected to AP"));
}
bool reconnect() {
  // Check to ensure we aren't connected yet
  const wl_status_t status = WiFi.status();
  if (status == WL_CONNECTED) {
    return true;
  }
  // If we aren't establish a new connection to the given WiFi network
  InitWiFi();
  return true;
}

void setup() {
  // If analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(34));
  // Initalize serial connection for debugging
  Serial.begin(SERIAL_DEBUG_BAUD);
  delay(1000);
  InitWiFi();
}

void loop() {
  delay(1000);

  if (!reconnect()) {
    return;
  }

#if !USING_HTTPS
  if (!tb.connected()) {
    // Reconnect to the ThingsBoard server,
    // if a connection was disrupted or has not yet been established
    Serial.printf("Connecting to: (%s) with token (%s)\n", THINGSBOARD_SERVER, TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
      Serial.println(F("Failed to connect"));
      return;
    }
  }
#endif

  Serial.println(F("Sending temperature data..."));
  tb.sendTelemetryInt(TEMPERATURE_KEY, random(10, 31));

  Serial.println(F("Sending humidity data..."));
  tb.sendTelemetryFloat(HUMIDITY_KEY, random(40, 90));

#if !USING_HTTPS
  tb.loop();
#endif
}
