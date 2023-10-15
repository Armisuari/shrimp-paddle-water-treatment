#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "eFisheryFS";
const char* password = "123123123";

IPAddress staticIP(192, 168, 8, 200);  // Define your desired static IP address
IPAddress gateway(192, 168, 8, 1);      // Define your gateway IP address
IPAddress subnet(255, 255, 255, 0);     // Define your subnet mask

WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.config(staticIP, gateway, subnet);  // Set the static IP address here
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print the IP address to the serial monitor

  server.on("/data", HTTP_GET, [](void){
    String html = "<html><body><h1>ESP32 Server</h1><p>This is the /data page.</p></body></html>";
    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}