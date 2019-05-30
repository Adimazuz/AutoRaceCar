#include <iostream>
#include "IUDPClient.h"

int main()
{
    auto client = IUDPClient::create("127.0.0.1", 1234);
    client->send("hello world");
    return 0;
}
