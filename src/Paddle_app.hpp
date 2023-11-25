#include <Arduino.h>
#include <WifiHandler.h>
#include "mdns.h"
#include <ESPmDNS.h>
#include "config.h"

// mdns setup
const char *version = CONFIG_MAIN_FW_VERSION_STRING;
char clientID[sizeof(CONFIG_MAIN_CLIENT_ID_PREFIX) + 6];

WifiHandler wifi(CONFIG_MAIN_WIFI_DEFAULT_SSID, CONFIG_MAIN_WIFI_DEFAULT_PASS);
WiFiClient client;
const char *serverHostname = "tambak-dc75ec.local"; // Replace with your ESP32's IP address

void generateClientID(char *idBuff);
void setupMDNSResponder(char *hostname);
void connectToServer();
float getDOValue(String &msg);
String msgFromServer;

void setup()
{
    Serial.begin(115200);
    generateClientID(clientID);
    wifi.init();
    // MDNS
    setupMDNSResponder(clientID);
    delay(5000);

    if (MDNS.begin(serverHostname))
    {
        Serial.println("mDNS started");
    }
}

void loop()
{
    connectToServer();
    Serial.printf("DO Value from server: %4.2f\n", getDOValue(msgFromServer));
    delay(5000);
}

void connectToServer()
{
    if (client.connect(serverHostname, 80))
    {
        Serial.println("\nConnected to server");

        client.print("GET /GetData HTTP/1.1\r\n");
        client.print("Host: ");
        client.print(serverHostname);
        client.print("\r\n\r\n");

        delay(1000);

        // Read the server's response
        while (client.available())
        {
            char c = client.read();
            Serial.print(c);
            msgFromServer += c;
        }
        Serial.println();
        client.stop();
    }
    else
    {
        Serial.println("Connection to server failed");
    }
}

float getDOValue(String &msg)
{
    // Extract the DO value from the JSON response
    int doIndex = msg.indexOf("\"DO\":");
    if (doIndex != -1)
    {
        String _msg = msg.substring(doIndex + 6, msg.indexOf('}', doIndex));
        return _msg.toFloat();
    }
    else
    {
        Serial.println("DO value not found in the JSON response");
    }
    return 0.0;
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
    // Serial.printf("hosname: %s\n", hostname);
    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_init());
    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_hostname_set(hostname));
    ESP_LOGI("MAIN", "MDNS hostname: %s", hostname);

    // OTA Service decription
    mdns_txt_item_t serviceTxtData[4] = {
        {"HW version", "v1"},
        {"FW version", CONFIG_MAIN_FW_VERSION_STRING},
        {"Device", "client"},
        {"path", "/"}};

    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_service_add(NULL, "_http", "_tcp", 80, serviceTxtData, 3));
}