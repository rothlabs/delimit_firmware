#ifndef HEAT
#define HEAT
#include <Arduino.h>
#include <thermistor.h>
#include <PID_v1.h>
#include <TMCStepper.h>
#include "teensystep4.h"
#include "global.h"

using namespace TS4;

Stepper spinner_t3(spin_pin_t3, 17);
TMC2208Stepper spin_driver(&STEPPER_SERIAL_PORT, R_SENSE);

double pid_target_t2 = 220; // pla
double pid_target_t3 = 200; // tpu
double pid_target_t4 = 230; // tpu
double pid_input_t2, pid_input_t3, pid_input_t4;
double pid_output_t2, pid_output_t3, pid_output_t4;
double Kp=15, Ki=0.3, Kd=0; // double Kp=2, Ki=5, Kd=1;
thermistor therm_t2(therm_pin_t2, 0); //therm_pin_t2
thermistor therm_t3(therm_pin_t3, 0); 
thermistor therm_t4(therm_pin_t4, 0); 
PID pid_t2(&pid_input_t2, &pid_output_t2, &pid_target_t2, Kp, Ki, Kd, DIRECT);
PID pid_t3(&pid_input_t3, &pid_output_t3, &pid_target_t3, Kp, Ki, Kd, DIRECT);
PID pid_t4(&pid_input_t4, &pid_output_t4, &pid_target_t4, Kp, Ki, Kd, DIRECT);

class Heat {
  uint32_t sample_interval = 500;
  uint32_t sample_time = 0;
  bool heat_t2 = false;
  bool heat_t3 = false;
  bool heat_t4 = false;
  // bool heat_ready_t2 = false;
  // bool heat_ready_t3 = false;
  // bool heat_ready_t4 = false;
  int spin_speed = 6667; // should be 1000 rpm
  public: void init(){
    STEPPER_SERIAL_PORT.begin(115200);
    spin_driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins  // UART: Init SW UART (if selected) with default 115200 baudrate
    spin_driver.toff(5);                 // Enables driver in software
    spin_driver.rms_current(600);        // Set motor RMS current
    spin_driver.microsteps(2);          // Set microsteps to 1/16th
    spin_driver.en_spreadCycle(true);   // Toggle spreadCycle on TMC2208/2209/2224

    TS4::begin();
    spinner_t3.setMaxSpeed(12000).setAcceleration(2000);
    //spinner_t3.rotateAsync(spin_speed);

    pid_input_t2 = therm_t2.analog2temp();
    pid_input_t3 = therm_t3.analog2temp();
    pid_input_t4 = therm_t4.analog2temp();
    pid_t2.SetMode(AUTOMATIC);
    pid_t3.SetMode(AUTOMATIC);
    pid_t4.SetMode(AUTOMATIC);
    pid_t2.SetSampleTime(sample_interval);
    pid_t3.SetSampleTime(sample_interval);
    pid_t4.SetSampleTime(sample_interval);
    digitalWrite(air_pin_t1, LOW);
    analogWrite(heat_pin_t2, 0);
    analogWrite(heat_pin_t3, 0);
    analogWrite(heat_pin_t4, 0);
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
      spinner_t3.stop(); //spinner_t3.rotateAsync(0);
      // heat_ready_t2 = false;
      // heat_ready_t3 = false;
      // heat_ready_t4 = false;
    }else if(cmd == 1){
      digitalWrite(air_pin_t1, LOW);
    }else if(cmd == 2){
      heat_t2 = false;
      //heat_ready_t2 = false;
      analogWrite(heat_pin_t2, 0);
    }else if(cmd == 3){
      heat_t3 = false;
      //heat_ready_t3 = false;
      analogWrite(heat_pin_t3, 0);
    }else if(cmd == 4){
      heat_t4 = false;
      //heat_ready_t4 = false;
      analogWrite(heat_pin_t4, 0);
    }else if(cmd == 5){
      digitalWrite(air_pin_t1, HIGH);
    }else if(cmd == 6){
      heat_t2 = true;
    }else if(cmd == 7){
      heat_t3 = true;
      spinner_t3.rotateAsync(spin_speed);
    }else if(cmd == 8){
      heat_t4 = true;
    }
  }
  public: void run(){
    if(millis() - sample_time > sample_interval){
      if(heat_t2){
        pid_input_t2 = therm_t2.analog2temp();
        pid_t2.Compute();
        analogWrite(heat_pin_t2, pid_output_t2 * 16); // PWMServo or other lib called analogWriteResolution(12) (0-4095)?! #1
        //if(!heat_ready_t2){
          Serial.print("Temp T2: ");
          Serial.println(pid_input_t2);
        //  if(pid_input_t2 >= pid_target_t2) {
        //    heat_ready_t2 = true;
            //digitalWrite(ready_pin_t2, HIGH);
        //    Serial.println("Heat Ready T2");
        //  }
        //}
      }
      if(heat_t3){
        pid_input_t3 = therm_t3.analog2temp();
        pid_t3.Compute();
        analogWrite(heat_pin_t3, pid_output_t3 * 16);
        //if(!heat_ready_t3){
          Serial.print("Temp T3: ");
          Serial.println(pid_input_t3);
          //if(pid_input_t3 >= pid_target_t3) {
          //  heat_ready_t3 = true;
          //  //digitalWrite(ready_pin_t3, HIGH);
          //  Serial.println("Heat Ready T3");
          //}
        //}
      }
      if(heat_t4){
        pid_input_t4 = therm_t4.analog2temp();
        pid_t4.Compute();
        analogWrite(heat_pin_t4, pid_output_t4 * 16);
        Serial.print("Temp T4: ");
        Serial.println(pid_input_t4);
      }
      sample_time = millis();
    }
  }
};

#endif


//digitalWrite(heat_pin_t2, HIGH);
        //analogWrite(heat_pin_t2, 4000);
        //Serial.print("Output Heat T2: ");
        //Serial.println(pid_output_t2);


    //therm_t2 = thermistor(therm_pin_t2, 0); 
    //therm_t3 = thermistor(therm_pin_t3, 0); 
    //therm_t4 = thermistor(therm_pin_t4, 0); 
    //pid_t2 = PID(&pid_input_t2, &pid_output_t2, &pid_target_t2, Kp, Ki, Kd, DIRECT);
    //pid_t3 = PID(&pid_input_t3, &pid_output_t3, &pid_target_t3, Kp, Ki, Kd, DIRECT);
    //pid_t4 = PID(&pid_input_t4, &pid_output_t4, &pid_target_t4, Kp, Ki, Kd, DIRECT);