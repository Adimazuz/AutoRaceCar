#include "UDPClient.h"

std::shared_ptr<IUDPClient> IUDPClient::create(const string &ip, const ushort &port)
{
    return std::make_shared<UDPClient>(ip, port);
}
