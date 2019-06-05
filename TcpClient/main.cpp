#include <iostream>
#include "ITcpClient.h"

int main()
{

    try
    {
        std::shared_ptr<ITcpClient> client = ITcpClient::create();

        client->connect("192.168.70.21", 1234);

        client->send("yo yo this is anter");

        auto data = client->receive(1024);

        std::cout << data.data() << std::endl;

    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
