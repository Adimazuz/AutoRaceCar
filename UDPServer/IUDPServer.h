#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "UDPServer_types.h"

class IUDPServer
{
public:
    static std::shared_ptr<IUDPServer> create(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept = 0;
    virtual void send(const std::vector<char> &msg) = 0;
    virtual void send(const string &msg) = 0;
    virtual ~IUDPServer() = default;
};

#endif // UDPSERVER_H
