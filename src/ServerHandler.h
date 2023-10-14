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
        void postToClient(String storedVar);

    private :
        static void _staticTaskFunc(void *parameter);
        void _taskFunc();

        WebServer *server;
        const char* apSSID_;
        String receiveData_ = "23";
};