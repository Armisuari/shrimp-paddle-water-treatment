#include "Sensors/JSN.h"
#define pintriger 19
#define pinecho 18

void JSN::init(){
    pinMode (pintriger, OUTPUT);
    pinMode (pinecho, INPUT);
}

int JSN::measure(){
    digitalWrite (pintriger, 0);
    delayMicroseconds(2);
    digitalWrite (pintriger, 1);
    delayMicroseconds(10);
    digitalWrite (pintriger, 0);
    delayMicroseconds(2);
    
    durasi = pulseIn(pinecho, HIGH);
    float lastcm = cm;
    cm = (durasi * 0.0343)/2;
    if (cm == 0)
    {
        cm=lastcm;
    }

    return cm;
}