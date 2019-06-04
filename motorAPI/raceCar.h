#include <string>
#include "Serial/ISerial.h"

#include "MotorController.hpp"

class RaceCar : public MotorController
{

public:
    /*
     * connects to Arduino controller
     */
    virtual RaceCar &connect() override;

    virtual RaceCar &stop() override;

    virtual RaceCar &changeSpeed(const int &wanted_speed) override;

    virtual RaceCar &changeAngle(const int &wanted_angle) override;

    virtual RaceCar &drive(const int &speed, const int &angle) override;

    virtual RaceCar &changeSpeedBy(const int &delta) override;

    virtual RaceCar &changeAngleBy(const int &delta) override;

    RaceCar() = default;

private:
    std::shared_ptr<ISerial> m_serial;
    int m_current_speed=0;
    int m_current_angle=90;
    static constexpr int TOP_SPEED = 30;
    static constexpr int MIN_ANGLE = 65;
    static constexpr int MAX_ANGLE = 125;
    void sendDriveCommand();
    std::string createCommandMsg(int speed,int angle);
};