#ifndef TCPSOCKET_ITCPCLIENT_H
#define TCPSOCKET_ITCPCLIENT_H

#ifdef EXPORTS
    #define TCP_CLIENT_API __attribute__((visibilty ("default")))
#else
    #define TCP_CLIENT_API
#endif

/**
  ITcpClient is an interface for opening client TCP communication and communicate with a TCP server.

  example of sending data:

        std::shared_ptr<ITcpClient> client = ITcpClient::create();

        client->connect("127.0.0.1", 5555);

        if(client->isConnected())
        {
            char *data = new char[10];
            client->send(data, 10);
            delete[] data;
        }

  example of receiving data:

        std::shared_ptr<ITcpClient> client = ITcpClient::create();

        client->connect("127.0.0.1", 5555);

        if(client->isConnected())
        {
            char *data = new char[10];
            std::vector<char> rcv = client->receive(data, 10, true, 3);
            if(rcv.size() > 0)
            {
                //do something
            }
        }
  */

#include "TcpClient_types.h"

class TCP_CLIENT_API ITcpClient {
public:

    /**
     * @brief create an instance of the interface
     * @return pointer to the interfcace
     */
    static std::shared_ptr<ITcpClient> create();

    /**
     * @brief connect to a tcp server
     * @param ip - the ip address of the server
     * @param port - the port defined by the server
     */
    virtual void connect(const string& ip, const unsigned short& port) = 0;

    /**
     * @brief isConnected - check if client is connected
     * @return true if client is connected, otherwise return false
     */
    virtual bool isConnected() const = 0;

    /**
     * @brief disconnect - disconnect from server
     */
    virtual void disconnect() = 0;

    /**
     * @brief receive data from the server
     * @param len - the length of the data[bytes]
     * @param timeout_sec - determine how much time in seconds wait for receive, in case of timeout_sec = 0,
     * the function will be nonblocking
     */
    virtual void receive(char *dst, const uint &len, const uint &timeout_sec = 3) = 0;

    /**
     * @brief send data to the server
     * @param data - a vector which constains the data
     */
    virtual void send(const std::vector<char>& data) noexcept = 0;

    /**
     * @brief send string to the server
     * @param message - the message to by sent
     */
    virtual void send(const string& message) noexcept = 0;

    /**
     * @brief send data to the server
     * @param data - pointer to data to be sent
     * @param len - the length of te data[bytes]
     */
    virtual void send(const char* data, const uint &len) noexcept = 0;

    /**
      * @brief destructor
      */
    virtual ~ITcpClient() noexcept = default;
};

#endif //TCPSOCKET_ITCPCLIENT_H
