#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    pinMode(16,INPUT_PULLUP);
    pinMode(17,INPUT_PULLUP);
}

void loop(){
    Serial.printf("Tombol 1 = %d\n", digitalRead(16));
    Serial.printf("Tombol 2 = %d\n", digitalRead(17));
    delay(500);
}