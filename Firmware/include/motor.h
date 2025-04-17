#include "Arduino.h"

class motor {

  public:
    
    motor(int motorPinA, int motorPinB, bool reversed);

    /**
    * @param speed Speed, from -255 to 255
    */
    void drive(int speed);

  private:

    int motorPinA, motorPinB;
};