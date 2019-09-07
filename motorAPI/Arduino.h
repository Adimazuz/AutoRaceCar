#include <string>
#include "ISerial.h"

#include "MotorController.h"

class Arduino : public MotorController
{

public:
    /**
     * throw exception if fails
     * @return this
     */
    virtual bool connect() override;
    /**
     * stops the car and set the wheels to a 90 degree angle
     * @return this
     */
    virtual Arduino &stop() override;
    /**
     * sends command to drive at <speed> <current_angle>
     * @param wanted_speed should be [-25,25]
     * @return this
     */
    virtual Arduino &changeSpeed(const int &wanted_speed) override;
    /**
     * sends command to drive at <current_speed> <angle>
     * @param wanted_angle should be in [55,125]
     * @return this
     */
    virtual Arduino &changeAngle(const int &wanted_angle) override;
    /**
     * sends command to drive at <speed> <angle>
     * @param speed should be [-25,25]
     * @param angle should be in [55,125]
     * @return
     */
    virtual Arduino &drive(const int &speed, const int &angle) override;
    /**
     * changes current speed by delta
     * if change is outside possible range speed will be set to max/min
     * @param delta
     * @return this
     */
    virtual Arduino &changeSpeedBy(const int &delta) override;
    /**
     * changes current angle by delta
     * if change is outside possible range angel will be set to max/min
     * @param delta
     * @return this
     */
    virtual Arduino &changeAngleBy(const int &delta) override;
	
    virtual Arduino &driveCurrentState();
    /**
     *
     * @return currnet speed in units between [-30,30]
     */
    virtual int getSpeed() ;
    /**
     *
     * @return current angle in degrees
     */
    virtual int getAngle() ;

    ~Arduino();

    Arduino() = default;

private:

    std::shared_ptr<ISerial> m_serial;
    int m_current_speed=0;
    int m_current_angle=90;
    static constexpr int START_SPEED = 8;
    static constexpr int TOP_SPEED = 12;
    static constexpr int MIN_ANGLE = 30;
    static constexpr int MAX_ANGLE = 150;
    void sendDriveCommand();
    bool _is_connected = false;
    std::string createCommandMsg(int speed,int angle);
};
