#ifndef FLOW
#define FLOW
#include <Arduino.h>
#include <PWMServo.h>

class Flow {
  PWMServo servo_h2o;
  PWMServo servo_pva;
  const int servo_h2o_pin = 9;
  const int servo_pva_pin = 10;
  //const int servo_pu1_pin = 11;
  //const int servo_pu2_pin = 12;
  const h2o_closed = 45;
  const h2o_open = 180;
  const pva_closed = 45;
  const pva_open = 180;
  public: void init(){
    servo_h2o.attach(servo_h2o_pin, 500, 2500); //pinMode(servo_h2o_pin, OUTPUT);
    servo_pva.attach(servo_pva_pin, 500, 2500);
  }
  public: void update(byte mode, byte speed){ // byte speed
    byte flow = speed*0.7;
    if(mode == 4){
      servo_h2o.write(map(flow, 0, 255, h2o_closed, h2o_open));
    }else{
      servo_h2o.write(h2o_closed);
    }
    if(mode == 5){
      servo_h2o.write(map(flow, 0, 255, pva_closed, pva_open));
    }else{
      servo_h2o.write(pva_closed);
    }
  }
};

//byte opening = (int)round(180 - speed*0.7);


#endif