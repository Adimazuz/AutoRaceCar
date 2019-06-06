#ifndef TCPSOCKET_ITCPCLIENT_H
#define TCPSOCKET_ITCPCLIENT_H

/**
  ITcpClient is an interface for opening client TCP communication and communicate with a TCP server.

  example of sending data:

        std::shared_ptr<ITcpClient> client = ITcpClient::create();

        client->connect("127.0.0.1", 5555);

        char *data = new char[10];
        client->send(data, 10);

  example of receiving data:

        std::shared_ptr<ITcpClient> client = ITcpClient::create();

        client->connect("127.0.0.1", 5555);

        std::vector<char> rec = client->receive(10);
  */

#include "TcpClient_types.h"

class ITcpClient {
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
    virtual void connect(const string& ip, const unsigned short& port) const = 0;

    /**
     * @brief receive data from the server
     * @param len - the length of the data[bytes]
     * @return a vector of chars contains the data
     */
    virtual std::vector<char> receive(const unsigned int &len) const = 0;

    /**
     * @brief send data to the server
     * @param data - a vector which constains the data
     */
    virtual void send(const std::vector<char>& data) const noexcept = 0;

    /**
     * @brief send string to the server
     * @param message - the message to by sent
     */
    virtual void send(const string& message) const noexcept = 0;

    /**
     * @brief send data to the server
     * @param data - pointer to data to be sent
     * @param len - the length of te data[bytes]
     */
    virtual void send(const char* data, const uint &len) const noexcept = 0;

    /**
      * @brief destructor
      */
    virtual ~ITcpClient() noexcept = default;
};

#endif //TCPSOCKET_ITCPCLIENT_H
