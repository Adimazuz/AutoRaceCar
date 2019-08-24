#include "RealSenseAPI.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include "chrono"
#include <thread>
#define NUM_OF_RS_SENSORS 3

//typedef enum rs2_format
//{
//    RS2_FORMAT_ANY             , /**< When passed to enable stream, librealsense will try to provide best suited format */
//    RS2_FORMAT_Z16             , /**< 16-bit linear depth values. The depth is meters is equal to depth scale * pixel value. */
//    RS2_FORMAT_DISPARITY16     , /**< 16-bit float-point disparity values. Depth->Disparity conversion : Disparity = Baseline*FocalLength/Depth. */
//    RS2_FORMAT_XYZ32F          , /**< 32-bit floating point 3D coordinates. */
//    RS2_FORMAT_YUYV            , /**< 32-bit y0, u, y1, v data for every two pixels. Similar to YUV422 but packed in a different order - https://en.wikipedia.org/wiki/YUV */
//    RS2_FORMAT_RGB8            , /**< 8-bit red, green and blue channels */
//    RS2_FORMAT_BGR8            , /**< 8-bit blue, green, and red channels -- suitable for OpenCV */
//    RS2_FORMAT_RGBA8           , /**< 8-bit red, green and blue channels + constant alpha channel equal to FF */
//    RS2_FORMAT_BGRA8           , /**< 8-bit blue, green, and red channels + constant alpha channel equal to FF */
//    RS2_FORMAT_Y8              , /**< 8-bit per-pixel grayscale image */
//    RS2_FORMAT_Y16             , /**< 16-bit per-pixel grayscale image */
//    RS2_FORMAT_RAW10           , /**< Four 10-bit luminance values encoded into a 5-byte macropixel */
//    RS2_FORMAT_RAW16           , /**< 16-bit raw image */
//    RS2_FORMAT_RAW8            , /**< 8-bit raw image */
//    RS2_FORMAT_UYVY            , /**< Similar to the standard YUYV pixel format, but packed in a different order */
//    RS2_FORMAT_MOTION_RAW      , /**< Raw data from the motion sensor */
//    RS2_FORMAT_MOTION_XYZ32F   , /**< Motion data packed as 3 32-bit float values, for X, Y, and Z axis */
//    RS2_FORMAT_GPIO_RAW        , /**< Raw data from the external sensors hooked to one of the GPIO's */
//    RS2_FORMAT_6DOF            , /**< Pose data packed as floats array, containing translation vector, rotation quaternion and prediction velocities and accelerations vectors */
//    RS2_FORMAT_DISPARITY32     , /**< 32-bit float-point disparity values. Depth->Disparity conversion : Disparity = Baseline*FocalLength/Depth */
//    RS2_FORMAT_COUNT             /**< Number of enumeration values. Not a valid input: intended to be used in for-loops. */
//} rs2_format;

static rs2_format converColorFrameFormat(RealSense::ColorFrameFormat format){
    if(format == RealSense::ColorFrameFormat::RGB8){
        return RS2_FORMAT_RGB8;
    }
    if(format == RealSense::ColorFrameFormat::BGR8){
        return RS2_FORMAT_BGR8;
    }
    if(format == RealSense::ColorFrameFormat::RGBA8){
        return RS2_FORMAT_RGBA8;
    }
    if(format == RealSense::ColorFrameFormat::BGRA8){
        return RS2_FORMAT_BGRA8;
    }
    if(format == RealSense::ColorFrameFormat::YUYV){
        return RS2_FORMAT_YUYV;
    }
    if(format == RealSense::ColorFrameFormat::Y16){
        return RS2_FORMAT_Y16;
    }
    return RS2_FORMAT_ANY;
}

static rs2_format converInfraFrameFormat(RealSense::InfrarFrameFormat format){
    if (format == RealSense::InfrarFrameFormat::Y8){
        return RS2_FORMAT_Y8;
    }
    if (format == RealSense::InfrarFrameFormat::Y16){
        return RS2_FORMAT_Y16;
    }
    return RS2_FORMAT_ANY;
}

static void convertColorFPStoInt(RealSense::ColorCamFps fps, int& f_int){
    if(fps == RealSense::ColorCamFps::F_60hz){
        f_int = 60;
    }else if(fps == RealSense::ColorCamFps::F_30hz){
        f_int = 30;
    }else if(fps == RealSense::ColorCamFps::F_15hz){
        f_int = 15;
    }else if(fps == RealSense::ColorCamFps::F_6hz){
        f_int = 6;
    }
}

