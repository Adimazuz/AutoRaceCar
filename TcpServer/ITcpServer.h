#ifndef SERVERSOCKET_ITCPSERVER_H
#define SERVERSOCKET_ITCPSERVER_H

#ifdef EXPORTS
    #define TCP_SERVER_API __attribute__((visibilty ("default")))
#else
    #define TCP_SERVER_API
#endif

/**
  ITcpServer is an interface for opening server with TCP communication.

  example of opening connection, wait for client and receive data:

        std::shared_ptr<ITcpServer> server = ITcpServer::create("127.0.0.1", 5555, 5);

        Socket new_client = server->waitForConnections();

        if(server->hasConnectionWithSocket(new_client))
        {
            std::vector<char> rcv = server->receive(new_client, 10);
            if(rcv.size() > 0)
            {
                //do something
            }
        }

  */

#include "TcpServer_types.h"

class TCP_SERVER_API ITcpServer
{
public:

    /**
     * @brief create an instance of the interface
     * @return pointer to the interface
     */
    static std::shared_ptr<ITcpServer> create();

    /**
     * @brief bind - established connection as a server
     * @param ip - the ip of the host(can be reach by type in terminal "ifconfig")
     * @param port - an arbitrary port defined by the host
     * @param max_num_of_clients - the maximum number of clients which can be connect to the server
     */
    virtual void bind(const string &ip, const unsigned short &port, const int &max_num_of_clients) = 0;

    /**
     * @brief isBind - check if the server is bind
     * @return true if server is bind, otherwise return false
     */
    virtual bool isBind() const = 0;

    /**
     * @brief hasConnectionWithSocket - check connection between server and one of his clients
     * @param socket - the id of the client to check connection with
     * @return true if there is connection between server and client, otherwise retrun false
     */
    virtual bool hasConnectionWithSocket(const Socket &socket) = 0;

    /**
     * @brief waitForConnections is a blocking function which is waiting for new client connection
     * @return Socket(typedef for uint) which can be used to reach the connected client
     */
    virtual Socket waitForConnections() = 0;

    /**
     * @brief getNumOfConnectedClients - receive the number of connected clients to this server
     * @return number of connected clients to this server
     */
    virtual unsigned long getNumOfConnectedClients() const = 0;

    /**
     * @brief receive data from a client
     * @param socket - the id of the client
     * @param len - the length of the data[bytes]
     * @return vector of data
     */
    virtual std::vector<char> receive(const Socket &socket,
            const uint &len) noexcept = 0;

    /**
     * @brief send data to a client
     * @param socket - the id of the client
     * @param data - vector of data
     */
    virtual void send(const Socket& socket, const std::vector<char>& data) const noexcept = 0;

    /**
     * @brief send string to a client
     * @param socket - the id of the client
     * @param message - the message to be sent
     */
    virtual void send(const Socket& socket, const string& message) const noexcept = 0;

    /**
     * @brief send data to a client
     * @param socket - the id of the client
     * @param data - pointer to the data to be sent
     * @param len - the length of the data[bytes]
     */
    virtual void send(const Socket& socket, const char *data, const uint &len) const noexcept = 0;

    /**
      * @brief destructor
      */
    virtual ~ITcpServer() noexcept = default ;
};


#endif //SERVERSOCKET_ITCPSERVER_H
