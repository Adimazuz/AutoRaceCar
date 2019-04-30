#include <iostream>
#include "ITcpClient.h"

int main()
{

    try
    {
        std::shared_ptr<ITcpClient> client = ITcpClient::create();

        client->connect("192.168.1.101", 1234);

        client->send("hello im client");

        std::vector<char> msg = client->receive(1024);

        std::cout << msg.data() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}