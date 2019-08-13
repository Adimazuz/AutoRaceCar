#include <iostream>

#include "Exceptions.h"
#include "TcpClient.h"

#ifdef _WIN32
#include <inaddr.h>
#else
    #include <arpa/inet.h>
    #include <unistd.h> 
    #include <fcntl.h>
#endif

TcpClient::TcpClient() noexcept :
        _socket(-1),
        _address(),
        _is_connected(false),
        _is_unblocking(false),
        _unblocking_flag(false)
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

void TcpClient::connect(const string& ip, const unsigned short& port)
{
    sockaddr_in server_address = buildAddress(ip, port);

    int res = ::connect(_socket, reinterpret_cast<sockaddr*>(& server_address),
                        sizeof(server_address));
    if(res < 0)
    {
        _is_connected = false;
        return;
    }

    _is_connected = true;
    if(_unblocking_flag)
    {
        setUnblocking(true);
    }
}

void TcpClient::setUnblocking(const bool &new_val)
{
    if(_is_connected)
    {
        if(new_val)
        {
            int flags = fcntl(_socket, F_GETFL);
            fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
        }
        else
        {
            int flags = fcntl(_socket, F_GETFL);
            fcntl(_socket, F_SETFL, flags | !O_NONBLOCK);
        }

        _is_unblocking = new_val;
    }

    _unblocking_flag = new_val;
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

void TcpClient::receive(char *dst, const uint &len)
{
    uint bytes_received = 0;

    while(bytes_received < len)
    {
        auto tmp_len = recv(_socket, dst + bytes_received, len - bytes_received, 0);

        if(tmp_len == 0)
        {
            _is_connected = false;
            return;
        }

        else if(tmp_len < 0)
        {
            return;
        }

        bytes_received += tmp_len;
    }
}

void TcpClient::send(const std::vector<char> &data) noexcept
{
    uint bytes_sent = 0;
    while (bytes_sent < data.size())
    {
        auto tmp_len = ::send(_socket, data.data() + bytes_sent, data.size() - bytes_sent, MSG_NOSIGNAL);

        if(tmp_len < 0)
        {
            _is_connected = false;
            return;
        }

        bytes_sent += tmp_len;
    }
}

void TcpClient::send(const string &message) noexcept
{
    uint bytes_sent = 0;
    uint len = static_cast<uint>(message.size());
    while (bytes_sent < message.size())
    {
        auto tmp_len = ::send(_socket, message.c_str() + bytes_sent, len - bytes_sent, MSG_NOSIGNAL);

        if(tmp_len < 0)
        {
            _is_connected = false;
            return;
        }

        bytes_sent += tmp_len;
    }
}

void TcpClient::send(const char *data, const uint &len) noexcept
{
    uint bytes_sent = 0;
    while (bytes_sent < len)
    {
        auto tmp_len = ::send(_socket, data + bytes_sent, len - bytes_sent, MSG_NOSIGNAL);

        if(tmp_len < 0)
        {
            _is_connected = false;
            return;
        }

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
