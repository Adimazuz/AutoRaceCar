#include "RaceCarArd.h"

RaceCarArd car;

void setup() {
  // put your setup code here, to run once:
  car.setup();
  Serial.begin(9600); 
}

char c;

void loop() {
  // put your main code here, to run repeatedly:
  car.updateTimers();
  //car.getKeyBoardInput();
  car.getDriveCommand();
}
