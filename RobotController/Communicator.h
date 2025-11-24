#ifndef COMMUNICATOR_H

#define COMMUNICATOR_H

#include <Arduino.h>

class Communicator {
  private:
    
  public:
    // Constructor
    Communicator();
    
    // Initialize pins
    void begin();
    
    //Different Tones
    void BeepOnce();

    // Measure distance in centimeters
    bool isBlack();
};

#endif