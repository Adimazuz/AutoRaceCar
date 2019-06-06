#ifndef TCPCLIENT_TYPES_H
#define TCPCLIENT_TYPES_H

#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
    using Socket = unsigned long long;
#else
    using Socket = int;
#endif

using string = std::string;

#endif // TCPCLIENT_TYPES_H
