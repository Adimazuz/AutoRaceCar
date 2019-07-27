#include <string>
#include "ISerial.h"
#include "flow.h
#include "MotorController.h"

class Arduino : public MotorController
{

public:
    /*
     * connects to Arduino controller
     */
    virtual bool connect() override;

    virtual Arduino &stop() override;

    virtual Arduino &changeSpeed(const int &wanted_speed) override;

    virtual Arduino &changeAngle(const int &wanted_angle) override;

    virtual Arduino &drive(const int &speed, const int &angle) override;

    virtual Arduino &changeSpeedBy(const int &delta) override;

    virtual Arduino &changeAngleBy(const int &delta) override;
	
	virtual Arduino &driveCurrentState();

    virtual Flow &getFlowOutput();


   ~Arduino();

    Arduino() = default;

private:
    std::shared_ptr<ISerial> m_serial;
    int m_current_speed=0;
    int m_current_angle=90;
    static constexpr int TOP_SPEED = 30;
    static constexpr int MIN_ANGLE = 60;
    static constexpr int MAX_ANGLE = 130;
    void sendDriveCommand();
    bool _is_connected = false;
    std::string createCommandMsg(int speed,int angle);
};
