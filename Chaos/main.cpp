#include <iostream>
#include <string>
#include <stdio.h>
//#include "ITcpClient.h"
#include "librealsense2/rs.hpp"
#include "ISerial.h"
#include "RaceCar.h"



int main() {



//    auto s = ISerial::create();
//    auto res = s->connect("/dev/ttyUSB0");
//    if(res)
//    {
//        std::cout << "arduino connected" << std::endl;
//    }
////    Flow data = {};

//    while(true)
//    {
//        s->write("#");
////        s->read(reinterpret_cast<char*>(&data), sizeof(Flow));
////        std::cout << data.deltaX << " " << data.deltaY << " " << data.range << " " << data.mili_sec << std::endl;
//    }

    RaceCar car;
    car.connect("192.168.1.75",5555,"192.168.1.114");
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
