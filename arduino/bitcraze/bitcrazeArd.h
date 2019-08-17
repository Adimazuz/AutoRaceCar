#ifndef BITCRAZRE_HPP
#define BITCRAZRE_HPP
#include <VL53L0X.h>
#include "Bitcraze_PMW3901.h"
#include "Arduino_types.h"


class bitcraze {
  VL53L0X _rangeSensor;
  Bitcraze_PMW3901 flow;
  int16_t _deltaX,_deltaY;
  float _range;
  unsigned long timer = 0;

  
  public:
  bitcraze():_deltaX(0),_deltaY(0),_range(0),flow(10){}
  void setup();
  void updateTimer();
  void sendData();
  Flow getData();
};

#endif
