/*
  Delimit Printer
*/

#include "extruder.h"
Extruder extruder;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  extruder.init();
}

// the loop function runs over and over again forever
void loop() {
  extruder.update();
  
} 

//#define DELAY_TIME 800
//#include "sd_card.h"
//SD_Card sd = SD_Card();
//sd.load_code();
// digitalWrite(LED_BUILTIN, HIGH); //led_on(LED_BUILTIN);
  // delay(DELAY_TIME);
  // digitalWrite(LED_BUILTIN, LOW); //led_off(LED_BUILTIN);
  // delay(DELAY_TIME);


