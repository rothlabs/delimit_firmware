#ifndef EXTRUDER
#define EXTRUDER
#include <Arduino.h>
#include <AccelStepper.h>

byte Get_PWM(byte pin){
  unsigned long highTime = pulseIn(pin, HIGH, 5000UL);  // 50 millisecond timeout
  unsigned long lowTime = pulseIn(pin, LOW, 5000UL);  // 50 millisecond timeout
  // pulseIn() returns zero on timeout
  //if (highTime == 0 || lowTime == 0)
  //  return digitalRead(pin) ? 255 : 0;  // HIGH == 100%,  LOW = 0%
  return (255 * highTime) / (highTime + lowTime);  // highTime as percentage of total cycle time
}

class Extruder {
  AccelStepper stepper;
  const int speed_input_pin = 33;
  const int dir_input_pin = 36;
  const int aux1_input_pin = 34;
  const int aux2_input_pin = 35;
  const int stp_pin = 26;
  const int dir_pin = 27;
  const int enb_pin = 37;
  byte speed, dir; // uint8_t
  public: void init(){
    pinMode(speed_input_pin, INPUT);
    pinMode(dir_input_pin, INPUT);
    pinMode(aux1_input_pin, INPUT);
    pinMode(aux2_input_pin, INPUT);
    pinMode(stp_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(enb_pin, OUTPUT);
    stepper = AccelStepper(AccelStepper::DRIVER, stp_pin, dir_pin);
    //stepper.setAcceleration(10);
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(0);
    digitalWrite(dir_pin, LOW);
    digitalWrite(enb_pin, LOW); // ACTIVE LOW
  }
  public: void update(){
    //delay(500);
    
    //start = micros();
    // Call to your function
    speed = Get_PWM(speed_input_pin);
    dir = digitalRead(dir_input_pin);
    //int test_speed = (1-dir*2)*speed;
    stepper.setSpeed(speed*(1-dir*2));
    stepper.runSpeed();
    //Serial.println(test_speed);
    // Compute the time it took
    //end = micros();
    //delta = end - start;
    //Serial.println(delta);

    //Serial.println("hello");
    // delay(100);
    // digitalWrite(heat_pin, HIGH); //led_on(LED_BUILTIN);
    // delay(100);
    // digitalWrite(heat_pin, LOW); //led_off(LED_BUILTIN);
    // delay(100);
  }
};

#endif