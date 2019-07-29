#ifndef DATATYPES_H
#define DATATYPES_H

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

struct Flow
{
    real32 dx;
    real32 dy;
    real32 range;
}
#pragma pack(pop)

#endif // DATATYPES_H
