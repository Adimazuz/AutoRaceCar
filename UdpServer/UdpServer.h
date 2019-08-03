#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "IUdpServer.h"

class UdpServer : public IUdpServer
{
public:
    UdpServer(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept override;
    virtual void receive(char *dst, const unsigned long &len) override;
    virtual void send(const std::vector<char> &data) override;
    virtual void send(const string &msg) override;

private: //methods
    UdpServer &createSocket();
    UdpServer &bind(const string &ip, const ushort &port);

private: //members
    Socket _socket;
    sockaddr_in _client_address;
};

#endif // UDPSERVER_H
