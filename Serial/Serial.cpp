#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <termios.h>
#include <sys/ioctl.h>
#include <iostream>

#include "Serial.h"
#include "Exceptions.h"

Serial::Serial() :
    _fd(-1),
    _path(),
    _is_connected(false)
{

}

bool Serial::connect(const string &path)
{
    _path = path;
    _fd = open(_path.data(), O_RDWR | O_NOCTTY /*| O_NDELAY*/);
    if(_fd < 0)
    {
        return false;
    }

    struct termios config;

    tcgetattr(_fd, &config);

    config.c_iflag  &= static_cast<uint>(~(IGNBRK | BRKINT  | ICRNL |
                                           INLCR | PARMRK | INPCK | ISTRIP | IXON));
    config.c_oflag = 0;
    config.c_lflag &= static_cast<uint>(~(ECHO | ECHONL | ICANON | IEXTEN | ISIG));
    config.c_cflag &= static_cast<uint>(~(CSIZE | PARENB));
    config.c_cflag  |= CS8;
    config.c_cc[VMIN] = 1;
    config.c_cc[VTIME] = 0;
    cfsetispeed(&config, B9600)  < 0 || cfsetospeed(&config, B9600);
    tcsetattr(_fd, TCSAFLUSH, &config);

    usleep(ARDUINO_REBOOT_MS);
    _is_connected = true;
    return true;
}

Serial &Serial::write(const string &msg)
{
    auto bytes_written = ::write(_fd, msg.data(), msg.size());


    if(bytes_written < 0)
    {
        close(_fd);
        _is_connected = false;
        return *this;
    }


    return *this;
}

Serial &Serial::write(const char &msg)
{
    auto bytes_written = ::write(_fd, &msg, 1);
//TODO add close(fd)
    if(bytes_written < 0)
    {
        close(_fd);
        _is_connected = false;
        return *this;
    }


    return *this;
}

string Serial::read(const uint &len)
{  
//    uint bytes_received = 0;
//    std::vector<char> rec(len);
//    while(bytes_received < len)
//    {
//        auto curr_byes = ::read(_fd, rec.data(), len);
//        if(curr_byes <= 0)
//        {
//            _is_connected = false;
//            rec.clear();
//            return string(rec.data());
//        }
//        bytes_received += curr_byes;
//    }

//    return string(rec.data());
}

void Serial::read(char *dst, const uint &len)
{
//    int available_bytes = 0;
//    ioctl(_fd, TIOCINQ, &available_bytes);
//    int timeout = 0;
//    while(available_bytes < len)
//    {
//        ioctl(_fd, TIOCINQ, &available_bytes);

////        timeout++;
////        if (timeout > 100000){
////            return;
////        }
//    }

//    auto bytes_recieved = ::read(_fd, dst, len);

//    if(bytes_recieved < 0)
//    {
//        throw SerialCannotRead();
//    }

    uint bytes_received = 0;
    while(bytes_received < len)
    {
        auto curr_byes = ::read(_fd, dst + bytes_received, len - bytes_received);
        if(curr_byes <= 0)
        {
            _is_connected = false;
            return;
        }
        bytes_received += curr_byes;
    }
}

Serial::~Serial()
{
    close(_fd);
}
