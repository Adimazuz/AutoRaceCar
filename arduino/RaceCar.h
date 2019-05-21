#include<Servo.h>
#include "timer.h"

//speed between -0 to 20
//angle between -65 to 125

class RaceCar {
	static constexpr int TOP_SPEED = 20;
	static constexpr int MIN_ANGLE = 65;
	static constexpr int MAX_ANGLE = 125;
	static constexpr int NATURAL_SPEED = 90;
	static constexpr int COMMAND_DELAY = 50;

	char input;
	int speed;
	int angle;
	bool flag = false;
	Servo engine;
	Servo steering;
	Timer engineTimer;
	Timer steeringTimer;
	public:

RaceCar():speed(0),angle(90){}

//attach PWM's and arm engine.
void setup(){
		  engine.attach(9);
		  steering.attach(10);
  for(int i=80;i<90;i++)
  {
    engine.write(i);
    delay(200);
  }
		  engineTimer.start();
		  steeringTimer.start();
}
void drive(){
	engine.write(NATURAL_SPEED + speed);
	//Serial.print("Drive inst: ");
	//Serial.println(NATURAL_SPEED + speed);
	steering.write(angle);
	delay(40);
}
void increaseSpeed(){
	if(speed<TOP_SPEED && engineTimer.getElapsedTime()>COMMAND_DELAY) {
		if(speed ==0){
			speed =10;
		}else if(speed ==-5){
			speed=0;
		}else{
		speed++;
			}
		Serial.print("speed: ");
		Serial.println(speed);
		engineTimer.reset();
	}
	//Serial.println("max speed");
	drive();
}
void decreseSpeed(){
	if(speed>-TOP_SPEED && engineTimer.getElapsedTime()>COMMAND_DELAY){
		if(speed ==0){
			neutral();
			speed =-5;
		}else if (speed ==10){
			speed =0;
		}else{
		speed--;
			}		
		Serial.print("speed: ");
		Serial.println(speed);
		engineTimer.reset();
	}
	drive();
}
void steerRight(){
	if(angle<MAX_ANGLE && steeringTimer.getElapsedTime()>COMMAND_DELAY) {
		angle+=5;
		Serial.print("angle: ");
		Serial.println(angle);
		steeringTimer.reset();
	}
	steering.write(angle);

}
void steerLeft(){
	if(angle>MIN_ANGLE && steeringTimer.getElapsedTime()>COMMAND_DELAY ) {
		angle-=5;
		Serial.print("angle: ");
		Serial.println(angle);
		steeringTimer.reset();
	}
	steering.write(angle);
}
void stop(){
	speed=0;
	angle=90;
}
void setSpeed(int wanted_speed){
	speed=wanted_speed;
	drive();
}
void setAngle(int wanted_angle){
	angle=wanted_angle;
	steering.write(angle);
}
void updateTimers(){
	engineTimer.update();
    steeringTimer.update();
}
void IncreaseSpeedPrint(){
		if(engineTimer.getElapsedTime()>COMMAND_DELAY) {
		//speed++;
		Serial.println(1);
		engineTimer.reset();
		}
	//drive();
	}
void neutral(){
 for(int i=91;i<95;i++)
 {
   engine.write(i);
   delay(40);
 }
 speed =0;
}
void handleInput(){
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

