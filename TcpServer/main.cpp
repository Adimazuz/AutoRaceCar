#include "ITcpServer.h"
#include <iostream>

int main()
{
    auto server = ITcpServer::create();
    char *dst = new char[20];
    server->bind("127.0.0.1", 5555, 5);
    if(server->isBind())
    {
        std::cout << "bind success" << std::endl;
    }
    bool is_connected = false;
    Socket sock;

    while(!server->hasConnectionWithSocket(sock))
    {
        sock = server->waitForConnections(1);
    }


    while(server->hasConnectionWithSocket(sock))
    {

        if(sock > 0)
        {
            is_connected = true;
            std::cout << "client: " << sock << " has connected" << std::endl;
            string msg = server->receive(sock, 5);
            std::cout << msg << std::endl;
        }
        else
        {
            std::cout << "no one connect" << std::endl;
        }
    }



    return 0;
}
