#ifndef EXTRUDER
#define EXTRUDER
#include <Arduino.h>
#include <AccelStepper.h>

byte Get_PWM(byte pin){
  unsigned long highTime = pulseIn(pin, HIGH, 50000UL);  // 50 millisecond timeout
  unsigned long lowTime = pulseIn(pin, LOW, 50000UL);  // 50 millisecond timeout
  // pulseIn() returns zero on timeout
  if (highTime == 0 || lowTime == 0)
    return digitalRead(pin) ? 100 : 0;  // HIGH == 100%,  LOW = 0%
  return (100 * highTime) / (highTime + lowTime);  // highTime as percentage of total cycle time
}

class Extruder {
  AccelStepper e_axis;
  const int input_pin = 33;
  public: void init(){
    const int dir_pin = 2;
    const int stp_pin = 3;
    //const int input_pin = 33;
    e_axis = AccelStepper(AccelStepper::DRIVER, dir_pin, stp_pin);
    pinMode(input_pin, INPUT);
  }
  public: void update(){
    byte pwm = Get_PWM(input_pin);
    Serial.println(pwm);
    delay(100);
  }
};

#endif