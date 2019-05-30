#include "UDPServer.h"

std::shared_ptr<IUDPServer> IUDPServer::create(const string &ip, const ushort &port)
{
    return std::make_shared<UDPServer>(ip, port);
}
