// #include <WiFi.h>
// #include <WebServer.h>

// const char* ssid = "eFisheryFS";
// const char* password = "123123123";

// IPAddress staticIP(192, 168, 8, 200);  // Define your desired static IP address
// IPAddress gateway(192, 168, 8, 1);      // Define your gateway IP address
// IPAddress subnet(255, 255, 255, 0);     // Define your subnet mask

// WebServer server(80);

// void setup() {
//   Serial.begin(115200);
//   WiFi.config(staticIP, gateway, subnet);  // Set the static IP address here
//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }

//   Serial.println("Connected to WiFi");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP()); // Print the IP address to the serial monitor

//   server.on("/data", HTTP_GET, [](void){
//     String html = "<html><body><h1>ESP32 Server</h1><p>This is the /data page.</p></body></html>";
//     server.send(200, "text/html", html);
//   });

//   server.begin();
// }

// void loop() {
//   server.handleClient();
// }

#include <Arduino.h>
#include <WifiHandler.h>
#include "mdns.h"
#include "config.h"
#include "ServerHandler.h"

// mdns setup
const char *version = CONFIG_MAIN_FW_VERSION_STRING;
char clientID[sizeof(CONFIG_MAIN_CLIENT_ID_PREFIX) + 6];

void generateClientID(char *idBuff);
void setupMDNSResponder(char *hostname);

WifiHandler wifi(CONFIG_MAIN_WIFI_DEFAULT_SSID, CONFIG_MAIN_WIFI_DEFAULT_PASS);
ServerHandler server("DevServer");

void setup()
{
  Serial.begin(115200);
  generateClientID(clientID); // Generate clientID based on MAC Addr

  // connectivity setup
  wifi.init();
  server.begin();

  // MDNS
  setupMDNSResponder(clientID);
}

void loop()
{
  server.postToClient(random(24, 39));
  vTaskDelay(5000);
}

void generateClientID(char *idBuff)
{
  const char *clientIdPrefix = CONFIG_MAIN_CLIENT_ID_PREFIX;
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);

  sprintf(idBuff, "%s%02X%02X%02X", clientIdPrefix, mac[3], mac[4], mac[5]);
}

void setupMDNSResponder(char *hostname)
{
  ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_init());
  ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_hostname_set(hostname));
  ESP_LOGI("MAIN", "MDNS hostname: %s", hostname);

  mdns_txt_item_t serviceTxtData[4] = {
      {"HW version", "v1"},
      {"FW version", CONFIG_MAIN_FW_VERSION_STRING},
      {"Device", "Server"},
      {"path", "/"}};

  ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_service_add(NULL, "_http", "_tcp", 80, serviceTxtData, 3));
}