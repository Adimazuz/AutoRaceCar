#include "raceCar.h"
#include <iostream>
using std::string;


RaceCar &RaceCar::connect()
{
    m_serial = ISerial::create();
    m_serial->connect();

}
RaceCar &RaceCar::drive(const int &wanted_speed, const int &wanted_angle)
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
RaceCar &RaceCar::changeSpeed(const int &wanted_speed)
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
RaceCar &RaceCar::changeAngle(const int &wanted_angle)
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
RaceCar &RaceCar::stop()
{
    m_current_speed = 0;
    m_current_angle = 90;
    sendDriveCommand();
}
RaceCar& RaceCar::changeAngleBy(const int &delta)
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
RaceCar& RaceCar::changeSpeedBy(const int &delta)
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


//==========================private==================================

string RaceCar::createCommandMsg(int speed, int angle){
    string cmd_string = (std::to_string(speed) + " " + std::to_string(angle));
    return cmd_string;
}
void RaceCar::sendDriveCommand(){
    string cmd_string = createCommandMsg(m_current_speed,m_current_angle);
    m_serial->write(cmd_string);
}






int main(){
    int speed = 5;
    int angle = 90;
    string my_string = (std::to_string(speed) + " " + std::to_string(angle) );
    std::cout << my_string<<std::endl;
    return 0;
}