static void convertInfraFPStoInt(RealSense::InfrarCamFps fps, int& f_int){
    if(fps == RealSense::InfrarCamFps::F_90hz){
        f_int = 90;
    }else if(fps == RealSense::InfrarCamFps::F_60hz){
        f_int = 60;
    }else if(fps == RealSense::InfrarCamFps::F_30hz){
        f_int = 30;
    }else if(fps == RealSense::InfrarCamFps::F_25hz){
        f_int = 25;
    }else if(fps == RealSense::InfrarCamFps::F_15hz){
        f_int = 15;
    }else if(fps == RealSense::InfrarCamFps::F_6hz){
        f_int = 6;
    }
}

static void convertDepthFPStoInt(RealSense::DepthCamFps fps, int& f_int){
    if(fps == RealSense::DepthCamFps::F_90hz){
        f_int = 90;
    }else if(fps == RealSense::DepthCamFps::F_60hz){
        f_int = 60;
    }else if(fps == RealSense::DepthCamFps::F_30hz){
        f_int = 30;
    }else if(fps == RealSense::DepthCamFps::F_15hz){
        f_int = 15;
    }else if(fps == RealSense::DepthCamFps::F_6hz){
        f_int = 6;
    }
}

static void convertColorRessToInt(RealSense::ColorRessolution ressolution, int& w, int& h){
    if(ressolution == RealSense::ColorRessolution::R_1920x1080){
        w = 1920;
        h = 1080;
    }else if(ressolution == RealSense::ColorRessolution::R_1280x720){
        w = 1280;
        h = 720;
    }else if(ressolution == RealSense::ColorRessolution::R_960_540){
        w = 960;
        h = 540;
    }else if(ressolution == RealSense::ColorRessolution::R_848_480){
        w = 848;
        h = 480;
    }else if(ressolution == RealSense::ColorRessolution::R_640x480){
        w = 640;
        h = 480;
    }else if(ressolution == RealSense::ColorRessolution::R_640x360){
        w = 640;
        h = 360;
    }else if(ressolution == RealSense::ColorRessolution::R_424x240){
        w = 424;
        h = 240;
    }else if(ressolution == RealSense::ColorRessolution::R_320x240){
        w = 320;
        h = 240;
    }else if(ressolution == RealSense::ColorRessolution::R_320x180){
        w = 320;
        h = 180;
    }
}

static void convertInfraRessToInt(RealSense::InfrarRessolution ressolution, int& w, int& h){
    if(ressolution == RealSense::InfrarRessolution::R_1280x800){
        w = 1280;
        h = 800;
    }else if(ressolution == RealSense::InfrarRessolution::R_1280x720){
        w = 1280;
        h = 720;
    }else if(ressolution == RealSense::InfrarRessolution::R_848_480){
        w = 848;
        h = 480;
    }else if(ressolution == RealSense::InfrarRessolution::R_640x480){
        w = 640;
        h = 480;
    }else if(ressolution == RealSense::InfrarRessolution::R_640x360){
        w = 640;
        h = 360;
    }else if(ressolution == RealSense::InfrarRessolution::R_480x270){
        w = 480;
        h = 270;
    }else if(ressolution == RealSense::InfrarRessolution::R_424x240){
        w = 424;
        h = 240;
    }
}

static void converDepthRessToInt(RealSense::DepthRessolution ressolution, int& w, int& h){
    if(ressolution == RealSense::DepthRessolution::R_1280x720){
            w = 1280;
            h = 720;
        }else if(ressolution == RealSense::DepthRessolution::R_848_480){
            w = 848;
            h = 480;
        }else if(ressolution == RealSense::DepthRessolution::R_640x480){
            w = 640;
            h = 480;
        }else if(ressolution == RealSense::DepthRessolution::R_640x360){
            w = 640;
            h = 360;
        }else if(ressolution == RealSense::DepthRessolution::R_480x270){
            w = 480;
            h = 270;
        }else if(ressolution == RealSense::DepthRessolution::R_424x240){
            w = 424;
            h = 240;
        }
}

