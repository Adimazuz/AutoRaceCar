#include "RaceCarArd.h"

RaceCarArd car;

bool flag =true;

void setup() {
  car.setup();
  Serial.begin(9600); 
  Serial.flush();     
}


void loop() {
  car.getDriveCommand();
  if (!Serial) {
    car.stop();
  }
}
