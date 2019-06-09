#include "UdpServer.h"

std::shared_ptr<IUdpServer> IUdpServer::create(const string &ip, const ushort &port)
{
    return std::make_shared<UdpServer>(ip, port);
}
