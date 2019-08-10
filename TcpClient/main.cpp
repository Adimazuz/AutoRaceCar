#include <thread>

#include "ITcpClient.h"

int main()
{
    auto client = ITcpClient::create();
    client->connect("127.0.0.1", 5555);

    client->send("asaf");

    return 0;
}
