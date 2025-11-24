#include "UltrasonicSensor.h"

// Constructor
UltrasonicSensor::UltrasonicSensor(int trig, int echo) {
  triggerPin = trig;
  echoPin = echo;
  duration = 0;
  distanceCm = 0;
  begin();
}

// Initialize pins
void UltrasonicSensor::begin() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// Measure distance in centimeters
float UltrasonicSensor::distance() {
  // Clear the trigger pin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  // Send 10 microsecond pulse to trigger
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Read the echo pin, returns pulse duration in microseconds
  duration = pulseIn(echoPin, HIGH, 12000); // 12ms timeout
  
  // Return 0 if no echo received (timeout)
  if (duration == 0) {
    return 999.0; // Return large value to indicate no object detected
  }

  // Calculate distance in cm (speed of sound = 343 m/s or 0.0343 cm/µs)
  // Distance = (duration / 2) * 0.0343
  distanceCm = (duration * 0.0343) / 2.0;
  
  
  
  return distanceCm;
}

// Check if object is found within specified distance
bool UltrasonicSensor::isFoundObject(float threshold) {
  float dist = distance();
  return (dist <= threshold && dist > 0);
}

// Get raw pulse duration
long UltrasonicSensor::getDuration() {
  return duration;
}