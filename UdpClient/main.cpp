#include <iostream>
#include <thread>
#include "IUdpClient.h"


int main()
{
    auto client = IUdpClient::create("127.0.0.1", 5555);

    for(int i = 0; i < 5; i++)
    {
        char *data = new char[172800];
        client->send(data, 172800);
        delete[] data;
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }


    return 0;
}
