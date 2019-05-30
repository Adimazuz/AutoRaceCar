#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using string = std::string;
using ushort = unsigned short;

class UDPClientExceptions : public std::exception
{
public:
    UDPClientExceptions()
    {
        _msg = "UDPClient exception";
    }

    const char *what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    string _msg;
};

class UDPClientCannotCreateSocket : public UDPClientExceptions
{
public:
    UDPClientCannotCreateSocket()
    {
        _msg = "UDPClient exception: cannot create socket";
    }

    const char *what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    string _msg;
};

#endif // EXCEPTIONS_H
