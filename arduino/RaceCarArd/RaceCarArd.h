#include<Servo.h>
#include "timer.h"
#include "Arduino_types.h"

//#define DEBUG_MODE

//speed between -20 to 20
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
  //bitcraze motion_sensor;
  Timer engineTimer;
  Timer steeringTimer;
  public:

RaceCarArd():speed(0),angle(90){}

//attach PWM's and arm engine.
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
     // motion_sensor.setup();
  for(int i=85;i<95;i++)
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
  //5delay(10);
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
  drive();

}
void steerLeft(){
  if(angle>MIN_ANGLE && steeringTimer.getElapsedTime()>COMMAND_DELAY ) {
    angle-=5;
    Serial.print("angle: ");
    Serial.println(angle);
    steeringTimer.reset();
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
void updateTimers(){
  engineTimer.update();
    steeringTimer.update();
}
void IncreaseSpeedPrint()
{
    if(engineTimer.getElapsedTime()>COMMAND_DELAY) {
    //speed++;
    Serial.println(1);
    engineTimer.reset();
    }
  //drive();
}
void neutral()
{
 for(int i=91;i<95;i++)
 {
   engine.write(i);
   delay(15);
 }

 speed =0;
}
void sendFlow(){
   Flow data = {1, 2, 3.5f};
   Serial.write(reinterpret_cast<char*>(&data),8);
  }
void getDriveCommand()
{
  String speed_string;
  String angle_string;

  while (!Serial.available()) {};
  //get speed
  while (Serial.available()) {
      char c = Serial.read();  //gets one byte from serial buffer
      if( c == '#' )
      {
          Serial.flush();
          sendFlow();
          //delay(40);
          //  motion_sensor.getData();
          return;
      }
      if(c== '\n' ){           //to know if this is end of former cmd
        return;
      }
      speed_string += c; //makes the String speed_string
      delay(2);  //slow looping to allow buffer to fill with next character
      if(c == ' ') break; // go to get angle
    }
    //get angle
    while (Serial.available()) {
      char c = Serial.read();  
      angle_string += c; 
      delay(2); 
    }
//    Serial.println(speed_string);
//    Serial.println(angle_string);
//    Serial.println("");
    if (speed_string.length() > 0 && angle_string.length()) {
  
      int wanted_speed= speed_string.toInt(); 
      int wanted_angle= angle_string.toInt(); 
      
//      Serial.println("");  
//      Serial.print("speed:");
//      Serial.println(wanted_speed);  
//      Serial.print("angle:");  
//      Serial.println(wanted_angle);  

      //if we need to put in revese
      if(speed >= 0 && wanted_speed < 0 )
      {
         speed=0;
         drive();
         delay(40);
         neutral();
      }
      speed=wanted_speed;
      angle=wanted_angle;
      
//      Serial.flush();
//      sendFlow();
    }
    speed_string = "";
    angle_string = "";
    
      Serial.flush();
      sendFlow();
      
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
