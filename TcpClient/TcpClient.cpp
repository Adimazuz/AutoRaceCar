#include <iostream>
#include "Exceptions.h"
#include "TcpClient.h"

#ifdef _WIN32
#include <inaddr.h>
#else
#include <arpa/inet.h>
    #include <unistd.h> 
#endif

TcpClient::TcpClient() noexcept :
        _socket(-1),
        _address()
{
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);
#endif

    try
    {
        createSocket();
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TcpClient::connect(const string& ip, const unsigned short& port) const
{
    sockaddr_in server_address = buildAddress(ip, port);

    int res = ::connect(_socket, (sockaddr*)& server_address, sizeof(server_address));

    if(res < 0)
    {
        throw ITcpClientCannotConnect(ip, port);
    }
}

TcpClient &TcpClient::createSocket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if(_socket == -1)
    {
        throw ITcpClientCannotCreateSocket();
    }

    return *this;
}

std::vector<char> TcpClient::receive(const unsigned int &len) const
{
    std::vector<char> data(len);

    int bytes_received = recv(_socket, data.data(), len, 0);

    if (bytes_received <= 0)
    {
        throw ITcpClientConnectionWithServerHasBeenClosed();
    }

    return data;
}

void TcpClient::send(const std::vector<char> &data, const unsigned int &len) const noexcept
{
    int bytes_sent = 0;
    while (bytes_sent < len)
    {
        int tmp_len = ::send(_socket, data.data() + bytes_sent, len - bytes_sent, 0);
        bytes_sent += tmp_len;
    }
}

void TcpClient::send(const string &message) const noexcept
{
    int bytes_sent = 0;
    int len = static_cast<int>(message.size());
    while (bytes_sent < message.size())
    {
        int tmp_len = ::send(_socket, message.c_str() + bytes_sent, len - bytes_sent, 0);
        bytes_sent += tmp_len;
    }
}

sockaddr_in TcpClient::buildAddress(const string &ip, const unsigned short &port) const noexcept
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

TcpClient::~TcpClient()
{
#ifdef _WIN32
    closesocket(_socket);
#else
    close(_socket);
#endif
}
