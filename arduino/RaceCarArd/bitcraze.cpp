#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>
#include "bitcraze.h"
#include "Arduino_types.h"



	void bitcraze::setup() {
		Serial.begin(9600);
		if (!flow.begin()) {
		  //Serial.println("Initialization of the flow sensor failed");
		//while(1) { }
		}
		timer.start();
    timer2 = millis();

		// Initialize range sensor
		Wire.begin();
		_rangeSensor.init();
		_rangeSensor.setTimeout(500);
	}
  
	void bitcraze::updateTimer() {
		timer.update();
	}

  
	Flow bitcraze::getData() {
    int x,y;
	  flow.readMotionCount(&x, &y);
	  float z = _rangeSensor.readRangeSingleMillimeters();
	  if (_range > 5000) {
        //Serial.write("N/A");
	  }
    short t2 = timer2 - millis();
    timer2 = millis();
   // short t = timer.getElapsedTime();
//    timer.reset();
   //maybe remove delay
    delay(50);
    Flow data = {x, y, z, t2};
    return data;
	}