static rs2_stream convertStream(RealSense::Stream stream){
    if(stream == RealSense::Stream::ANY){
        return RS2_STREAM_ANY;
    } else if (stream == RealSense::Stream::DEPTH){
        return RS2_STREAM_DEPTH;
    }else if (stream == RealSense::Stream::COLOR){
        return RS2_STREAM_COLOR;
    }else if (stream == RealSense::Stream::INFRARED){
        return RS2_STREAM_INFRARED;
    }else if (stream == RealSense::Stream::FISHEYE){
        return RS2_STREAM_FISHEYE;
    }else if (stream == RealSense::Stream::GYRO){
        return RS2_STREAM_GYRO;
    }else if (stream == RealSense::Stream::ACCEL){
        return RS2_STREAM_ACCEL;
    }else if (stream == RealSense::Stream::GPIO){
        return RS2_STREAM_GPIO;
    }else if (stream == RealSense::Stream::POSE){
        return RS2_STREAM_POSE;
    }else if (stream == RealSense::Stream::CONFIDENCE){
        return RS2_STREAM_CONFIDENCE;
    }else if (stream == RealSense::Stream::COUNT){
        return RS2_STREAM_COUNT;
    }
}
static int converSide(RealSense::InfrarCamera side){
    if (side == RealSense::InfrarCamera::LEFT){
        return 1;
    }
    return 2;
}

RealSense::~RealSense()
{
    if(this->isConnect()){
        _pipe.stop();
        resetCamera();
    }
}

bool RealSense::connectCamera(){

    rs2::context ctx;
    rs2::device_list devices = ctx.query_devices();
    if (devices.size() == 0){
        return false;

    }
    _camera = devices[0];



    std::vector<rs2::sensor> sensors = devices[0].query_sensors();
    if (sensors.size() < NUM_OF_RS_SENSORS){
        throw IRealSenseColorRessAndFreq();
    }

   _stereo_module = sensors[0];
   _rgb_camera = sensors[1];
   _motion_module = sensors[2];

   return true;
}

bool RealSense::isConnect()
{
//    rs2::context ctx;
//    rs2::device_hub device_h(ctx);
//    return device_h.is_connected(_camera);
    rs2::context ctx;
    rs2::device_list devices = ctx.query_devices();
    if (devices.size() == 0){
        return false;

    }
    return true;

}

void RealSense::resetCamera()
{
    _camera.hardware_reset();
}







void RealSense::setupColorImage(RealSense::ColorFrameFormat format, RealSense::ColorRessolution ressolution, RealSense::ColorCamFps fps)
{

    if(((ressolution == ColorRessolution::R_1920x1080 || ressolution == ColorRessolution::R_1280x720) && fps == ColorCamFps::F_60hz) ||
            (ressolution ==ColorRessolution::R_320x180 || ressolution ==ColorRessolution::R_320x240) && fps == ColorCamFps::F_15hz ){
        throw IRealSenseColorRessAndFreq();
    }
    int w,h,freq;
    convertColorRessToInt(ressolution, w, h);
    convertColorFPStoInt(fps,freq);
    _config.enable_stream(RS2_STREAM_COLOR, w, h, converColorFrameFormat(format), freq);
}

void RealSense::setupInfraredImage(RealSense::InfrarFrameFormat format, RealSense::InfrarRessolution ressolution, RealSense::InfrarCamFps fps,
                                   RealSense::InfrarCamera side)
{
    if(ressolution == InfrarRessolution::R_1280x800 && !(fps == InfrarCamFps::F_30hz || fps == InfrarCamFps::F_25hz || fps == InfrarCamFps::F_15hz)){
        throw IRealSenseInfraRessAndFreq();
    }
    if (format == InfrarFrameFormat::Y16 && !(fps == InfrarCamFps::F_25hz || fps == InfrarCamFps::F_15hz)){
        throw IRealSenseInfraRessAndFreqY16();
    }
    int w,h,freq;
    convertInfraRessToInt(ressolution, w, h);
    convertInfraFPStoInt(fps,freq);
    _config.enable_stream(RS2_STREAM_INFRARED, converSide(side), w, h, converInfraFrameFormat(format),freq);
}

void RealSense::setupDepthImage(RealSense::DepthRessolution ressolution, RealSense::DepthCamFps fps)
{
    if(ressolution == DepthRessolution::R_1280x720 && (fps == DepthCamFps::F_90hz || fps == DepthCamFps::F_60hz)){
        throw IRealSenseDepthRessAndFreq();
    }
    int w,h,freq;
    converDepthRessToInt(ressolution, w, h);
    convertDepthFPStoInt(fps,freq); //same fps as infra
    _config.enable_stream(RS2_STREAM_DEPTH,w,h,RS2_FORMAT_Z16,freq);

}

