#include <string>

#include "MotorController.hpp"

class RaceCar : public MotorController
{

public:
    /*
     * connects to Arduino controller
     * returns true for success
     */
    virtual bool connect(int serial) override;
    /*
     * stops the car and set the wheels to a 90 degree angle
     */
    virtual RaceCar &stop() override;
    /*
    * sends command to drive at <speed> <current_angle>
    * param speed should be [-25,25]
    */
    virtual RaceCar &changeSpeed(const int &wanted_speed) override;
    /*
    * sends command to drive at <current_speed> <angle>
    * angle should be in [55,125]
    */
    virtual RaceCar &changeAngle(const int &wanted_angle) override;
    /*
     * sends command to drive at <speed> <angle>
     * param speed should be [-25,25]
     * param angle should be in [55,125]
     */
    virtual RaceCar &drive(const int &speed, const int &angle) override;

    /**
     *
     * @param speed
     * @return
     */
    RaceCar &increaseSpeed(const int &speed) override;

    /**
     *
     * @param speed
     * @return
     */
    RaceCar &decreaseSpeed(const int &speed) override;

private:
    int m_current_speed=0;
    int m_current_angle=90;
    void sendDriveCommand();
    std::string createCommandMsg(int speed,int angle);
};