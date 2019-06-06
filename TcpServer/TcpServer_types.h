#ifndef SERVERSOCKET_TCPSERVER_TYPES_H
#define SERVERSOCKET_TCPSERVER_TYPES_H

#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
    using Socket = unsigned long long;
#else
    using Socket = int;
#endif

using string = std::string;
using uint = unsigned int;

#endif //SERVERSOCKET_TCPSERVER_TYPES_H
