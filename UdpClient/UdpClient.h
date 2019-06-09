#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "IUdpClient.h"

class UdpClient : public IUdpClient
{
public:
    UdpClient(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept override;
    virtual void send(const std::vector<char> &msg) override;
    virtual void send(const string &msg) override;
    virtual void send(const char* data, const uint &len) override;

private://methids
    UdpClient &createSocket();

private://members
    Socket _socket;
    sockaddr_in _server_addres;
};

#endif // UDPCLIENT_H
