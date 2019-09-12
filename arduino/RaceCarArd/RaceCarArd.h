#include<Servo.h>


//#define DEBUG_MODE

//speed between -500 to 500
//min speed for forword 80
//angle between 50 to 140
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
	static constexpr int NUTRALE_SPEED_IN_MILI = 1500;
	static constexpr int ZERO_ANGLE_IN_MILI = 1000;
	static constexpr int STRIGHT_ANGLE = 1500;
	static constexpr int NUTRALE_SPEED = 90;
	static constexpr int COMMAND_DELAY = 0;
	
	String command;
	char input;
	int speed;
	int angle;
	Servo engine;
	Servo steering;

	public:


	RaceCarArd():speed(0),angle(STRIGHT_ANGLE){}

	//attach PWM's and arm engine. engine(5),steering(6)
	void setup(){
		engine.attach(5);
		steering.attach(6);
		for(int i=85;i<95;i++)
		{
			engine.write(i);
			delay(200);
		}
	}
	/**
	*sends command to motor and to steering to drive and speed and angle set in class
	*/
	void drive(){
		engine.writeMicroseconds(NUTRALE_SPEED_IN_MILI + speed);
		steering.writeMicroseconds(ZERO_ANGLE_IN_MILI  + angle);
		//delay(10);
	}
	/**
	* stops car and set wheels to 90 degree angle
	*/
    void stop(){
     speed = 0;
     angle = 500;
     drive();
  }
	/**
	*when changing from forewords to revers this function needs to be called
	*before changing speed use this function
	*/
	void neutral() {
    engine.write(NUTRALE_SPEED);
    delay(300);
    
		for(int i=91;i<95;i++)
		{
			engine.write(i);
			delay(15);
		}
		speed = 0;
	}

	/**
	*waits for command to be writing ti Serial
	* command structure "<speed> <angle>" 
	* example "10 90"
	*/
	void getDriveCommand() {
		String speed_string;
		String angle_string;
    
		//this line make this a blocking function
		while (!Serial.available()) {};
		
		//get speed
		while (Serial.available()) {
			char c = Serial.read();  		//gets one byte from serial buffer
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
				neutral();
			}
			speed=wanted_speed;
			angle=wanted_angle;
		}
		speed_string = "";
		angle_string = "";
		drive();
	}

};
