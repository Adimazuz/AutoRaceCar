#include "bitcraze_types.h"
#include "bitcrazeArd.h"

bitcraze motion_sensor;


void setup() {
  motion_sensor.setup();
  Serial.begin(9600); 
  Serial.flush();     
}
char c;


void loop() {
    if (Serial.available()) {
     c = Serial.read();     //gets one byte from serial buffer
    }
    
    if( c == START_STREAMING ){
      motion_sensor.sendData();
    }

    if( c == STOP_STREAMING ){
      Serial.flush();
    }

}
