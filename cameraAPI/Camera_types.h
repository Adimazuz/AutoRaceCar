#ifndef CAMERA_TYPES_H
#define CAMERA_TYPES_H

namespace Camera {

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using real32 = float;
using real64 = double;

#pragma pack(push,1)

struct ColorImage
{
    uint64 frame_num;
    uint64 size;
    int64 timestamp_ms;
    int32 width;
    int32 height;
    const unsigned char *data;
};

struct DepthImage
{
    uint64 frame_num;
    uint64 size;
    int64 timestamp_ms;
    int32 width;
    int32 height;
    real32 depth_scale;
    const unsigned char *data;
};

#pragma pack(pop)

}


#endif // CAMERA_TYPES_H
