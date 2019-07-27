#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>
#include "bitcraze.h"
#include "flow.h"



	void bitcraze::setup()
	{
		Bitcraze_PMW3901 flow(10);
		Serial.begin(9600);
		if (!flow.begin()) {
			Serial.println("Initialization of the flow sensor failed");
			while(1) { }
		}
		// Initialize range sensor
		Wire.begin();
		_rangeSensor.init();
		_rangeSensor.setTimeout(500);
	}
 
	void bitcraze::getData()
	{
		flow.readMotionCount(&_deltaX, &_deltaY);
		_range = _rangeSensor.readRangeSingleMillimeters();
		  Serial.print("X: ");
		Serial.print(_deltaX);
    //Serial.write(_deltaX);
		Serial.print(", Y: ");
		Serial.print(_deltaY);
   // Serial.write(_deltaY);
		Serial.print(", Range: ");
		if (_range > 5000) {
      Serial.write("N/A");
			//Serial.print("N/A");
		} else {
			Serial.print(_range);
      //Serial.Write(_range);
		}
		Serial.print("\n");

   //send data
   Flow data(_deltaX,_deltaY,_range);
   char*  p_to_send = (char *) &data;
   Serial.write( p_to_send,sizeof(Flow));
	}
