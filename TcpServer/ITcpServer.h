#ifndef SERVERSOCKET_ITCPSERVER_H
#define SERVERSOCKET_ITCPSERVER_H

#include "TcpSocket_types.h"

class ITcpServer
{
public:

    static std::shared_ptr<ITcpServer> create(const string &ip, const int &port,
                                               const int &max_num_of_clients);

    virtual Socket waitForConnections(Address &address) const = 0;

    virtual std::vector<char> receive(const Socket &socket,
            const unsigned int &len) const noexcept = 0;

    virtual void send(const Socket& socket, const std::vector<char>& data,
            const unsigned int& len) const noexcept = 0;

    virtual void send(const Socket& socket, const string& message) const noexcept = 0;
};


#endif //SERVERSOCKET_ITCPSERVER_H
