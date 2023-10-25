/*
  Delimit Printer
*/

#include "global.h"
#include "heat.h"
#include "flow.h"
#include "step.h"

// Settings
const byte cmd_resolve_interval = 10;
const byte pwm_shift = 1; 

// State
uint32_t cmd_potential_change_time = 0;
byte prev_cmd_potential  = 0;
byte cmd = 0;
byte pwm = 0;
byte prev_cmd = 0;
byte prev_pwm = 0;
Heat heat;
Flow flow;
Step step;

void setup() {
  pinMode(air_pin_t1,   OUTPUT);
  pinMode(heat_pin_t2,  OUTPUT);
  pinMode(heat_pin_t3,  OUTPUT);
  pinMode(heat_pin_t4,  OUTPUT);
  pinMode(flow_pin_t1a, OUTPUT);
  pinMode(flow_pin_t1b, OUTPUT);
  pinMode(flow_pin_t1c, OUTPUT);
  //pinMode(flow_pin_t1d, OUTPUT);
  //pinMode(laser_pin_t5, OUTPUT);
  //pinMode(fiber_pin_t5, OUTPUT);
  pinMode(dir_pin_t2,   OUTPUT);
  pinMode(stp_pin_t2,   OUTPUT);
  pinMode(enb_pin_t2,   OUTPUT);
  pinMode(dir_pin_t3,   OUTPUT);
  pinMode(stp_pin_t3,   OUTPUT);
  pinMode(enb_pin_t3,   OUTPUT);
  pinMode(dir_pin_t4,   OUTPUT);
  pinMode(stp_pin_t4,   OUTPUT);
  pinMode(enb_pin_t4,   OUTPUT);
  pinMode(spin_pin_t2,  OUTPUT);
  pinMode(spin_pin_t3,  OUTPUT);
  pinMode(spin_pin_t4,  OUTPUT);
  pinMode(cap_pin,      OUTPUT);
  pinMode(ready_pin_t2, OUTPUT);
  pinMode(ready_pin_t3, OUTPUT);
  pinMode(ready_pin_t4, OUTPUT);

  pinMode(therm_pin_t2, INPUT);
  pinMode(therm_pin_t3, INPUT);
  pinMode(therm_pin_t4, INPUT);
  pinMode(cmd_pin_1,    INPUT);
  pinMode(cmd_pin_2,    INPUT);
  pinMode(cmd_pin_3,    INPUT);
  pinMode(cmd_pin_4,    INPUT);
  pinMode(cmd_pin_5,    INPUT);
  pinMode(cmd_pin_6,    INPUT);
  pinMode(pwm_pin,      INPUT);

  Serial.begin(115200);
  
  heat.init();
  flow.init();
  step.init();
}

void read_cmd(){
  byte cmd_potential = digitalRead(cmd_pin_1) + digitalRead(cmd_pin_2)*2 + digitalRead(cmd_pin_3)*4 + digitalRead(cmd_pin_4)*8 + digitalRead(cmd_pin_5)*16;// + digitalRead(cmd_pin_6)*32;
  if(prev_cmd_potential != cmd_potential){
    prev_cmd_potential = cmd_potential;
    cmd_potential_change_time = millis();
  }
  if(cmd != cmd_potential && millis() - cmd_potential_change_time > cmd_resolve_interval){
    cmd = cmd_potential;
  }
}

void read_var(){ // put this back in main program #1
  unsigned long high_time = pulseIn(pwm_pin, HIGH, 5000UL);  // 50 millisecond timeout
  unsigned long low_time  = pulseIn(pwm_pin, LOW,  5000UL);  // 50 millisecond timeout
  byte pwm_potential = (255 * high_time) / (high_time + low_time);  // highTime as percentage of total cycle time
  if(pwm < pwm_potential - pwm_shift || pwm > pwm_potential + pwm_shift) pwm = pwm_potential;
}

void loop(){
  read_cmd();
  read_var();
  heat.run();
  step.run();
  if(prev_cmd == cmd && prev_pwm == pwm) return;
  prev_cmd = cmd;
  prev_pwm = pwm;
  //Serial.print("Cmd, pwm: ");
  //Serial.print(cmd);
  //Serial.print(", ");
  //Serial.println(pwm);
  heat.update(cmd, pwm);  
  flow.update(cmd, pwm); 
  step.update(cmd, pwm); 
} 



// Serial.print("Cmd, pwm: ");
  // Serial.print(cmd);
  // Serial.print(", ");
  // Serial.println(pwm);

  // if(prev_cmd != cmd){
  //   Serial.print("Cmd: ");
  //   Serial.println(cmd);
  //   if() return;
  // }

    // Serial.println("Command Changed!");
    // Serial.print("Cmd Code: ");
    // Serial.println(cmd);
    // Serial.print("Cmd Pin 1: ");
    // Serial.println(digitalRead(cmd_pin_1));
    // Serial.print("Cmd Pin 2: ");
    // Serial.println(digitalRead(cmd_pin_2));
    // Serial.print("Cmd Pin 3: ");
    // Serial.println(digitalRead(cmd_pin_3));
    // Serial.print("Cmd Pin 4: ");
    // Serial.println(digitalRead(cmd_pin_4));
    // Serial.print("Cmd Pin 5: ");
    // Serial.println(digitalRead(cmd_pin_5));
    // Serial.print("Cmd Pin 6: ");
    // Serial.println(digitalRead(cmd_pin_6));



// byte read_pwm(byte pin){ // put this back in main program #1
//   unsigned long high_time = pulseIn(pin, HIGH, 5000UL);  // 50 millisecond timeout
//   unsigned long low_time  = pulseIn(pin, LOW, 5000UL);  // 50 millisecond timeout
//   return (255 * high_time) / (high_time + low_time);  // highTime as percentage of total cycle time
// }


  // pulseIn() returns zero on timeout
  //if (highTime == 0 || lowTime == 0)
  //  return digitalRead(pin) ? 255 : 0;  // HIGH == 100%,  LOW = 0%



//pinMode(LED_BUILTIN, OUTPUT);

  // double temp = therm.analog2temp(); // read temperature
  // //Print temperature in port serial
  // Serial.print("Temperatura: "); 
  // Serial.println((String)temp);
  // Serial.print("----------------------");
  // delay(1000); //wait 2000 mS for next measure

//#define DELAY_TIME 800
//#include "sd_card.h"
//SD_Card sd = SD_Card();
//sd.load_code();
// digitalWrite(LED_BUILTIN, HIGH); //led_on(LED_BUILTIN);
  // delay(DELAY_TIME);
  // digitalWrite(LED_BUILTIN, LOW); //led_off(LED_BUILTIN);
  // delay(DELAY_TIME);


