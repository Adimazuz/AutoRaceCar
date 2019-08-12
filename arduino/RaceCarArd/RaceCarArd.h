#include<Servo.h>
#include "timer.h"
#include "Arduino_types.h"
#include "bitcraze.h"

//#define DEBUG_MODE

//speed between -30 to 30
//min speed for forword 10
//angle between -50 to 140
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length()-1;

    for(int i=0; i<=maxIndex && found<=index; i++){
        if(data.charAt(i)==separator || i==maxIndex){
            found++;
            strIndex[0] = strIndex[1]+1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }

    return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
};

class RaceCarArd {
	static constexpr int TOP_SPEED = 30;
	static constexpr int MIN_ANGLE = 65;
	static constexpr int MAX_ANGLE = 125;
	static constexpr int NATURAL_SPEED = 90;
	static constexpr int COMMAND_DELAY = 0;
	
	String command;
	char input;
	int speed;
	int angle;
	Servo engine;
	Servo steering;
  Flow _data;
  bitcraze motion_sensor;
	public:


	RaceCarArd():speed(0),angle(90){}

	//attach PWM's and arm engine. engine(5),steering(6)
	void decreseToRest(){
		if(angle>90) {
			angle--;
		}else if (angle<90){
			angle++;
		}
		if(speed>0) {
			speed--;
		}else if(speed<0) {
			speed++;
		}
			drive();
	}
		
	void setup(){
		engine.attach(5);
		steering.attach(6);
		motion_sensor.setup();
		for(int i=85;i<95;i++)
		{
			engine.write(i);
			delay(200);
		}
	}
	
	void drive(){
		engine.write(NATURAL_SPEED + speed);
		steering.write(angle);
		//delay(10);
	}
	
	void increaseSpeed(){
		if(speed<TOP_SPEED ) {
			if(speed ==0){
				speed =10;
			}else if( speed == -5 ){
				speed=0;
			}else{
				speed++;
			}
		}
		drive();
	}
	
	void decreseSpeed(){
		if(speed>-TOP_SPEED ){
			if(speed ==0){
				neutral();
				speed =-5;
			}else if (speed ==10){
				speed =0;
			}else{
				speed--;
			}
		}
		drive();
	}
	
	void steerRight(){
		if(angle<MAX_ANGLE) {
			angle+=5;
		}
		drive();
	}
	
	void steerLeft(){
		if(angle>MIN_ANGLE ) {
			angle-=5;
		}
		drive();
	}
	
	void stop(){
		speed=0;
		angle=90;
		drive();
	}
	
	void rest(){
		speed=0;
		drive();
	}
	
	void setSpeed(int wanted_speed){
		speed=wanted_speed;
		drive();
	}
	void setAngle(int wanted_angle){
		angle=wanted_angle;
		steering.write(angle);
	}
	void updateTimer(){
		motion_sensor.updateTimer();
	}
	

	void neutral() {
		for(int i=91;i<95;i++)
		{
			engine.write(i);
			delay(15);
		}
		speed =0;
	}

  void getData() {
    _data = motion_sensor.getData();
  }
  
	void sendFlow(){
		Flow data = motion_sensor.getData ();
//    Serial.println(data.deltaX);
//    Serial.println(data.deltaY);
//    Serial.println(data.range);
//    Serial.println(data.t);

		Serial.write(reinterpret_cast<char*>(&data),sizeof(Flow));
	}
	
	void getDriveCommand() {
		String speed_string;
		String angle_string;
		//while (!Serial.available()) {};
		
		//get speed
		while (Serial.available()) {
			char c = Serial.read();  		//gets one byte from serial buffer
			if( c == '#' )					//if Flow data is asked for
			{	
				Serial.flush();	
				sendFlow();	
				return;	
			}	
			if(c== '\n' ){           		//to know if this is end of former cmd
				return;	
			}	
			speed_string += c; 				//makes the String speed_string
			delay(2);  						//slow looping to allow buffer to fill with next character
			if(c == ' ') break; 			// go to get angle
		}
		//get angle
		while (Serial.available()) {
			char c = Serial.read();  
			angle_string += c; 
			delay(2); 
		}

		if (speed_string.length() > 0 && angle_string.length()) {
			//if here we have a valid request
			int wanted_speed= speed_string.toInt(); 
			int wanted_angle= angle_string.toInt(); 
			
			//if we need to put in reverse
			if(speed >= 0 && wanted_speed < 0 )
			{
				speed=0;
				drive();
				delay(40);
				neutral();
			}
			speed=wanted_speed;
			angle=wanted_angle;
			
//		      Serial.flush();
//		      sendFlow();
		}
		speed_string = "";
		angle_string = "";
		
//    Serial.flush();
//    sendFlow(); 
		drive();
	}
	
	void getKeyBoardInput(){
		input = Serial.read();
		switch (input) {
			case 's' : {
			stop();
			break;
			}
			case 'u' : {
			increaseSpeed();
			break;
			}
			case 'd' : {
			decreseSpeed();
			break;
			}
			case 'l' : {
			steerLeft();
			break;
			}
			case 'r' :{
			steerRight();
			break;
			}
			case 'b' : {
			neutral();
			break;
			}
			default : drive();
		}
	}
	
};
