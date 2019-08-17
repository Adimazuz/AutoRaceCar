#ifndef SERIAL_H
#define SERIAL_H

#include "ISerial.h"

class Serial : public ISerial
{
public:
    Serial();
    virtual bool connect(const string &path = "/dev/ttyACM0") override;
    virtual Serial &write(const string &msg) override;
    virtual Serial &write(const char &msg) override;
    virtual string read(const uint &len) override;
    virtual void read(char *dst, const uint &len) override;
    virtual bool isConnected() const override {return _is_connected;}
    virtual ~Serial() override;

private:
    static constexpr int ARDUINO_REBOOT_MS = 3500000;

    int _fd;
    string _path;
    bool _is_connected;
};

#endif // SERIAL_H





