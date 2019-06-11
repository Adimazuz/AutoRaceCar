#ifndef ISERIAL_H
#define ISERIAL_H

/**
  ISerial library for open serial connection and use read and write to a file descriptor.
  first need to call connect function and give the path to the file descriptor,
  then one can use read and write to the file descriptor
  */

#include "Serial_types.h"

class ISerial
{
public:

    /**
     * @brief create new instance of ISerial
     * @return Iserial instance
     */
    static std::shared_ptr<ISerial> create();

    /**
     * @brief connect with serial connection to a file descriptor
     * @param path - the path to the file descriptor
     * @return this
     */
    virtual bool connect(const string &path = "/dev/ttyACM0") = 0;

    /**
     * @brief write string to the file descriptor
     * @param msg - the string to write
     * @return this
     */
    virtual ISerial &write(const string &msg) = 0;

    /**
     * @brief read string from the file descriptor, block function
     * @param len - the length of the string[bytes]
     * @return the string was read from the file descriptor
     */
    virtual string read(const uint &len) = 0;

    /**
     * @brief destructor
     */
    virtual ~ISerial() = default;
};

#endif // ISERIAL_H
