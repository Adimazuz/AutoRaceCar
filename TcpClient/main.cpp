#include <thread>
#include <iostream>

#include "ITcpClient.h"

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

    auto client = ITcpClient::create();
    client->setUnblocking(true);

    client->connect("127.0.0.1", 5555);


    char *name = new char[4];

    while(is_run)
    {
        if(client->isConnected())
        {
            client->send("asaf");
            std::this_thread::sleep_for(std::chrono::seconds(1));
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
