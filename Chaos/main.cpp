#include <iostream>

#include "ITcpClient.h"

#include "RaceCar.h"
int main() {


    RaceCar car;
    car.connect("132.",5560);
    car.run();

    std::cout << " ok" << std::endl;
}
