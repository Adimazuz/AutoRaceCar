#include <iostream>
#include "IUdpClient.h"


int main()
{
    auto client = IUdpClient::create("127.0.0.1", 5555);

    char *data = new char[3];
    data[0] = 'a';
    data[1] = 'b';
    data[2] = 'c';

    client->send(data, 3);
    return 0;
}
