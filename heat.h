#ifndef HEAT
#define HEAT
#include <Arduino.h>
#include <thermistor.h>
#include <PID_v1.h>


class Heat {
  double pid_target_t2, pid_input_t2, pid_output_t2;
  double Kp=15, Ki=0.3, Kd=0; // double Kp=2, Ki=5, Kd=1;
  const int sample_interval = 1000;
  uint32_t sample_time = 0;
  public: void init(){
    therm_t2 = therm(therm_pin_t2, 0); 
    therm_t3 = therm(therm_pin_t3, 0); 
    therm_t4 = therm(therm_pin_t4, 0); 
    PID pid_t2(&pid_input_t2, &pid_output_t2, &pid_target_t2, Kp, Ki, Kd, DIRECT);
    pid_input_t2 = therm.analog2temp();
    pid_target_t2 = 205; // 205 C
    pid_t2.SetMode(AUTOMATIC);
    pid_t2.SetSampleTime(sample_interval);
  }
  public: void update(byte mode, byte speed){
    ////Compute the time it took
    //end = micros();
    //delta = end - start;
    //Serial.println(delta);
    if(millis() - sample_time > sample_interval){
      pid_input_t2 = therm_t2.analog2temp();
      if(digitalRead(heat_input_pin)){
        pid_t2.Compute();
        analogWrite(heat_pin, pid_output_t2);
      }else{
        analogWrite(heat_pin, 0);
      }
      Serial.println(pid_input_t2);
      sample_time = millis();
    }
    //delay(sample_time);
  }
};