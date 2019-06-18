#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <termios.h>
#include "Serial.h"
#include "Exceptions.h"

Serial::Serial() :
    _fd(-1),
    _path()
{

}

bool Serial::connect(const string &path)
{
    _path = path;
    _fd = open(_path.data(), O_RDWR | O_NOCTTY | O_NDELAY);
    if(_fd < 0)
    {
        return false;
//        throw SerialCannotBeOpened(_path);
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

    return true;
}

Serial &Serial::write(const string &msg)
{
    auto bytes_written = ::write(_fd, msg.data(), msg.size());

    if(bytes_written < 0)
    {
        throw SerialCannotWrite();
    }

    return *this;
}

string Serial::read(const uint &len)
{
    std::vector<char> rec(len);
    auto bytes_recieved = ::read(_fd, rec.data(), len);

    if(bytes_recieved < 0)
    {
        throw SerialCannotRead();
    }

    return string(rec.data());
}

Serial::~Serial()
{
    close(_fd);
}
