#include "ServerHandler.h"

#define serverTag "SERVER"

ServerHandler::ServerHandler(const char *apSSID) : apSSID_(apSSID)
{
    server = new WebServer(80);
}

ServerHandler::~ServerHandler()
{
}

bool ServerHandler::begin()
{
    // IPAddress staticIP(192, 168, 8, 200); // Define your desired static IP address
    // IPAddress gateway(192, 168, 8, 1);    // Define your gateway IP address
    // IPAddress subnet(255, 255, 255, 0);   // Define your subnet mask

    // if (!WiFi.config(staticIP, gateway, subnet))
    // {
    //     ESP_LOGW(serverTag, "Failed to active AP server");
    //     return false;
    // }
    // else
    // {
    // server.on("/tes", handleRoot);
    server->on("/GetData", [this]()
               {
            if(server)
            {
                server->send(200, "text/plain", receiveData_);
            } });
    server->begin();
    // ESP_LOGI(serverTag, "server activated with name '%s' and IP %s", apSSID_, WiFi.softAPIP().toString().c_str());
    ESP_LOGI(serverTag, "server activated with name '%s' and IP %s", apSSID_, WiFi.localIP().toString().c_str());
    // }

    // Create the task regardless of the connection status
    xTaskCreate(&ServerHandler::_staticTaskFunc,
                "server task handler",
                4096,
                this,
                1,
                NULL);

    return true;
}

void ServerHandler::postToClient(float storedVar)
{
    char buff[20];
    sprintf(buff,
            "{"
            "\"DO\": %4.2f"
            "}",
            storedVar);

    receiveData_ = String(buff);
}

/*STATIC*/ void ServerHandler::_staticTaskFunc(void *parameter)
{
    ServerHandler *serverObj = reinterpret_cast<ServerHandler *>(parameter);
    serverObj->_taskFunc();
}

void ServerHandler::_taskFunc()
{
    ESP_LOGI(serverTag, "Server Task Started !");
    while (1)
    {
        server->handleClient();
        // vTaskDelay(200);
    }
    delete server;
    vTaskDelete(NULL);
}