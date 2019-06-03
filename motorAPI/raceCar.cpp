#include "raceCar.h"
#include <iostream>
using std::string;

bool RaceCar::connect(int serial)
{
    //TODO implement
}
RaceCar &RaceCar::drive(const int &wanted_speed, const int &wanted_angle)
{
    m_current_speed = wanted_speed;
    m_current_angle = wanted_angle;
    sendDriveCommand();
}
RaceCar &RaceCar::changeSpeed(const int &wanted_speed)
{
    m_current_speed = wanted_speed;
    //sendMessage(wanted_speed,m_current_angle);
}
RaceCar &RaceCar::changeAngle(const int &wanted_angle)
{
    m_current_angle = wanted_angle;
    sendDriveCommand();
}
RaceCar &RaceCar::stop()
{
    m_current_speed = 0;
    m_current_angle = 90;
    sendDriveCommand();
}


//==========================private==================================

string RaceCar::createCommandMsg(int speed, int angle){
    string cmd_string = (std::to_string(speed) + " " + std::to_string(angle));
    return cmd_string;
}
void RaceCar::sendDriveCommand(){
    string cmd_string = createCommandMsg(m_current_speed,m_current_angle);
    //TODO implement
    //sned cmd_string;
}






int main(){
    int speed = 5;
    int angle = 90;
    string my_string = (std::to_string(speed) + " " + std::to_string(angle) );
    std::cout << my_string<<std::endl;
    return 0;
}