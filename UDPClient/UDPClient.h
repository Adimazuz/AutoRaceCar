#ifndef UDPCLIENTIMPL_H
#define UDPCLIENTIMPL_H

#include "IUDPClient.h"

class UDPClient : public IUDPClient
{
public:
    UDPClient(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept override;
    virtual void send(const std::vector<char> &msg) override;
    virtual void send(const string &msg) override;

private://methids
    UDPClient &createSocket();

private://members
    Socket _socket;
    sockaddr_in _server_addres;
};

#endif // UDPCLIENTIMPL_H
