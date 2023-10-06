#include <Arduino.h>
class UltrasonicSensor {
private:
  const int triggerPin;
  const int echoPin;
  
public:
  UltrasonicSensor(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin) {}

  void setup() {
    Serial.begin(115200); // Baud rate for serial communication
    pinMode(triggerPin, OUTPUT); // Trigger pin defined as output
    pinMode(echoPin, INPUT);     // Echo pin defined as input
  }

  void measureDistance() {
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    float durationMicroSec = pulseIn(echoPin, HIGH);
    float distanceInCm = 0.018 * durationMicroSec;

    Serial.print("Distance: ");
    Serial.print(distanceInCm);
    Serial.println(" cm");

    delay(300);
  }
};

UltrasonicSensor sensor(19, 18); // Create an instance of the UltrasonicSensor class

void setup() {
  sensor.setup();
}

void loop() {
  sensor.measureDistance();
}
