

#include <string>

class CarControl {
    int m_current_speed=0;
    int m_current_angle=90;
    void sendMessage(int speed,int angle);

public:
    /*
     * connects to Arduino controller
     * returns true for success
     */
    bool connect(int serial);
    /*
     * stops the car and set the wheels to a 90 degree angle
     */
    void stop();
    /*
    * sends command to drive at <speed> <current_angle>
    * param speed should be [-25,25]
    */
    void changeSpeed(int wanted_speed);
    /*
    * sends command to drive at <current_speed> <angle>
    * angle should be in [55,125]
    */
    void changeAngle(int wanted_angle);
    /*
     * sends command to drive at <speed> <angle>
     * param speed should be [-25,25]
     * param angle should be in [55,125]
     */
    void drive(int speed,int angle);
};