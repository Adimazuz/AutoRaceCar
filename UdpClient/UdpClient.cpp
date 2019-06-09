#include "UdpClient.h"
#include "Exceptions.h"

UdpClient::UdpClient(const string &ip, const ushort &port) :
    _socket(-1),
    _server_addres()
{
    _server_addres.sin_family = AF_INET;
    _server_addres.sin_port = htons(port);
    _server_addres.sin_addr.s_addr = inet_addr(ip.c_str());

    createSocket();
}

std::vector<char> UdpClient::receive(const unsigned long &len) noexcept
{
    std::vector<char> buffer(len);

    socklen_t address_size = static_cast<unsigned int>(sizeof(_server_addres));

    recvfrom(_socket, buffer.data(), len, 0, reinterpret_cast<sockaddr*>(&_server_addres), &address_size);

    return buffer;
}

void UdpClient::send(const std::vector<char> &msg)
{
    sendto(_socket, msg.data(), msg.size(), 0, reinterpret_cast<sockaddr*>(&_server_addres), sizeof(_server_addres));
}

void UdpClient::send(const string &msg)
{
    sendto(_socket, msg.data(), msg.size(), 0, reinterpret_cast<sockaddr*>(&_server_addres), sizeof(_server_addres));
}

void UdpClient::send(const char *data, const uint &len)
{
    sendto(_socket, data, len, 0, reinterpret_cast<sockaddr*>(&_server_addres), sizeof(_server_addres));
}

UdpClient &UdpClient::createSocket()
{
    _socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(_socket < 0)
    {
        throw UDPClientCannotCreateSocket();
    }

    return *this;
}
