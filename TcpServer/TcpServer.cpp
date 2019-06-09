#include <iostream>
#include "Exceptions.h"
#include "TcpServer.h"

#ifdef _WIN32
    #include <inaddr.h>
#else
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

TcpServer::TcpServer(const string &ip, const unsigned short &port, const int &max_num_of_clients) noexcept :
    _ip(ip),
    _port(port),
    _max_num_of_clients(max_num_of_clients),
    _socket(-1),
    _address()
{
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);
#endif

    _address = buildAddress(ip, port);
    try
    {
        createSocket();
        doBind();
        doListen();
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

TcpServer &TcpServer::createSocket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if(_socket == -1)
    {
        throw ITcpServerCannotCreateSocket();
    }

    return *this;
}

TcpServer &TcpServer::doBind()
{
    int res = bind(_socket, reinterpret_cast<sockaddr*>(& _address), sizeof(_address));
    if(res < 0)
    {
        throw ITcpServerCannotBind(_ip, _port);
    }

    return *this;
}

TcpServer &TcpServer::doListen()
{
    int res = listen(_socket, _max_num_of_clients);
    if(res < 0)
    {
        throw ITcpServerCannotListen();
    }

    return *this;
}

TcpServer::~TcpServer()
{
#ifdef _WIN32
    closesocket(_socket);
#else
    close(_socket);
#endif
}

std::vector<char> TcpServer::receive(const Socket &socket, const uint &len) const noexcept
{ 
    std::vector<char> data(len);

    uint bytes_received = 0;

    while(bytes_received < len)
    {
        auto tmp_len = recv(socket, data.data() + bytes_received, len - bytes_received, 0);
        bytes_received += tmp_len;
    }

    return data;

//    std::vector<char> data(len);

//    recv(socket, data.data(), len, 0);

//    return data;
}

Socket TcpServer::waitForConnections() const
{
    Address address = {};

    sockaddr_in client = buildAddress(address.ip, address.port);

    Socket client_socket = doAccept(client);

    if(client_socket == -1)
    {
        throw ITcpServerCannotAccept();
    }

    return client_socket;
}

void TcpServer::send(const Socket &socket, const std::vector<char> &data) const noexcept
{
    uint bytes_sent = 0;
    while (bytes_sent < data.size())
    {
        auto tmp_len = ::send(socket, data.data() + bytes_sent, data.size() - bytes_sent, 0);
        bytes_sent += tmp_len;
    }
}

void TcpServer::send(const Socket &socket, const string &message) const noexcept
{
    uint bytes_sent = 0;
    uint len = static_cast<uint>(message.size());
    while (bytes_sent < message.size())
    {
        auto tmp_len = ::send(socket, message.c_str() + bytes_sent, len - bytes_sent, 0);
        bytes_sent += tmp_len;
    }
}

void TcpServer::send(const Socket &socket, const char *data, const uint &len) const noexcept
{
    uint bytes_sent = 0;
    while (bytes_sent < len)
    {
        auto tmp_len = ::send(socket, data + bytes_sent, len - bytes_sent, 0);
        bytes_sent += tmp_len;
    }
}

sockaddr_in TcpServer::buildAddress(const string &ip, const unsigned short &port) const noexcept
{
    sockaddr_in address;

#ifdef _WIN32
    address.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
#else
    address.sin_addr.s_addr = inet_addr(ip.c_str());
#endif

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    return address;
}

Socket TcpServer::doAccept(sockaddr_in& client) const
{

#ifdef _WIN32
    int client_address_size = sizeof(client);
#else
    unsigned int client_address_size = sizeof(client);
#endif

    return accept(_socket, reinterpret_cast<sockaddr*>(& client), &client_address_size);
}
