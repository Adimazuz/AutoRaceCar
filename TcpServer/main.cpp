#include <iostream>
#include <string>
#include <vector>
#include "ITcpServer.h"


int main()
{

    std::shared_ptr<ITcpServer> server = ITcpServer::create("127.0.0.1", 1234, 5);

    Address a;

    auto x = server->waitForConnections(a);

    string msg = R"({"id": 1, "sub_parking_area_id": 1, "parking_area_id": 1, "status": "occupied", "owner": "asaf"})";

    server->send(x, msg);

    std::vector<char> rec = server->receive(x, 1024);

    std::cout << rec.data() << std::endl;

    return 0;
}
