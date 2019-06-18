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


class IRealSenseColorRessAndFreq : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "RealSense exception: this ressolution and fps not supported on color frame mode";
    }
};

class IRealSenseInfraRessAndFreqY16 : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "RealSense exception: this ressolution and fps not supported on infra red frame mode Y16";
    }
};

class IRealSenseInfraRessAndFreq : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "RealSense exception: resolution 1280x800 not supported on such fps";
    }
};

#endif //TCPCLIENT_EXCEPTIONS_H
