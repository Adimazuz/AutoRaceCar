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
    uint64 _frame_num;
    uint64 _size;
    uint64 _timestamp_ms;
    uint32 _width;
    uint32 _height;
    const unsigned char *_data;
};

struct DepthImage
{
    uint64 _frame_num;
    uint64 _size;
    uint64 _timestamp_ms;
    uint32 _width;
    uint32 _height;
    real32 depth_scale;
    const unsigned char *_data;
};

#pragma pack(pop)

}


#endif // CAMERA_TYPES_H
