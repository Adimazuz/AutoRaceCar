#include <iostream>
#include <string>
#include <stdio.h>
//#include "ITcpClient.h"
//#include "librealsense2/rs.hpp"
//#include "ISerial.h"
#include "RaceCar.h"



int main() {
    RaceCar car;
    car.connect("10.42.0.1",5555,"10.42.0.205");
    car.run();

    std::cout << " ok" << std::endl;


    std::thread thread([&car]()
    {
        while(car._is_running)
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
