#include <thread>

#include "ITcpClient.h"

int main()
{
    auto client = ITcpClient::create();
    client->connect("127.0.0.1", 5555);

    auto res = client->isConnected();
    client->send("asf");
    client->send("asf");
    res = client->isConnected();

    client->connect("127.0.0.1", 5555);
    res = client->isConnected();

    return 0;
}
