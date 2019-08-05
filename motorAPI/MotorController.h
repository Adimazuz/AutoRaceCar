//
// Created by tapuz_000 on 03/06/2019.
//

#ifndef UNTITLED_MOTORCONTROLLER_HPP
#define UNTITLED_MOTORCONTROLLER_HPP
#include "Arduino_types.h"

class MotorController
{
public:
    /**
     * throw exception if fails
     * @return this
     */
    virtual bool connect() = 0;
    /**
     * stops the car and set the wheels to a 90 degree angle
     * @return this
     */

    virtual MotorController &stop() = 0;
    /**
     * sends command to drive at <speed> <current_angle>
     * @param wanted_speed should be [-25,25]
     * @return this
     */
    virtual MotorController &changeSpeed(const int &wanted_speed) = 0;
    /**
     * sends command to drive at <current_speed> <angle>
     * @param wanted_angle should be in [55,125]
     * @return this
     */
    virtual MotorController &changeAngle(const int &wanted_angle) = 0;
    /**
     * sends command to drive at <speed> <angle>
     * @param speed should be [-25,25]
     * @param angle should be in [55,125]
     * @return
     */
    virtual MotorController &drive(const int &speed, const int &angle) = 0;
    /**
     * changes current speed by delta
     * if change is outside possible range speed will be set to max/min
     * @param delta
     * @return this
     */

    virtual MotorController &changeSpeedBy(const int &delta) = 0;

    /**
     * changes current angle by delta
     * if change is outside possible range angel will be set to max/min
     * @param delta
     * @return this
     */
    virtual MotorController &changeAngleBy(const int &delta) = 0;
	
    virtual MotorController &driveCurrentState()=0;

    virtual Flow &getFlowOutput() = 0;

};

#endif //UNTITLED_MOTORCONTROLLER_HPP
