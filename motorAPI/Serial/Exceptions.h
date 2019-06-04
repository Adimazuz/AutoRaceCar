#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using string = std::string;

class SerialException : public std::exception
{
public:

    SerialException() :
        _msg("SerialException") {}
    const char *what() const  noexcept override{
        return _msg.data();
    }

private:
    string _msg;
};

class SerialCannotBeOpened : public std::exception
{
public:

    SerialCannotBeOpened(const string &path) :
        _msg("SerialCannotBeOpened: serial with the path: " + path + "cannot be opened") {}
    const char *what() const  noexcept override{
        return _msg.data();
    }

private:
    string _msg;
};

class SerialCannotWrite : public std::exception
{
public:

    SerialCannotWrite() :
        _msg("SerialCannotWrite: cannot write data") {}
    const char *what() const  noexcept override{
        return _msg.data();
    }

private:
    string _msg;
};

class SerialCannotRead : public std::exception
{
public:

    SerialCannotRead() :
        _msg("SerialCannotRead: cannot read data") {}
    const char *what() const  noexcept override{
        return _msg.data();
    }

private:
    string _msg;
};

#endif // EXCEPTIONS_H
