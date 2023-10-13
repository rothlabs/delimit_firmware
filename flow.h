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
  PWMServo cap;
  byte selector = 0;
  public: void init(){
    flow_t1a.attach(flow_pin_t1a, 500, 2500); 
    flow_t1b.attach(flow_pin_t1b, 500, 2500);
    flow_t1c.attach(flow_pin_t1c, 500, 2500);
    flow_t1d.attach(flow_pin_t1d, 500, 2500);
    cap.attach(cap_pin,           500, 2500);
    flow_t1a.write(flow_off_t1a);
    flow_t1b.write(flow_off_t1b);
    flow_t1c.write(flow_off_t1c);
    flow_t1d.write(flow_off_t1d);
    cap.write(cap_closed);
  }
  private: void close_cap(){
    //cap.write(cap_closed+2);
    //delay(1300);
    cap.write(cap_closed);
  }
  public: void update(byte cmd, byte pwm){ // byte speed
    if(cmd==0 || cmd==12 || cmd==13 || cmd==14 || cmd==15){ // idle, t2, t3, t4, t5 
      selector = 0;
      flow_t1a.write(flow_off_t1a);
      flow_t1b.write(flow_off_t1b);
      flow_t1c.write(flow_off_t1c);
      flow_t1d.write(flow_off_t1d);
      //close_cap(); // cap.write(cap_closed);
    }else if(cmd == 9){ // h2o
      selector = 1;
      //flow_t1a.write(flow_on_t1a);
      flow_t1b.write(flow_off_t1b);
      flow_t1c.write(flow_off_t1c);
      flow_t1d.write(flow_off_t1d);
    }else if(cmd == 10){ // pva
      selector = 2;
      flow_t1a.write(flow_off_t1a);
      //flow_t1b.write(flow_on_t1b);
      flow_t1c.write(flow_off_t1c);
      flow_t1d.write(flow_off_t1d);
    }else if(cmd == 11){ // pu components
      selector = 3;
      flow_t1a.write(flow_off_t1a);
      flow_t1b.write(flow_off_t1b);
      //flow_t1c.write(flow_on_t1c);
      //flow_t1d.write(flow_on_t1d);
    }else if(cmd == 18){
      close_cap(); // cap.write(cap_closed);
    }else if(cmd == 19){
      cap.write(cap_open);
    }else if(cmd == 20){
      cap.write(cap_mixer);
    }
    if(selector == 1){
      //flow_t1a.write(map(pwm, 0, 255, flow_off_t1a, flow_on_t1a));
      if(pwm > 128) flow_t1a.write(flow_on_t1a);
      else flow_t1a.write(flow_off_t1a);
    }else if(selector == 2){
      if(pwm > 128) flow_t1b.write(flow_on_t1b);
      else flow_t1b.write(flow_off_t1b);
    }else if(selector == 3){
      flow_t1c.write(map(pwm, 0, 255, flow_off_t1c, flow_on_t1c));
      flow_t1d.write(map(pwm, 0, 255, flow_off_t1d, flow_on_t1d));
    }
  }
};

#endif


    //flow_t1b.write(map(pwm, 0, 255, flow_off_t1b, flow_on_t1b));

  //byte prev_cmd = 0;
  //byte prev_pwm = 0;

    // if(prev_cmd == cmd && prev_pwm == pwm) return;
    // prev_cmd = cmd;
    // prev_pwm = pwm;
    // Serial.print("Cmd pwm change: ");
    // Serial.print(cmd);
    // Serial.print(", ");
    // Serial.println(pwm);


//byte opening = (int)round(180 - speed*0.7);
//byte flow = speed*0.7;