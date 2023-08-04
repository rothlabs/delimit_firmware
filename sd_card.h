#ifndef SD_CARD
#define SD_CARD
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class SD_Card {
  File file;
  public: void load_code(){
    /*
    SD card read/write

    This example shows how to read and write data to and from an SD card file
    The circuit:
      SD card attached to SPI bus as follows:
    ** MOSI - pin 11
    ** MISO - pin 12
    ** CLK - pin 13
    ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

    created   Nov 2010
    by David A. Mellis
    modified 9 Apr 2012
    by Tom Igoe

    This example code is in the public domain.
    */

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.print("Initializing SD card...");

    if (!SD.begin(BUILTIN_SDCARD)) {
      Serial.println("initialization failed!");
      while (1);
    }
    Serial.println("initialization done.");

    // open the file for reading:
    file = SD.open("dlmt.nc");
    if (file) {
      Serial.println("dlmt.nc:");

      // read from the file until there's nothing else in it:
      while (file.available()) {
        Serial.write(file.read());
      }
      // close the file:
      file.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening dlmt.nc");
    }
  };
};
//void led_on(byte pin);
//void led_off(byte pin);
// void led_on(byte pin){
//   digitalWrite(pin, HIGH);
// }

// void led_off(byte pin){
//   digitalWrite(pin, LOW);
// }

#endif