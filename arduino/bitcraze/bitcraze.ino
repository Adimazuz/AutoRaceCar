#include "Arduino_types.h"
#include "bitcraze.h"

bitcraze motion_sensor;


void setup() {
  motion_sensor.setup();
  Serial.begin(9600); 
  Serial.flush();     
}


void loop() {
    if (Serial.available()) {
      char c = Serial.read();     //gets one byte from serial buffer
      if ( c == '#' ) {
          motion_sensor.sendData();
      }

    }
}
