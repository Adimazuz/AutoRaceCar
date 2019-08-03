#include <iostream>
#include "UdpServer.h"
#include "zlib.h"

int main()
{

    UdpServer server("127.0.0.1", 5555);

    for(int i = 0; i < 5; i++)
    {
        char *data = new char[172800];
        server.receive(data, 172800);
    }

    return 0;
}
