/**
  Interface to camera RealSense
  *NOTES:
  * 1). the camera adapt the ressolutions and the FPSs the she can provide
  * acording the USB cable that connect the camera and the host
  * (i.e. camera calculate the throughput that she can provide
  * according the cable)
  * all the iterface is assume that the camera connected with
  * USB3 cable.
  *
  * 2). the general flow of use is:
  * -turnon the camera (start camera)
  * -setup wanted frames from the camera
  * -capture the frame in any time u want it



  */


#ifndef REALSENSEAPI_H
#define REALSENSEAPI_H

#include <librealsense2/rs.hpp>
#include "Camera_types.h"

class RealSense{

public:
        enum class sensor_name //TODO update names
        {
            SRERIO_MODULE,
            RGB_CAMERA,
            MOTION_MODULE
        };

        enum class Stream
        {
            ANY,
            DEPTH                            , /**< Native stream of depth data produced by RealSense device */
            COLOR                            , /**< Native stream of color data captured by RealSense device */
            INFRARED                         , /**< Native stream of infrared data captured by RealSense device */
            FISHEYE                          , /**< Native stream of fish-eye (wide) data captured from the dedicate motion camera */
            GYRO                             , /**< Native stream of gyroscope motion data produced by RealSense device */
            ACCEL                            , /**< Native stream of accelerometer motion data produced by RealSense device */
            GPIO                             , /**< Signals from external device connected through GPIO */
            POSE                             , /**< 6 Degrees of Freedom pose data, calculated by RealSense device */
            CONFIDENCE                       , /**< 4 bit per-pixel depth confidence level */
            COUNT
        };

//        enum class FrameFormat
//        {
//            FORMAT_ANY             , /**< When passed to enable stream, librealsense will try to provide best suited format */
//            FORMAT_Z16             , /**< 16-bit linear depth values. The depth is meters is equal to depth scale * pixel value. */
//            FORMAT_DISPARITY16     , /**< 16-bit float-point disparity values. Depth->Disparity conversion : Disparity = Baseline*FocalLength/Depth. */
//            FORMAT_XYZ32F          , /**< 32-bit floating point 3D coordinates. */
//            FORMAT_YUYV            , /**< 32-bit y0, u, y1, v data for every two pixels. Similar to YUV422 but packed in a different order - https://en.wikipedia.org/wiki/YUV */
//            FORMAT_RGB8            , /**< 8-bit red, green and blue channels */
//            FORMAT_BGR8            , /**< 8-bit blue, green, and red channels -- suitable for OpenCV */
//            FORMAT_RGBA8           , /**< 8-bit red, green and blue channels + constant alpha channel equal to FF */
//            FORMAT_BGRA8           , /**< 8-bit blue, green, and red channels + constant alpha channel equal to FF */
//            FORMAT_Y8              , /**< 8-bit per-pixel grayscars2_stream_profilele image */
//            FORMAT_Y16             , /**< 16-bit per-pixel grayscale image */
//            FORMAT_RAW10           , /**< Four 10 bits per pixel luminance values packed into a 5-byte macropixel */
//            FORMAT_RAW16           , /**< 16-bit raw image */
//            FORMAT_RAW8            , /**< 8-bit raw image */
//            FORMAT_UYVY            , /**< Similar to the standard YUYV pixel format, but packed in a different order */
//            FORMAT_MOTION_RAW      , /**< Raw data from the motion sensor */
//            FORMAT_MOTION_XYZ32F   , /**< Motion data packed as 3 32-bit float values, for X, Y, and Z axis */
//            FORMAT_GPIO_RAW        , /**< Raw data from the external sensors hooked to one of the GPIO's */
//            FORMAT_6DOF            , /**< Pose data packed as floats array, containing translation vector, rotation quaternion and prediction velocities and accelerations vectors */
//            FORMAT_DISPARITY32     , /**< 32-bit float-point disparity values. Depth->Disparity conversion : Disparity = Baseline*FocalLength/Depth */
//            FORMAT_Y10BPACK        , /**< 16-bit per-pixel grayscale image unpacked from 10 bits per pixel packed ([8:8:8:8:2222]) grey-scale image. The data is unpacked to LSB and padded with 6 zero bits */
//            FORMAT_DISTANCE        , /**< 32-bit float-point depth distance value.  */
//            FORMAT_COUNT             /**< Number of enumeration values. Not a valid input: intended to be used in for-loops. */
//        };

