#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "UDPClient_types.h"

class IUDPClient
{
public:
    static std::shared_ptr<IUDPClient> create(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept = 0;
    virtual void send(const std::vector<char> &msg) = 0;
    virtual void send(const string &msg) = 0;
    virtual ~IUDPClient();
};

#endif // UDPCLIENT_H
