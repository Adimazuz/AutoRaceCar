#include "UdpServer.h"
#include "Exceptions.h"
#include <iostream>

UdpServer::UdpServer(const string &ip, const ushort &port) :
    _socket(-1),
    _client_address()
{
    createSocket().bind(ip, port);
    _client_address.sin_port = 0;
}

UdpServer &UdpServer::createSocket()
{
    _socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(_socket < 0)
    {
        throw UDPServerCannotCreateSocket();
    }

    return *this;
}

UdpServer &UdpServer::bind(const string &ip, const ushort &port)
{
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip.c_str());

    auto res = ::bind(_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof (server_address));

    if(res < 0)
    {
        throw UDPServerCannotBind(ip, port);
    }

    return *this;
}

std::vector<char> UdpServer::receive(const unsigned long &len) noexcept
{
    std::vector<char> buffer(len);

    socklen_t address_size = static_cast<unsigned int>(sizeof(_client_address));

    recvfrom(_socket, buffer.data(), len, 0, reinterpret_cast<sockaddr*>(&_client_address), &address_size);

    return buffer;
}

void UdpServer::receive(char *dst, const unsigned long &len)
{
    uint tot_rcv_bytes = 0;
    socklen_t address_size = static_cast<unsigned int>(sizeof(_client_address));

    while(tot_rcv_bytes < len)
    {
        auto rcv_bytes = recvfrom(_socket, dst + tot_rcv_bytes, len - tot_rcv_bytes, 0, 
                                  reinterpret_cast<sockaddr*>(&_client_address), &address_size);
        std::cout << rcv_bytes << std::endl;
        tot_rcv_bytes += rcv_bytes;
    }
}

void UdpServer::send(const std::vector<char> &data)
{
    if(_client_address.sin_port == 0)
    {
        throw UDPServerNoClientAddress();
    }

    sendto(_socket, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&_client_address), sizeof(_client_address));
}

void UdpServer::send(const string &msg)
{
    if(_client_address.sin_port == 0)
    {
        throw UDPServerNoClientAddress();
    }

    sendto(_socket, msg.data(), msg.size(), 0, reinterpret_cast<sockaddr*>(&_client_address), sizeof(_client_address));
}
