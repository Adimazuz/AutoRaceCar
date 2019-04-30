#include "TcpClient.h"

std::shared_ptr<ITcpClient> ITcpClient::create()
{
    return std::make_shared<TcpClient>();
}
