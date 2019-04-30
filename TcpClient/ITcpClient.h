#ifndef TCPSOCKET_ITCPCLIENT_H
#define TCPSOCKET_ITCPCLIENT_H

#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
    using Socket = unsigned long long;
#else
    using Socket = int;
#endif

using string = std::string;

class ITcpClient {
public:

    static std::shared_ptr<ITcpClient> create();

    virtual void connect(const string& ip, const unsigned short& port) const = 0;

    virtual std::vector<char> receive(const unsigned int &len) const = 0;

    virtual void send(const std::vector<char>& data,
                      const unsigned int& len) const noexcept = 0;

    virtual void send(const string& message) const noexcept = 0;
};


#endif //TCPSOCKET_ITCPCLIENT_H
