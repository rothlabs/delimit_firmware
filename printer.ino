/*
  Delimit Printer
  M3 S0 - stop extrusion 
  M3 S1000 - full flow extrusion
  M64 P0 - retract mode
  M65 P0 - regular extrusion
  M64 P1 - heat to target temp
  M65 P1 - heat off
*/

#include "extruder.h"
#include <thermistor.h>
#include <PID_v1.h>

const int heat_input_pin = 30;
const int heat_pin = 8;

Extruder extruder;
thermistor therm(A0, 0); // pin 14
double tmp_target, tmp_input, heat_output;
double Kp=15, Ki=0.3, Kd=0; // double Kp=2, Ki=5, Kd=1;
PID tmp_pid(&tmp_input, &heat_output, &tmp_target, Kp, Ki, Kd, DIRECT);
const int sample_interval = 1000;

unsigned long start = 0;
unsigned long end = 0;
unsigned long delta = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(heat_input_pin, INPUT);
  pinMode(heat_pin, OUTPUT);
  digitalWrite(heat_pin, LOW);
  Serial.begin(115200);
  //pinMode(LED_BUILTIN, OUTPUT);
  extruder.init();
  tmp_input = therm.analog2temp();
  tmp_target = 205; // 205 C
  tmp_pid.SetMode(AUTOMATIC);
  tmp_pid.SetSampleTime(sample_interval);
}

// the loop function runs over and over again forever
void loop() {


  //start = micros();

  ////Call to your function
  
  extruder.update();

  ////Compute the time it took
  //end = micros();
  //delta = end - start;
  //Serial.println(delta);
  if((millis() - start) > sample_interval){
    tmp_input = therm.analog2temp();
    if(digitalRead(heat_input_pin)){
      tmp_pid.Compute();
      analogWrite(heat_pin, heat_output);
    }else{
      analogWrite(heat_pin, 0);
    }
    //Serial.print("Set Point: ");
    //Serial.print(tmp_target);
    //Serial.println(" *C)");
    //Serial.print("Temperature: ");
    Serial.println(tmp_input);
    //Serial.println(" *C)");
    //Serial.print("PID output: ");
    //Serial.println(heat_output);
    start = millis();
  }
  //delay(sample_time);
} 

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


