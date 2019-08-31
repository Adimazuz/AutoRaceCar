#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>
#include "bitcrazeArd.h"
#include "Arduino_types.h"


/**
* start both sensors in bitcraze
*/
	void bitcraze::setup() {
		if (!flow.begin()) {
		  Serial.println("Initialization of the flow sensor failed");
		//while(1) { }
		}
		timer = millis();

		// Initialize range sensor
		Wire.begin();
		_rangeSensor.init();
		_rangeSensor.setTimeout(500);
	}
  /**
  * sends data trough serial to computer
  */
  	void bitcraze::sendData(){
		Flow data = getData ();
   // Serial.print("X: ");
   // Serial.println(data.deltaX);
   // Serial.print("Y: ");
   // Serial.println(data.deltaY);
  // Serial.print("R: ");
    //Serial.println(data.range);
   // Serial.print("T: ");
   // Serial.println(data.mili_sec);

		Serial.write(reinterpret_cast<char*>(&data),sizeof(Flow));
	}
	/**
	* requests data from bitcraze
	*/
	Flow bitcraze::getData() {
    int x,y;
	  flow.readMotionCount(&x, &y);
	  float z = _rangeSensor.readRangeSingleMillimeters();

    short t2 = millis() -timer;
    timer = millis();
   // short t = timer.getElapsedTime();
//    timer.reset();
   //maybe remove delay
    //delay(50);
    Flow data = {x, y, z, t2};
    return data;
	}
	/**
	*stops sending data to computer
	*/
 void bitcraze::stopstreaming(){
  
  
 }
