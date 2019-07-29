#ifndef SERVERSOCKET_TCPSERVER_H
#define SERVERSOCKET_TCPSERVER_H

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
#include <map>
#include "ITcpServer.h"

class TcpServer : public ITcpServer
{
public:

    TcpServer() noexcept;

    virtual void bind(const string &ip, const unsigned short &port, const int &max_num_of_clients) override;

    virtual bool isBind() const override {return _is_bind;}

    virtual std::vector<char> receive(const Socket &socket, const uint &len) noexcept override;

    virtual void send(const Socket& socket, const std::vector<char>& data) const noexcept override;

    virtual void send(const Socket& socket, const string& message) const noexcept override;

    virtual void send(const Socket& socket, const char *data, const uint &len) const noexcept override;

    virtual bool hasConnectionWithSocket(const Socket &socket) override;

    virtual Socket waitForConnections() override;

    virtual unsigned long getNumOfConnectedClients() const override {return _clients_connection_state.size();}

    virtual ~TcpServer() override;

private: //functions

    TcpServer &createSocket();
    TcpServer &doBind();
    TcpServer &doListen();
    Socket doAccept(sockaddr_in &client) const;
    sockaddr_in buildAddress(const string& ip, const unsigned short& port) const noexcept;

private: //members

    struct Address
    {
        unsigned short port;
        string ip;
    };

    struct Client
    {
        Socket socket;
        bool is_connected;
    };

    string _ip;
    unsigned short _port;
    int _max_num_of_clients;
    Socket _socket;
    std::map<Socket, bool> _clients_connection_state;
    sockaddr_in _address;
    bool _is_bind;
};


#endif //SERVERSOCKET_TCPSERVER_H
