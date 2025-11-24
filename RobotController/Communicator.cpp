#include "Arduino.h"
#include "Communicator.h"


#define BUZZER 13
#define IR_SENSOR A3
// Constructor
Communicator::Communicator() {
  begin();
}

// Initialize pins
void Communicator::begin() {
  pinMode(BUZZER, OUTPUT);
}


void Communicator::BeepOnce(){
  tone(BUZZER, 5000);
  delay(600);
  noTone(BUZZER);
}

// Check if object is found within specified brightness threshold
bool Communicator::isBlack() {
  //TODO: Check if the Floor is black
  return true; // Placeholder implementation
}
