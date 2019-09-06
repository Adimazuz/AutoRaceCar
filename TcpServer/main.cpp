#include "ITcpServer.h"
#include <iostream>
#include <thread>

int main()
{
    bool is_run = true;
    std::thread t([&is_run]()
    {
        while(is_run)
        {
            char c;
            std::cin >> c;
            if(c == 'q')
            {
                is_run = false;
            }
        }
    });

    auto server = ITcpServer::create();
    server->bind("127.0.0.1", 5555, 5);
    if(server->isBind())
    {
        std::cout << "bind success" << std::endl;
    }


    auto sock = server->waitForConnections(1);
//    server->setClientUnblocking(sock, true);
    if(sock > 0)
    {
        std::cout << "someone connected" << std::endl;
    }

    char *name = new char[5];
    while(is_run)
    {
        if(server->hasConnectionWithSocket(sock))
        {
//            std::cout << "receiving" << std::endl;
//            server->receive(sock, name, 4);
//            server->send(sock, "asaf");
        }
        else
        {
            std::cout << "disconnected" << std::endl;
            is_run = false;
        }
    }

    t.join();

    return 0;
}
