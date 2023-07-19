/*
  Delimit Printer
*/

#include "sd_card.h"
#include "stepper.h"
#define DELAY_TIME 200 // BUILTIN_LED

SD_Card sd = SD_Card();

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  sd.load_code();
  stepper_setup();
}

// the loop function runs over and over again forever
void loop() {
  led_on(LED_BUILTIN);
  delay(DELAY_TIME);
  led_off(LED_BUILTIN);
  delay(DELAY_TIME);
} 


