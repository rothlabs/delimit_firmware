/*
  Delimit Printer
*/

#include "sd_card.h"
#define LED_PIN 13

// the setup function runs once when you press reset or power the board
void setup() {
  led_setup(LED_PIN);
}

// the loop function runs over and over again forever
void loop() {
  led_on(LED_PIN);
  delay(100);
  led_off(LED_PIN);
  delay(100);
}