        enum class ColorFrameFormat
        {
            YUYV            , /**< 32-bit y0, u, y1, v data for every two pixels. Similar to YUV422 but packed in a different order - https://en.wikipedia.org/wiki/YUV */
            RGB8            , /**< 8-bit red, green and blue channels */
            BGR8            , /**< 8-bit blue, green, and red channels -- suitable for OpenCV */
            RGBA8           , /**< 8-bit red, green and blue channels + constant alpha channel equal to FF */
            BGRA8           , /**< 8-bit blue, green, and red channels + constant alpha channel equal to FF */
            Y16             , /**< 16-bit per-pixel grayscale image */
        };

        enum class ColorRessolution
        {
            R_1920x1080,
            R_1280x720,
            R_960_540,
            R_848_480,
            R_640x480,
            R_640x360,
            R_424x240,
            R_320x240,
            R_320x180
        };

        enum class ColorCamFps
        {
            F_60hz,
            F_30hz,
            F_15hz,
            F_6hz
        };

        enum class InfrarFrameFormat
        {
            Y8, /**< 8-bit per-pixel grayscale image */
            Y16 /**< 16-bit per-pixel grayscale image */
        };

        enum class InfrarRessolution
        {
            R_1280x800,
            R_1280x720,
            R_848_480,
            R_640x480,
            R_640x400,
            R_640x360,
            R_480x270,
            R_424x240
        };

        enum class InfrarCamera
        {
            LEFT,
            RIGHT
        };

        enum class InfrarCamFps
        {
            F_90hz,
            F_60hz,
            F_30hz,
            F_25hz,
            F_15hz,
            F_6hz
        };

        enum class DepthRessolution
        {
            R_1280x720,
            R_848_480,
            R_640x480,
            R_640x360,
            R_480x270,
            R_424x240
        };

        enum class DepthCamFps
        {
            F_90hz,
            F_60hz,
            F_30hz,
            F_15hz,
            F_6hz
        };



       RealSense() = default;
       ~RealSense();


       /**
        * @brief connectCamera - assumes that only 1 cammera connected to the divice
        * the function detect the cammera initilize the sensors of the camera
        * @return true- if connected
        * false - if camera not connected
        */
       bool connectCamera();

       /**
        * @brief isConnect - check if camera connected
        * @return
        */
       bool isConnect();


       void resetCamera();


       /**
         * @brief setupColorImage - setup the camera to steam wanted frames.
         * notice that color camera can NOT stream at ress: 1920x1080 or 1280x720 at 60 fps
         * and cant stream at ress: 320x240 or 320x180 at 15 fps
         * @param format: supported formats:
         * RGB8
         * BGR8
         * RGBA8
         * BGRA8
         * YUYV
         * Y16
         * @param ressolution
         * @param fps
         * @return
         */
        void setupColorImage(RealSense::ColorFrameFormat format,RealSense::ColorRessolution ressolution,RealSense::ColorCamFps fps);


        /**
         * @brief setupInfraredImage - setup one of 2 inferar cameras
         * notice that
         * 1). at ressolution 1280x800 camera can work only at 20/25/15 fps
         * 2). format Y16 works only for resolutions: 1280x800 and 640x400 and only at rates 25/15
         * *depth and infrared frames cant be setuped together (same sensors)
         * @param format:
         * Y8
         * Y16
         * @param ressolution
         * @param fps
         * @param side - Left or Right inferar camera
         */
        void setupInfraredImage(RealSense::InfrarFrameFormat format, RealSense::InfrarRessolution ressolution, RealSense::InfrarCamFps fps
                                ,RealSense::InfrarCamera side);

        /**
         * @brief setupDepthImage - setup depth stream in format Z16
         * Z16 = 16-bit linear depth values. The depth is meters is equal to depth scale * pixel value.
         * notice that
         * at resolution 1280x720 camera cant work at 90/60 fps
         * *depth and infrared frames cant be setuped together (same sensors)
         */
        void setupDepthImage(RealSense::DepthRessolution ressolution, RealSense::DepthCamFps fps);

