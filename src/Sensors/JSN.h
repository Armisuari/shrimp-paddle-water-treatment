#pragma once
#include <Arduino.h>

class JSN
{
private:
    const long SERIAL_REFRESH_TIME = 100;
    long refresh_time;
    long durasi;   
    float cm, inch;
public:
    void init();
    int measure();
};
