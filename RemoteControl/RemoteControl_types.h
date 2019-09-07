#ifndef REMOTECONTROL_TYPES_H
#define REMOTECONTROL_TYPES_H

#include <vector>

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;
using real32 = float;
using real64 = double;

#pragma pack(push, 1)

struct DepthMap
{
    std::vector<uint8> data;
    std::vector<real64> distances;
    real64 avg;
    real64 sdv;
    uint16 min;
    uint16 max;
};

#pragma pack(pop)

#endif // REMOTECONTROL_TYPES_H
