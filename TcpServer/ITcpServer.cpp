#include "TcpServer.h"

std::shared_ptr<ITcpServer> ITcpServer::create(const string &ip, const int &port,
                                           const int &max_num_of_clients)
{
    return std::make_shared<TcpServer>(ip, port, max_num_of_clients);
}