#ifndef IUDPCLIENT_H
#define IUDPCLIENT_H

#include "UdpClient_types.h"

class IUdpClient
{
public:
    static std::shared_ptr<IUdpClient> create(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept = 0;
    virtual void send(const std::vector<char> &msg) = 0;
    virtual void send(const string &msg) = 0;
    virtual void send(const char* data, const uint &len) = 0;
    virtual ~IUdpClient() = default;
};

#endif // IUDPCLIENT_H
