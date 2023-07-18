#include "sd_card.h"

void led_setup(byte pin){
  pinMode(pin, OUTPUT);
}

void led_on(byte pin){
  digitalWrite(pin, HIGH);
}

void led_off(byte pin){
  digitalWrite(pin, LOW);
}
