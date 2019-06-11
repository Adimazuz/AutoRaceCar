#ifndef SERIAL_H
#define SERIAL_H

#include "ISerial.h"

class Serial : public ISerial
{
public:
    Serial();
    virtual bool connect(const string &path = "/dev/ttyACM0") override;
    virtual Serial &write(const string &msg) override;
    virtual string read(const uint &len) override;
    virtual ~Serial() override;

private:
    static constexpr int ARDUINO_REBOOT_MS = 3500000;

    int _fd;
    string _path;
};

#endif // SERIAL_H





