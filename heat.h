#ifndef HEAT
#define HEAT
#include <Arduino.h>
#include <thermistor.h>
#include <PID_v1.h>
#include "global.h"

class Heat {
  double pid_target_t2 = 210; // pla
  double pid_target_t3 = 220; // tpu
  double pid_target_t4 = 220; // tpu
  double pid_input_t2, pid_input_t3, pid_input_t4;
  double pid_output_t2, pid_output_t3, pid_output_t4;
  double Kp=15, Ki=0.3, Kd=0; // double Kp=2, Ki=5, Kd=1;
  const int sample_interval = 1000;
  uint32_t sample_time = 0;
  thermistor therm_t2;
  thermistor therm_t3;
  thermistor therm_t4;
  PID pid_t2;
  PID pid_t3;
  PID pid_t4;
  bool heat_t2 = false;
  bool heat_t3 = false;
  bool heat_t4 = false;
  public: void init(){
    therm_t2 = thermistor(therm_pin_t2, 0); 
    therm_t3 = thermistor(therm_pin_t3, 0); 
    therm_t4 = thermistor(therm_pin_t4, 0); 
    pid_t2 = PID(&pid_input_t2, &pid_output_t2, &pid_target_t2, Kp, Ki, Kd, DIRECT);
    pid_t3 = PID(&pid_input_t3, &pid_output_t3, &pid_target_t3, Kp, Ki, Kd, DIRECT);
    pid_t4 = PID(&pid_input_t4, &pid_output_t4, &pid_target_t4, Kp, Ki, Kd, DIRECT);
    pid_input_t2 = therm_t2.analog2temp();
    pid_input_t3 = therm_t3.analog2temp();
    pid_input_t4 = therm_t4.analog2temp();
    pid_t2.SetMode(AUTOMATIC);
    pid_t3.SetMode(AUTOMATIC);
    pid_t4.SetMode(AUTOMATIC);
    pid_t2.SetSampleTime(sample_interval);
    pid_t3.SetSampleTime(sample_interval);
    pid_t4.SetSampleTime(sample_interval);
  }
  public: void update(byte cmd, byte pwm){
    if(cmd == 0){
      digitalWrite(air_pin_t1, LOW);
      analogWrite(heat_pin_t2, 0);
      analogWrite(heat_pin_t3, 0);
      analogWrite(heat_pin_t4, 0);
      heat_t2 = false;
      heat_t3 = false;
      heat_t4 = false;
    }else if(cmd == 1){
      digitalWrite(air_pin_t1, HIGH);
    }else if(cmd == 2){
      heat_t2 = true;
    }else if(cmd == 3){
      heat_t3 = true;
    }else if(cmd == 4){
      heat_t4 = true;
    }
    if(millis() - sample_time > sample_interval){
      if(heat_t2){
        pid_input_t2 = therm_t2.analog2temp();
        pid_t2.Compute();
        analogWrite(heat_pin_t2, pid_output_t2);
        Serial.print('Temp T2: ');
        Serial.println(pid_input_t2);
      }
      if(heat_t3){
        pid_input_t3 = therm_t3.analog2temp();
        pid_t3.Compute();
        analogWrite(heat_pin_t3, pid_output_t3);
        Serial.print('Temp T3: ');
        Serial.println(pid_input_t3);
      }
      if(heat_t4){
        pid_input_t4 = therm_t4.analog2temp();
        pid_t4.Compute();
        analogWrite(heat_pin_t4, pid_output_t4);
        Serial.print('Temp T4: ');
        Serial.println(pid_input_t4);
      }
      sample_time = millis();
    }
  }
};