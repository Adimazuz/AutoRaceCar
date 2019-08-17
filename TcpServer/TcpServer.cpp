#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <thread>
#include <signal.h>

#include "Exceptions.h"
#include "TcpServer.h"

#ifdef _WIN32
    #include <inaddr.h>
#else
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

TcpServer::TcpServer() noexcept :
    _ip(""),
    _port(0),
    _max_num_of_clients(0),
    _socket(-1),
    _clients_unblocking_state(),
    _address(),
    _is_bind(false),
    _is_blocking(false)
{
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);
#endif

    signal(SIGPIPE, SIG_IGN);
}

TcpServer &TcpServer::createSocket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if(_is_blocking)
    {
        setUnblocking(true);
    }

    if(_socket == -1)
    {
        throw ITcpServerCannotCreateSocket();
    }

    return *this;
}

TcpServer &TcpServer::doBind()
{
    int res = ::bind(_socket, reinterpret_cast<sockaddr*>(& _address), sizeof(_address));
    if(res < 0)
    {
        _is_bind = false;
    }
    else
    {
        _is_bind = true;
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

    for(auto client : _clients_unblocking_state)
    {
#ifdef _WIN32
    closesocket(client.first);
#else
    close(client.first);
#endif
    }

#ifdef _WIN32
    closesocket(_socket);
#else
    close(_socket);
#endif
}

void TcpServer::bind(const string &ip, const unsigned short &port, const int &max_num_of_clients) noexcept
{
    _address = buildAddress(ip, port);
    _max_num_of_clients = max_num_of_clients;
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

void TcpServer::receive(const Socket &socket, char *dst, const uint &len)
{
    uint bytes_received = 0;

    while(bytes_received < len)
    {
        auto tmp_len = recv(socket, dst + bytes_received, len - bytes_received, 0);

        if(tmp_len == 0)
        {
            _clients_unblocking_state.erase(socket);
            return;
        }

        else if(tmp_len < 0)
        {
            return;
        }

        bytes_received += tmp_len;
    }
}

Socket TcpServer::waitForConnections(const uint &timeout_sec)
{
    if(!_is_bind)
    {
        return -1;
    }

    Address address = {};

    sockaddr_in client = buildAddress(address.ip, address.port);

    Socket client_socket = doAccept(client);

    if(client_socket == -1)
    {
        if(errno == EWOULDBLOCK)
        {
            std::this_thread::sleep_for(std::chrono::seconds(timeout_sec));
            return -1;
        }
        else
        {
            throw ITcpServerCannotAccept();
        }
    }

    _clients_unblocking_state.insert(std::pair<Socket, bool>(client_socket, false));
    return client_socket;
}

void TcpServer::setUnblocking(const bool &new_val)
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

    _is_blocking = true;
}

void TcpServer::setClientUnblocking(const Socket &socket, const bool &new_val)
{
    auto client = _clients_unblocking_state.find(socket);
    if(client == _clients_unblocking_state.end())
    {
        return;
    }

    _clients_unblocking_state[socket] = true;

    if(new_val)
    {
        int flags = fcntl(socket, F_GETFL);
        fcntl(socket, F_SETFL, flags | O_NONBLOCK);
    }
    else
    {
        int flags = fcntl(socket, F_GETFL);
        fcntl(socket, F_SETFL, flags | !O_NONBLOCK);
    }
}

void TcpServer::send(const Socket &socket, const std::vector<char> &data) noexcept
{  
    uint bytes_sent = 0;
    while (bytes_sent < data.size())
    {
        auto tmp_len = ::send(socket, data.data() + bytes_sent, data.size() - bytes_sent,
                              MSG_NOSIGNAL);

        if(tmp_len < 0)
        {
            _clients_unblocking_state.erase(socket);
            return;
        }

        bytes_sent += tmp_len;
    }
}

void TcpServer::send(const Socket &socket, const string &message) noexcept
{
    uint bytes_sent = 0;
    uint len = static_cast<uint>(message.size());
    while (bytes_sent < message.size())
    {
        auto tmp_len = ::send(socket, message.c_str() + bytes_sent, len - bytes_sent,
                              MSG_NOSIGNAL);

        if(tmp_len < 0)
        {
            _clients_unblocking_state.erase(socket);
            return;
        }

        bytes_sent += tmp_len;
    }
}

void TcpServer::send(const Socket &socket, const char *data, const uint &len) noexcept
{
    uint bytes_sent = 0;
    while (bytes_sent < len)
    {
        auto tmp_len = ::send(socket, data + bytes_sent, len - bytes_sent, MSG_NOSIGNAL);

        if(tmp_len < 0)
        {
            _clients_unblocking_state.erase(socket);
            return;
        }

        bytes_sent += tmp_len;
    }
}

bool TcpServer::hasConnectionWithSocket(const Socket &socket)
{
    auto client = _clients_unblocking_state.find(socket);

    return client != _clients_unblocking_state.end();
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
