#include <thread>

#include "ITcpClient.h"

int main()
{
    auto client = ITcpClient::create();
    client->connect("127.0.0.1", 5555);

    while(client->isConnected())
    {
        int x = 5;
        client->send("hello");
        x++;
    }

    return 0;
}
