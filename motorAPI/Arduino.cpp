#include "Arduino.h"
#include <iostream>
#include <vector>
#include <math.h>
using std::string;


bool Arduino::connect()
{
    m_serial = ISerial::create();
    _is_connected =  m_serial->connect("/dev/ttyUSB0");
    return _is_connected;

}
Arduino &Arduino::drive(const int &wanted_speed, const int &wanted_angle)
{
    if (wanted_speed > TOP_SPEED ){
        m_current_speed = TOP_SPEED;
    }
    else if (wanted_speed < -TOP_SPEED)
    {
        m_current_speed = -TOP_SPEED;
    }
    else
    {
        m_current_speed = wanted_speed;
    }

    if (wanted_angle  > MAX_ANGLE ){
        m_current_angle = MAX_ANGLE;
    }
    else if (wanted_angle < MIN_ANGLE )
    {
        m_current_angle = MIN_ANGLE;
    }
    else
    {
        m_current_angle = wanted_angle;
    }
    sendDriveCommand();
}
Arduino &Arduino::changeSpeed(const int &wanted_speed)
{
    if (wanted_speed > TOP_SPEED ){
        m_current_speed = TOP_SPEED;
    }
    else if (wanted_speed < -TOP_SPEED)
    {
        m_current_speed = -TOP_SPEED;
    }
    else
    {
        m_current_speed = wanted_speed;
    }
    sendDriveCommand();}
Arduino &Arduino::changeAngle(const int &wanted_angle)
{
    if (wanted_angle  > MAX_ANGLE ){
        m_current_angle = MAX_ANGLE;
    }
    else if (wanted_angle < MIN_ANGLE )
    {
        m_current_angle = MIN_ANGLE;
    }
    else
    {
        m_current_angle+=wanted_angle;
    }
    sendDriveCommand();
}
Arduino &Arduino::stop()
{
    m_current_speed = 0;
    m_current_angle = 90;
    sendDriveCommand();
}
Arduino& Arduino::changeAngleBy(const int &delta)
{
    if (delta > 0 && m_current_angle + delta > MAX_ANGLE  ){
        m_current_angle = MAX_ANGLE;
    }
    else if(delta < 0 && m_current_angle + delta < MIN_ANGLE )
    {
        m_current_angle = MIN_ANGLE;
    }
    else
    {
        m_current_angle += delta;
    }
    sendDriveCommand();
}
Arduino& Arduino::changeSpeedBy(const int &delta)
{
    if (delta > 0)
	{
        if( m_current_speed>=0 && m_current_speed <10)
		{
			m_current_speed = 10;
		}
		else if( m_current_speed + delta > TOP_SPEED )
		{
        m_current_speed = TOP_SPEED;
		}
        m_current_speed += delta;
    }
    else if (delta < 0)
	{
        if( m_current_speed<=0 && m_current_speed >-8)
		{
			m_current_speed = -8;
		}
        else if( m_current_speed + delta < -TOP_SPEED  )
		{
			m_current_speed = -TOP_SPEED;
        }
        m_current_speed += delta;
	}

    sendDriveCommand();
}
Arduino &Arduino::driveCurrentState(){
    sendDriveCommand();
}

Arduino::~Arduino()
{
    if(_is_connected)
    {
        drive(0,90);
    }
}


//==========================private==================================

string Arduino::createCommandMsg(int speed, int angle){
    string cmd_string = (std::to_string(speed) + " " + std::to_string(angle) + "/n" );
    return cmd_string;
}
void Arduino::sendDriveCommand(){
    string cmd_string = createCommandMsg(m_current_speed,m_current_angle);
    m_serial->write(cmd_string);
}

int Arduino::calcDistance(int sensor_value,int range){
	return ( (sensor_value * range) / (SENSOR_RESULUTION * SCALAR ) ) * 2 * tan(FIELD_OF_VIEW/2);
}

//int main() {
//    Arduino car;
//    bool flage=car.connect();
//    car.changeAngleBy(40);
//    car.changeAngleBy(-70);
//    car.changeSpeedBy(15);
//    car.changeSpeedBy(20);
//    car.changeSpeedBy(-40);
//    return 0;
// }
