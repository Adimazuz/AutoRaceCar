#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>
#include "bitcraze.h"
#include "Arduino_types.h"



	void bitcraze::setup()
	{
		Serial.begin(9600);
    if (!flow.begin()) {
      Serial.println("Initialization of the flow sensor failed");
      //while(1) { }
    }

		// Initialize range sensor
		Wire.begin();
		_rangeSensor.init();
		_rangeSensor.setTimeout(500);
	}
 
	void bitcraze::getData()
	{
    int x ;
    int y ;
    float z ;
		flow.readMotionCount(&x, &y);
		z = _rangeSensor.readRangeSingleMillimeters();
		if (_range > 5000) {
      //Serial.write("N/A");
		}

   //maybe remove delay
    delay(50);
    
   //send data

  Flow data = {x, y, z};

  while(Serial.availableForWrite() <12) {};

   Serial.write(reinterpret_cast<char*>(&data.deltaX),2);
   delay(10);
   Serial.write(reinterpret_cast<char*>(&data.deltaY),2);
   delay(10);
   Serial.write(reinterpret_cast<char*>(&data.range),4);
   delay(10);

	}
