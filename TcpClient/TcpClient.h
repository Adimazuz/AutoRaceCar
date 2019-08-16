#ifndef TCPSOCKET_TCPCLIENT_H
#define TCPSOCKET_TCPCLIENT_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <inaddr.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/types.h>
#endif

#include <vector>
#include "ITcpClient.h"

class TcpClient : public ITcpClient
{
public:

    TcpClient() noexcept;

    virtual void connect(const string& ip, const unsigned short& port) override;

    virtual bool isConnected() const override {return _is_connected;}

    virtual void setUnblocking(const bool &new_val) override;

    virtual void receive(char *dst, const uint &len) override;

    virtual void send(const std::vector<char>& data) noexcept override;

    virtual void send(const string& data) noexcept override;

    virtual void send(const char* data, const uint &len) noexcept override;

    virtual void disconnect() override;

    virtual ~TcpClient() override;

private: //functions
    TcpClient &createSocket();
    sockaddr_in buildAddress(const string &ip, const unsigned short &port) const noexcept;

private:
    Socket _socket;
    sockaddr_in _address;
    bool _is_connected;
    bool _is_unblocking;
    bool _unblocking_flag;
};


#endif //TCPSOCKET_TCPCLIENT_H
