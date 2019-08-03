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
using uint64 = unsigned long;
using real32 = float;
using real64 = double;

#pragma pack(push,1)

struct ColorImage
{
    uint64 frame_num;
    uint64 size;
    int64 timestamp_ms;
    uint32 width;
    uint32 height;
    const unsigned char *data;
};

struct DepthImage
{
    uint64 frame_num;
    uint64 size;
    int64 timestamp_ms;
    uint32 width;
    uint32 height;
    real32 depth_scale;
    const unsigned char *data;
};


struct Intrinsics
{
    real32         ppx;       /**< Horizontal coordinate of the principal point of the image, as a pixel offset from the left edge */
    real32         ppy;       /**< Vertical coordinate of the principal point of the image, as a pixel offset from the top edge */
    real32         fx;        /**< Focal length of the image plane, as a multiple of pixel width */
    real32         fy;        /**< Focal length of the image plane, as a multiple of pixel height */
//    rs2_distortion model;    /**< Distortion model of the image */
    real32         coeffs[5]; /**< Distortion coefficients, order: k1, k2, p1, p2, k3 */
};


struct MotionIntrinsics
{
    /* \internal
    * Scale X       cross axis  cross axis  Bias X \n
    * cross axis    Scale Y     cross axis  Bias Y \n
    * cross axis    cross axis  Scale Z     Bias Z */
    float data[3][4];          /**< Interpret data array values */

    float noise_variances[3];  /**< Variance of noise for X, Y, and Z axis */
    float bias_variances[3];   /**< Variance of bias for X, Y, and Z axis */
};

#pragma pack(pop)

}


#endif // CAMERA_TYPES_H
