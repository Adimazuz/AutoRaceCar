#include <iostream>
#include <string>
#include <stdio.h>
//#include "ITcpClient.h"
#include "librealsense2/rs.hpp"
#include "ISerial.h"
#include "RaceCar.h"



int main() {
    //TODO add timestamp from camera
    RaceCar car;
    car.connect("132.68.36.163",5555,"132.68.36.165");
    car.run();

    std::cout << " ok" << std::endl;


    std::thread thread([&car]()
    {
        while(true)
        {
            char ch;
            std::cin >> ch;
            if(ch == 'q')
            {
                car._is_running = false;
                break;
            }
        }
    });

    thread.join();
    return 0;
}
