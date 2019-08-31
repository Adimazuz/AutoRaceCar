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

class IRealSenseDepthRessAndFreq : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "RealSense exception: resolution 1280x720 not supported on such fps";
    }
};

class IRealSenseIntrinsic : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "Can't get intrinsics for some camera stream";
    }
};

class IRealSenseMotionIntrinsic : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "Can't get intrinsics from motion sensor";
    }
};

class IRealSenseMotionExtrinsic : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "Can't get Extrinsics";
    }
};

class IRealSenseBadSettingUse : public IRealSenseExceptions
{
public:
    const char* what() const noexcept override
    {
        return "didn't got frame from the set";
    }
};


#endif //TCPCLIENT_EXCEPTIONS_H
