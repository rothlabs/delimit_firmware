/*
  Delimit Printer
  M3 S0 - stop extrusion 
  M3 S1000 - full flow extrusion
  M64 P0 - retract mode
  M65 P0 - regular extrusion
  M64 P1 - heat to target temp
  M65 P1 - heat off
*/

#include "heat.h"
#include "flow.h"
#include "step.h"

#define heat_pin_t2 0 // pwm
#define heat_pin_t3 1 // pwm
#define heat_pin_t4 2 // pwm

#define flow_pin_t1a 3 // pwm
#define flow_pin_t1b 4 // pwm
#define flow_pin_t1c 5 // pwm
#define flow_pin_t1d 6 // pwm

#define laser_pin_t5 7 // pwm
#define fiber_pin_t5 8 // pwm

#define therm_pin_t2 14 
#define therm_pin_t3 15 
#define therm_pin_t4 16 

#define air_pin_t1 26

#define step_pin_t2 30
#define step_pin_t3 31
#define step_pin_t4 32

#define cmd_pin_1 34
#define cmd_pin_2 35
#define cmd_pin_3 38
#define cmd_pin_4 39
#define cmd_pin_5 40

#define speed_pin 41

#define cmd_delay 10;
uint32_t cmd_change_time = 0;
byte cmd_potential = 0;

byte cmd       = 0;
byte speed     = 0;

Heat heat;
Flow flow;
Step step;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(heat_pin_t2,  OUTPUT);
  pinMode(heat_pin_t3,  OUTPUT);
  pinMode(heat_pin_t4,  OUTPUT);
  pinMode(flow_pin_t1a, OUTPUT);
  pinMode(flow_pin_t1b, OUTPUT);
  pinMode(flow_pin_t1c, OUTPUT);
  pinMode(flow_pin_t1d, OUTPUT);
  pinMode(laser_pin_t5, OUTPUT);
  pinMode(fiber_pin_t5, OUTPUT);
  pinMode(air_pin_t1,   OUTPUT);
  pinMode(step_pin_t2,  OUTPUT);
  pinMode(step_pin_t3,  OUTPUT);
  pinMode(step_pin_t4,  OUTPUT);

  pinMode(therm_pin_t2, INPUT);
  pinMode(therm_pin_t3, INPUT);
  pinMode(therm_pin_t4, INPUT);
  pinMode(cmd_pin_1,    INPUT);
  pinMode(cmd_pin_2,    INPUT);
  pinMode(cmd_pin_3,    INPUT);
  pinMode(cmd_pin_4,    INPUT);
  pinMode(cmd_pin_5,    INPUT);
  pinMode(speed_pin,    INPUT);

  Serial.begin(115200);
  
  heat.init();
  flow.init();
  step.init();
}

void read_cmd(){
  cmd_potential = digitalRead(cmd_pin_1) + digitalRead(cmd_pin_2)*2 + digitalRead(cmd_pin_3)*4 + digitalRead(cmd_pin_4)*8 + digitalRead(cmd_pin_5)*16;
  if(cmd_potential != cmd) cmd_change_time = millis();
  if(millis() - cmd_change_time > cmd_delay) cmd = cmd_potential;
}

void read_speed(){ // put this back in main program #1
  unsigned long high_time = pulseIn(speed_pin, HIGH, 5000UL);  // 50 millisecond timeout
  unsigned long low_time  = pulseIn(speed_pin, LOW, 5000UL);  // 50 millisecond timeout
  return (255 * high_time) / (high_time + low_time);  // highTime as percentage of total cycle time
}

void loop(){
  read_cmd();
  read_speed();
  heat.update(cmd, speed);  
  flow.update(cmd, speed);  
  step.update(cmd, speed);
} 




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


