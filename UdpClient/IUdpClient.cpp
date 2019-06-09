#include "UdpClient.h"

std::shared_ptr<IUdpClient> IUdpClient::create(const string &ip, const ushort &port)
{
    return std::make_shared<UdpClient>(ip, port);
}
