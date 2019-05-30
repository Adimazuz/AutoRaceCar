#include <iostream>
#include "IUDPServer.h"

int main()
{
    auto server = IUDPServer::create("127.0.0.1", 1234);
    auto data = server->receive(1024);

    std::cout << data.data() << std::endl;
    return 0;
}
