#ifndef REMOTECONTROL_TYPES_H
#define REMOTECONTROL_TYPES_H

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

struct ColorImage
{
    uint64 frame_num;
    uint64 size;
    int64 timestamp_ms;
    uint32 width;
    uint32 height;
    unsigned char *data;
};

#pragma pack(pop)

#endif // REMOTECONTROL_TYPES_H
