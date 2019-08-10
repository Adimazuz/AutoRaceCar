#include <VL53L0X.h>
#include "Bitcraze_PMW3901.h"

class bitcraze {
  VL53L0X _rangeSensor;
  Bitcraze_PMW3901 flow;
  int16_t _deltaX,_deltaY;
  float _range;
  
  public:
  bitcraze():_deltaX(0),_deltaY(0),_range(0),flow(10){}
  void setup();
  void getData();
};
