#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using string = std::string;
using ushort = unsigned short;

class UDPServerExceptions : public std::exception
{
public:
    UDPServerExceptions()
    {
        _msg = "UDPServer exception";
    }

    const char *what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    string _msg;
};

class UDPServerCannotCreateSocket : public UDPServerExceptions
{
public:
    UDPServerCannotCreateSocket()
    {
        _msg = "UDPServer exception: cannot create socket";
    }

    const char *what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    string _msg;
};

class UDPServerCannotBind : public UDPServerExceptions
{
public:
    UDPServerCannotBind(const string &ip, const ushort &port)
    {
        _msg = "UDPServer exception: cannot bind to ip: " + ip + " at port: " + std::to_string(port);
    }

    const char *what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    string _msg;
};

class UDPServerNoClientAddress : public UDPServerExceptions
{
public:
    UDPServerNoClientAddress()
    {
        _msg = "UDPServer exception: thers is no client address";
    }

    const char *what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    string _msg;
};

#endif // EXCEPTIONS_H
