#ifndef CHAOS_TYPES_H
#define CHAOS_TYPES_H
#include "Camera_types.h"
#include "bitcraze_types.h"

namespace Chaos {

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

#pragma pack(push,1)
//TODO add bytes_per_pixel to ColorImage only
constexpr int COLOR_HEADER = 1;
constexpr int DEPTH_HEADER = 2;

struct header
{
    int type_code;
    uint64 total_size;
};

struct ColorImage
{
    uint64 frame_num;
    uint64 size;
    int32 bytes_per_pixel;
    int64 host_ts_ms;
    int64 camera_ts_ms;
    uint32 width;
    uint32 height;
    uint64 compressed_size;
    unsigned char *compresed_data;
};

struct DepthImage
{
    uint64 frame_num;
    uint64 size;
    int32 bytes_per_pixel;
    int64 host_ts_ms;
    int64 camera_ts_ms;
    uint32 width;
    uint32 height;
    real32 depth_scale;
    uint64 compressed_size;
    unsigned char *compresed_data;
};


struct ColorPacket
{
    Camera::EulerAngles euler_angl;
    Camera::AccelData accel_data;
    Flow flow_data;
    ColorImage image;

};

struct DepthPacket
{
    Camera::EulerAngles euler_angl;
    Camera::AccelData accel_data;
    Flow flow_data;
    DepthImage image;
};





#pragma pack(pop)
}



#endif // CHAOS_TYPES_H
