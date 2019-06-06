#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "ITcpServer.h"


int main()
{

    std::shared_ptr<ITcpServer> server = ITcpServer::create("127.0.0.1", 5555, 5);

    auto x = server->waitForConnections();

    std::vector<char> rec = server->receive(x, 2000000);

    return 0;
}
