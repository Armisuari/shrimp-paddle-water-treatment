#pragma once

#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>

class ServerHandler
{
    public :
        ServerHandler(const char* apSSID);
        ~ServerHandler();

        bool begin();
        void postToClient(float storedVar);

    private :
        static void _staticTaskFunc(void *parameter);
        void _taskFunc();

        WebServer *server;
        const char* apSSID_;
        String receiveData_;
};