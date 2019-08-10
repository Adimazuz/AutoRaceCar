#include "RaceCarArd.h"
#include "bitcraze.h"
#include "Arduino_types.h"

RaceCarArd car;
bitcraze motion_sensor;

void setup() {
  car.setup();
  Serial.begin(9600); 
  Serial.flush();   
  
  }



void loop() {
  // car.updateTimers();
  //car.getKeyBoardInput();
  //  motion_sensor.getData();

   car.getDriveCommand();
}
