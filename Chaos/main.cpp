#include <iostream>
#include <string>

//#include "ITcpClient.h"

#include "RaceCar.h"
int main() {


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