void RealSense::setupGyro()
{
    _config.enable_stream(RS2_STREAM_GYRO,RS2_FORMAT_MOTION_XYZ32F);
    _last_euler_angles = {0,0,0,0};
}

void RealSense::setupAccel()
{
    _config.enable_stream(RS2_STREAM_ACCEL,RS2_FORMAT_MOTION_XYZ32F);
    _last_accel_data = {0,0,0,0};
}





void RealSense::startCamera()
{
     _pipe_profile = _pipe.start(_config);
}



void RealSense::captureFrame()
{
    _frames = _pipe.wait_for_frames();
//    std::cout << _frames.size() << std::endl;
}

Camera::ColorImage RealSense::getColorImage()
{
    rs2::video_frame color_frame = _frames.get_color_frame();
    auto time_stamp = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto host_time_stamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_stamp).count();
    uint32_t w = color_frame.get_width();
    uint32_t h = color_frame.get_height();
    uint32_t byte_per_pixel = color_frame.get_bytes_per_pixel();

    uint64_t size = w*h*byte_per_pixel;

    Camera::ColorImage cur_image = {color_frame.get_frame_number(), size, color_frame.get_bytes_per_pixel(),
                                    host_time_stamp_ms,
                                    color_frame.get_timestamp(),w, h,
                                    reinterpret_cast<const unsigned char*>(color_frame.get_data())};

//            (reinterpret_cast<const unsigned char*>(color_frame.get_data()),color_frame.get_width(),color_frame.get_height(),
//                    color_frame.get_frame_number(), color_frame.get_timestamp(), color_frame.get_bytes_per_pixel());
    return cur_image;
}

Camera::ColorImage RealSense::getInfraredImage()
{
    rs2::video_frame infrared_frame = _frames.get_infrared_frame();
    auto time_stamp = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto host_time_stamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_stamp).count();
    uint32_t w = infrared_frame.get_width();
    uint32_t h = infrared_frame.get_height();
    uint32_t byte_per_pixel = infrared_frame.get_bytes_per_pixel();

    uint64_t size = w*h*byte_per_pixel;

    Camera::ColorImage cur_image = {infrared_frame.get_frame_number(), size, infrared_frame.get_bytes_per_pixel(),
                                    host_time_stamp_ms,
                                    infrared_frame.get_timestamp(),w, h,
                                    reinterpret_cast<const unsigned char*>(infrared_frame.get_data())};

//    Image cur_image(reinterpret_cast<const unsigned char*>(infrared_frame.get_data()),infrared_frame.get_width(),infrared_frame.get_height(),
//                    infrared_frame.get_frame_number(), time_stamp_ms, infrared_frame.get_bytes_per_pixel());

    return cur_image;
}

Camera::DepthImage RealSense::getDepthImage()
{
    rs2::depth_frame depth_frame = _frames.get_depth_frame();
    auto time_stamp = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto host_time_stamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_stamp).count();
    uint32_t w = depth_frame.get_width();
    uint32_t h = depth_frame.get_height();
    uint32_t byte_per_pixel = depth_frame.get_bytes_per_pixel();

    uint64_t size = w*h*byte_per_pixel;

    Camera::DepthImage cur_image = {depth_frame.get_frame_number(), size, depth_frame.get_bytes_per_pixel(),
                                    host_time_stamp_ms,
                                    depth_frame.get_timestamp(),w, h,
                                    getDepthUnits(),reinterpret_cast<const unsigned char*>(depth_frame.get_data())};
//    Image cur_image(reinterpret_cast<const unsigned char*>(depth_frame.get_data()),depth_frame.get_width(),depth_frame.get_height(),
//                    depth_frame.get_frame_number(), depth_frame.get_timestamp(), depth_frame.get_bytes_per_pixel());

    return cur_image;

}


float RealSense::getDepthUnits()
{
        float scale = _stereo_module.get_option(RS2_OPTION_DEPTH_UNITS);
        return scale;

}


static Camera::Intrinsics getIntrinsicsPerStream(rs2_stream stream_type, rs2::pipeline_profile& pipe_p ){
    rs2::stream_profile stream = pipe_p.get_stream(stream_type);
    Camera::Intrinsics intr;

    auto video_stream = stream.as<rs2::video_stream_profile>();
    try
    {
         rs2_intrinsics intrinsics = video_stream.get_intrinsics();
         intr.ppy = intrinsics.ppy;
         intr.ppx = intrinsics.ppx;
         intr.fy = intrinsics.fy;
         intr.fx = intrinsics.fx;
         intr.coeffs[0] = intrinsics.coeffs[0];
         intr.coeffs[1] = intrinsics.coeffs[1];
         intr.coeffs[2] = intrinsics.coeffs[2];
         intr.coeffs[3] = intrinsics.coeffs[3];
         intr.coeffs[4] = intrinsics.coeffs[4];

    }
    catch (const std::exception& e)
    {
        throw IRealSenseIntrinsic();
    }

    return intr;
}

