#include <iostream>
#include <string>
#include <vector>
#include "ITcpServer.h"


int main()
{

    std::shared_ptr<ITcpServer> server = ITcpServer::create("132.68.36.85", 1234, 5);

    Address a;

    auto x = server->waitForConnections(a);

    std::vector<char> rec = server->receive(x, 1024);

    std::cout << rec.data() << std::endl;

    return 0;
}
