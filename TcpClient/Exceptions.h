#ifndef TCPCLIENT_EXCEPTIONS_H
#define TCPCLIENT_EXCEPTIONS_H

#include <string>

class ITcpClientExceptions : public std::exception
{
public:
    using string = std::string;

    const char* what() const noexcept override
    {
        return "ITcpClient exception!";
    }

protected:
    string _msg;
};

class ITcpClientCannotCreateSocket : public ITcpClientExceptions
{
public:
    const char* what() const noexcept override
    {
        return "ITcpClient exception: cannot create socket";
    }
};

class ITcpClientCannotConnect : public ITcpClientExceptions
{
public:

    explicit ITcpClientCannotConnect(const string &ip, const unsigned short& port)
    {
        _msg = "ITcpClient exception: cannot connect to ip " + ip +
                " at port " + std::to_string(port);
    }
    const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};

class ITcpClientConnectionWithServerHasBeenClosed : public ITcpClientExceptions
{
public:
    const char* what() const noexcept override
    {
        return "ITcpClient exception: the connection with the server has been closed";
    }
};

#endif //TCPCLIENT_EXCEPTIONS_H
