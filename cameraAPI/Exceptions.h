#ifndef TCPCLIENT_EXCEPTIONS_H
#define TCPCLIENT_EXCEPTIONS_H

#include <string>

class IRealSenseExceptions : public std::exception
{
public:
    using string = std::string;

    const char* what() const noexcept override
    {
        return "RealSense exception!";
    }

protected:
    string _msg;
};

class IRealSenseSensorsFalls : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "RealSense exception: one of the sensors fails";
    }
};


class IRealSenseRessAndFreq : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "RealSense exception: this ressolution and fps not supported";
    }
};

#endif //TCPCLIENT_EXCEPTIONS_H
