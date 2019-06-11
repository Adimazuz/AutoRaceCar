#include "Arduino.h"
#include <iostream>
using std::string;


bool Arduino::connect()
{
    m_serial = ISerial::create();
    m_serial->connect();

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
        m_current_speed+=wanted_speed;
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
        m_current_angle+=wanted_angle;
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
        m_current_speed+=wanted_speed;
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
    if (m_current_angle + delta > MAX_ANGLE && delta > 0){
        m_current_angle = MAX_ANGLE;
    }
    else if (m_current_angle - delta < MIN_ANGLE && delta < 0)
    {
        m_current_angle = MIN_ANGLE;
    }
    else
    {
        m_current_angle+=delta;
    }
    sendDriveCommand();
}
Arduino& Arduino::changeSpeedBy(const int &delta)
{
    if (m_current_speed + delta > TOP_SPEED && delta > 0){
        m_current_speed = TOP_SPEED;
    }
    else if (m_current_speed - delta < -TOP_SPEED && delta < 0)
    {
        m_current_speed = -TOP_SPEED;
    }
    else
    {
        m_current_speed+=delta;
    }
    sendDriveCommand();
}
Arduino &Arduino::driveCurrentState(){
	sendDriveCommand();
}

//==========================private==================================

string Arduino::createCommandMsg(int speed, int angle){
    string cmd_string = (std::to_string(speed) + " " + std::to_string(angle));
    return cmd_string;
}
void Arduino::sendDriveCommand(){
    string cmd_string = createCommandMsg(m_current_speed,m_current_angle);
    m_serial->write(cmd_string);
}
