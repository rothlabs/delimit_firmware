#ifndef FLUID
#define FLUID
#include <Arduino.h>
#include <PWMServo.h>

class Fluid {
  PWMServo servo_h2o;
  const int servo_h2o_pin = 12;
  public: void init(){
    pinMode(servo_h2o_pin, OUTPUT);
    servo_h2o.attach(servo_h2o_pin, 500, 2500); //pinMode(servo_h2o_pin, OUTPUT);
  }
  public: void update(byte speed){ // byte speed
    //byte opening = (int)round(180 - speed*0.7);
    byte opening = speed*0.7;
    opening = map(opening, 0, 255, 45, 180);
    // if(opening < 75){
    //   opening = 75;
    // }
    // if(opening > 75){
    //   opening = 75;
    // }
    servo_h2o.write(opening);
    //Serial.println(opening);
    //delay(200); 
    //servo_h2o.write(180);
    //Serial.println("Servo: 180");
    //delay(500); 
  }
};


#endif