#ifndef SERVERSOCKET_EXCEPTIONS_H
#define SERVERSOCKET_EXCEPTIONS_H

#include <exception>
#include <string>

class ITcpServerExceptions : public std::exception
{
public:

    const char* what() const noexcept override
    {
        return "ITcpServer exception!";
    }

protected:
    using string = std::string;

    string _msg;
};

class ITcpServerCannotCreateSocket : public ITcpServerExceptions
{
public:
    const char* what() const noexcept override
    {
        return "ITcpServer exception: cannot create socket";
    }
};

class ITcpServerCannotBind : public ITcpServerExceptions
{
public:

    explicit ITcpServerCannotBind(const string &ip, const unsigned short &port)
    {
        _msg = "ITcpServer exception: cannot bind to ip " + ip +
                " at port " + std::to_string(port);
    }
    const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};

class ITcpServerCannotListen : public ITcpServerExceptions
{
public:
    const char* what() const noexcept override
    {
        return "ITcpServer exception: cannot listen";
    }
};

class ITcpServerCannotAccept : public ITcpServerExceptions
{
public:
    const char* what() const noexcept override
    {
        return "ITcpServer exception: cannot accept";
    }
};
#endif //SERVERSOCKET_EXCEPTIONS_H
