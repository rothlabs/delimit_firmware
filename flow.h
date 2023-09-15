#ifndef FLOW
#define FLOW
#include <Arduino.h>
#include <PWMServo.h>
#include "global.h"

class Flow {
  PWMServo flow_t1a;
  PWMServo flow_t1b;
  PWMServo flow_t1c;
  PWMServo flow_t1d;
  byte prev_cmd = 0;
  byte prev_pwm = 0;
  byte flow_type = 0;
  //bool flow_t1b = false;
  //bool flow_t1c = false;
  public: void init(){
    flow_t1a.attach(flow_pin_t1a, 500, 2500); 
    flow_t1b.attach(flow_pin_t1b, 500, 2500);
    flow_t1c.attach(flow_pin_t1c, 500, 2500);
    flow_t1d.attach(flow_pin_t1d, 500, 2500);
  }
  public: void update(byte cmd, byte pwm){ // byte speed
    if(prev_cmd == cmd && prev_pwm == pwm) return;
    Serial.print("Cmd pwm change: ");
    Serial.print(cmd);
    Serial.print(", ");
    Serial.println(pwm);
    prev_cmd = cmd;
    prev_pwm = pwm;
    if(cmd==0 || cmd==12 || cmd==13 || cmd==14 || cmd==15){ // idle, t2, t3, t4, t5
      //flow_t1a = false;
      //flow_t1b = false;
      //flow_t1c = false;
      flow_type = 0;
      flow_t1a.write(flow_off_t1a);
      flow_t1b.write(flow_off_t1b);
      flow_t1c.write(flow_off_t1c);
      flow_t1d.write(flow_off_t1d);
    }else if(cmd == 9){ // h2o
      flow_type = 1;
      flow_t1b.write(flow_off_t1b);
      flow_t1c.write(flow_off_t1c);
      flow_t1d.write(flow_off_t1d);
      //flow_t1a = true;
      //flow_t1b = false;
      //flow_t1c = false;
    }else if(cmd == 10){ // pva
      flow_type = 2;
      flow_t1a.write(flow_off_t1a);
      flow_t1c.write(flow_off_t1c);
      flow_t1d.write(flow_off_t1d);
      //flow_t1a = false;
      //flow_t1b = true;
      //flow_t1c = false;
    }else if(cmd == 11){ // pu components
      flow_type = 3;
      flow_t1a.write(flow_off_t1a);
      flow_t1b.write(flow_off_t1b);
      //flow_t1a = false;
      //flow_t1b = false;
      //flow_t1c = true;
    }
    if(flow_type == 1){
      flow_t1a.write(map(pwm, 0, 255, flow_off_t1a, flow_on_t1a));
    }else if(flow_type == 2){
      flow_t1b.write(map(pwm, 0, 255, flow_off_t1b, flow_on_t1b));
    }else if(flow_type == 3){
      flow_t1c.write(map(pwm, 0, 255, flow_off_t1c, flow_on_t1c));
      flow_t1d.write(map(pwm, 0, 255, flow_off_t1d, flow_on_t1d));
    }
  }
};

#endif


//byte opening = (int)round(180 - speed*0.7);
//byte flow = speed*0.7;