#include "TcpServer.h"

std::shared_ptr<ITcpServer> ITcpServer::create()
{
    return std::make_shared<TcpServer>();
}
