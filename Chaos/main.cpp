#include <iostream>
#include <string>
#include <stdio.h>
//#include "ITcpClient.h"
#include "librealsense2/rs.hpp"
#include "ISerial.h"
#include "RaceCar.h"


int main() {

//    auto s = ISerial::create();
//    auto res = s->connect();

//    Flow data = {};

//    s->write("$");
//    for(int i = 0 ; i < 1000; i++)
//    {
//        if(i % 2 == 0)
//        {
//            s->write("0 100");
//        }
//        else
//        {
//            s->write("0 90");
//        }

//        std::this_thread::sleep_for(std::chrono::milliseconds(200));

//        s->read(reinterpret_cast<char*>(&data), 8);

//        std::cout << data.deltaX << " " << data.deltaY << " " << data.range << std::endl;
//    }


    RaceCar car;
    car.connect("132.68.36.50",5555,"132.68.36.20");
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
