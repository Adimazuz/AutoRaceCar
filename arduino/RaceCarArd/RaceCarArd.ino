#include "RaceCarArd.h"
#include "bitcraze.h"

RaceCarArd car;
bitcraze motion_sensor;

void setup() {
  // put your setup code here, to run once:
  car.setup();
  //motion_sensor.setup();
  Serial.begin(9600); 
}

char c;

void loop() {
  // put your main code here, to run repeatedly:
 // car.updateTimers();
  //car.getKeyBoardInput();
  car.getDriveCommand();
  //motion_sensor.getData();
}
