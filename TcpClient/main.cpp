#include <iostream>
#include "ITcpClient.h"
#include <chrono>

int main()
{

    try
    {
        std::shared_ptr<ITcpClient> client = ITcpClient::create();

        client->connect("127.0.0.1", 5555);

        char *data = new char[2000000];
        for(uint i = 0; i < 2000000; i++)
        {
            data[i] = 'a';
        }

        client->send(data, 2000000);

    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
