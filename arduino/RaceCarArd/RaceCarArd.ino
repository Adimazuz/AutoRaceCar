#include "RaceCarArd.h"
//#include "bitcraze.h"
#include "Arduino_types.h"

RaceCarArd car;

bool flag =true;

void setup() {
  car.setup();
  Serial.begin(9600); 
  Serial.flush();     
}


void loop() {
  //car.getData();
  car.getDriveCommand();
  if (!Serial) {
    car.stop();
  }
}