        /**
         * @brief setupGyro - Add streams of gyro to configuration
         */
        void setupGyro();

        /**
         * @brief setupAccel - Add streams of accelerometer to configuration
         */
        void setupAccel();

        /**
         * @brief startCamera - after setups all wanted frames and start
         * streaming according to the configuraion
         */
        void startCamera();


        /**
         * @brief captureFrame - save frame for future use
         * before getting data of specific frame need call this function.
         * this function will wait setuped frames from the camera.
         */
        void captureFrame();


        /**
         * @brief getColorImage - get Color image (accordint the color setups) according
         * the last capture.
         * @return
         */
        Camera::ColorImage getColorImage();

        /**
         * @brief getInfraredImage - get Infrared image acording the setups
         *
         * @return same struct as colorImage
         */
        Camera::ColorImage getInfraredImage();

        /**
         * @brief getDepthImage - get Depth image according the setups
         * @return
         */
        Camera::DepthImage getDepthImage();


        /**
         * @brief getDepthColorizedImage - gets depth image that can be
         * drawn with simple RGB format (3 bytes per pixel)
         * @return
         */
        Camera::ColorImage getDepthColorizedImage();
        /**
         * @brief get_depth_units
         *         //A Depth stream contains an image that is composed of pixels with depth information.
        //The value of each pixel is the distance from the camera, in some distance units.
        //To get the distance in units of meters, each pixel's value should be multiplied by the sensor's depth scale
         * @return
         */
        float getDepthUnits();

        /**
         * @brief getDepthCamIntrinsics - check witch depth stream profile (according what was setuped in setupDepthImage)
         *  is availible
         * and return intrinsics for that lens+ressolution.
         * Call only after startCamera.
         * @return
         */
        Camera::Intrinsics getDepthCamIntrinsics();


        /**
         * @brief getColorCamIntrinsics - check witch color stream profile (according what was setuped in setupDepthImage)
         *  is availible
         * and return intrinsics for lens+ressolution.
         * Call only after startCamera.
         * @return
         */
        Camera::Intrinsics getColorCamIntrinsics();


        /**
         * @brief getIfraRedCamIntrinsics - check witch Infara red stream profile (according what was setuped in setupDepthImage)
         *  is availible
         * and return intrinsics for lens+ressolution.
         * Call only after startCamera.
         * @return
         */
        Camera::Intrinsics getIfraRedCamIntrinsics();

        /**
         * @brief getMotionCamIntrinsics - check witch Motion stream profile (according what was setuped in setupDepthImage)
         *  is availible
         * and return intrinsics for lens+ressolution.
         *     /* \internal
    * Scale X       cross axis  cross axis  Bias X \n
    * cross axis    Scale Y     cross axis  Bias Y \n
    * cross axis    cross axis  Scale Z     Bias Z
         * Call only after startCamera.
         * @return
         */
        Camera::MotionIntrinsics getMotionCamIntrinsics();

        /**
         * @brief getExtrinsics - transformation between any two streams (if such exists)
         * @param from_strea
         * @param to_stream
         * @return
         */
        Camera::Extrinsics getExtrinsics(RealSense::Stream from_stream, RealSense::Stream to_stream);


        /**
         * @brief getAngularVelocities -
         * Call only after startCamera.
         * @return struct   x_pitch;
                            y_yaw;
                            z_roll;
         */
        Camera::AngularVelocities getAngularVelocities();

        /**
         * @brief getAccelData
         * Call only after startCamera.
         * @return
         */
        Camera::AccelData getAccelData();






        //TODO why we need that?
//        /**
//         * @brief getMyFps -
//         * @param stream
//         * @return
//         */
//        unsigned int getMyFps(RealSense::Stream stream);

private:

      rs2::device _camera;
      //for config settings
      rs2::sensor _stereo_module;
      rs2::sensor _rgb_camera;
      rs2::sensor _motion_module;

      rs2::pipeline _pipe;
      rs2::pipeline_profile _pipe_profile;
      rs2::config _config;
      unsigned long _last_frame_ts;


      rs2::frameset _frames;

      Camera::AngularVelocities _last_euler_angles;
      Camera::AccelData _last_accel_data;

      rs2::colorizer colorize;
      rs2::decimation_filter decimate;

};

#endif // REALSENSEAPI_H
