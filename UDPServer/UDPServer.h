#ifndef UDPCLIENTIMPL_H
#define UDPCLIENTIMPL_H

#include "IUDPServer.h"

class UDPServer : public IUDPServer
{
public:
    UDPServer(const string &ip, const ushort &port);
    virtual std::vector<char> receive(const unsigned long &len) noexcept override;
    virtual void send(const std::vector<char> &msg) override;
    virtual void send(const string &msg) override;

private: //methods
    UDPServer &createSocket();
    UDPServer &bind(const string &ip, const ushort &port);

private: //members
    Socket _socket;
    sockaddr_in _client_address;
};

#endif // UDPCLIENTIMPL_H