Camera::Intrinsics RealSense::getDepthCamIntrinsics()
{
    return getIntrinsicsPerStream(RS2_STREAM_DEPTH, _pipe_profile);
}

Camera::Intrinsics RealSense::getColorCamIntrinsics()
{
    return getIntrinsicsPerStream(RS2_STREAM_COLOR, _pipe_profile);
}

Camera::Intrinsics RealSense::getIfraRedCamIntrinsics()
{
    return getIntrinsicsPerStream(RS2_STREAM_INFRARED, _pipe_profile);
}



Camera::MotionIntrinsics RealSense::getMotionCamIntrinsics()
{
    rs2::stream_profile stream = _pipe_profile.get_stream(RS2_STREAM_GYRO); //how much streams from there??
    Camera::MotionIntrinsics mot_intr;

    auto motion_stream = stream.as<rs2::motion_stream_profile>();
    try
    {
         rs2_motion_device_intrinsic intrinsics = motion_stream.get_motion_intrinsics();
         for (int i=0; i<3; ++i){
             for (int j=0; j<4; ++j){
                mot_intr.data[i][j] = intrinsics.data[i][j];
             }
         }
         for(int i=0; i<3; ++i){
             mot_intr.bias_variances[i] = intrinsics.bias_variances[i];
         }
         for(int i=0; i<3; ++i){
             mot_intr.noise_variances[i] = intrinsics.noise_variances[i];
         }

    }
    catch (const std::exception& e)
    {
        throw IRealSenseMotionIntrinsic();
    }

    return mot_intr;
}



Camera::Extrinsics RealSense::getExtrinsics(RealSense::Stream from_stream, RealSense::Stream to_stream)
{
    rs2_stream from_stream_rs = convertStream(from_stream);
    rs2_stream to_stream_rs = convertStream(to_stream);
    rs2::stream_profile from_stream_profile = _pipe_profile.get_stream(from_stream_rs);
    rs2::stream_profile to_stream_profile = _pipe_profile.get_stream(to_stream_rs);
    Camera::Extrinsics my_extrins;
    try
    {
        rs2_extrinsics extrinsics = from_stream_profile.get_extrinsics_to(to_stream_profile);
        for(int i=0; i<9; ++i){
            my_extrins.rotation[i] = extrinsics.rotation[i];
        }
        for(int i=0; i<3; ++i){
            my_extrins.translation[i] = extrinsics.translation[i];
        }
    }
    catch (const std::exception& e)
    {
        throw IRealSenseMotionExtrinsic();
    }
    return my_extrins;
}

Camera::EulerAngles RealSense::getEulerAngels()
{
    auto time_stamp = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto host_time_stamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_stamp).count();
//    try{
        rs2::frame motion_frame = _frames.first(RS2_STREAM_GYRO,RS2_FORMAT_MOTION_XYZ32F);
        // Cast the frame that arrived to motion frame
        auto motion = motion_frame.as<rs2::motion_frame>();
        /** 3D vector in Euclidean coordinate space */
        rs2_vector gyro_data = motion.get_motion_data();
        Camera::EulerAngles cur_angels = {gyro_data.x, gyro_data.y, gyro_data.z, host_time_stamp_ms,
                                         motion_frame.get_timestamp()};
        _last_euler_angles = cur_angels;
        return cur_angels;

//    }
//    catch (const std::exception& e)
//    {
//       return _last_euler_angles;
//    }

}

Camera::AccelData RealSense::getAccelData()
{
    auto time_stamp = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto host_time_stamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_stamp).count();

    rs2::frame motion_frame = _frames.first(RS2_STREAM_ACCEL,RS2_FORMAT_MOTION_XYZ32F);
    auto motion = motion_frame.as<rs2::motion_frame>();
    rs2_vector accel_data = motion.get_motion_data();
    Camera::AccelData cur_accel_data = {accel_data.x, accel_data.y, accel_data.z, host_time_stamp_ms,
                                       motion_frame.get_timestamp()};
    return cur_accel_data;
}





