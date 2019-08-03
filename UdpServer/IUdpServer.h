#ifndef IUDPSERVER_H
#define IUDPSERVER_H

#include "UdpServer_types.h"

class IUdpServer
{
public:
    static std::shared_ptr<IUdpServer> create(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept = 0;
    virtual void receive(char *dst, const unsigned long &len) = 0;
    virtual void send(const std::vector<char> &msg) = 0;
    virtual void send(const string &msg) = 0;
    virtual ~IUdpServer() = default;
};

#endif // IUDPSERVER_H
