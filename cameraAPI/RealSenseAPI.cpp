#include "RealSenseAPI.h"

#define NUM_OF_RS_SENSORS 3

static void convertFPStoInt(RealSense::rs2fps fps, int& f_int){
    if(fps == RealSense::rs2fps::F_60hz){
        f_int = 60;
    }else if(fps == RealSense::rs2fps::F_30hz){
        f_int = 30;
    }else if(fps == RealSense::rs2fps::F_15hz){
        f_int = 15;
    }else if(fps == RealSense::rs2fps::F_6hz){
        f_int = 6;
    }
}

static void convertRessToInt(RealSense::rs2ColorRessolution ressolution, int& w, int& h){
    if(ressolution == RealSense::rs2ColorRessolution::R_1920x1080){
        w = 1920;
        h = 1080;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_1280x720){
        w = 1280;
        h = 720;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_960_540){
        w = 960;
        h = 540;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_848_480){
        w = 848;
        h = 480;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_640x480){
        w = 640;
        h = 480;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_640x360){
        w = 640;
        h = 480;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_424x240){
        w = 424;
        h = 240;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_320x240){
        w = 320;
        h = 240;
    }else if(ressolution == RealSense::rs2ColorRessolution::R_320x180){
        w = 320;
        h = 180;
    }

}


Status RealSense::connectCamera(){

    //TODO cheak if must
    // rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);

    rs2::context ctx;
    rs2::device_list devices = ctx.query_devices();
    if (devices.size() == 0){
        return CAMERA_NOT_CONNECTED;

    }
    _camera = devices[0];
    std::vector<rs2::sensor> sensors = devices[0].query_sensors();
    if (sensors.size() < NUM_OF_RS_SENSORS){
        return ONE_OF_THE_SENSORS_FAIL;
    }

   _stereo_module = sensors[0];
   _rgb_camera = sensors[1];
   _motion_module = sensors[2];

   return SUCCESS;
}







Status RealSense::setupColorImage(/*rs2_format format,*/ RealSense::rs2ColorRessolution ressolution, RealSense::rs2fps fps)
{

    if(((ressolution == rs2ColorRessolution::R_1920x1080 || ressolution == rs2ColorRessolution::R_1280x720) && fps == rs2fps::F_60hz) ||
            (ressolution ==rs2ColorRessolution::R_320x180 || ressolution ==rs2ColorRessolution::R_320x240) && fps == rs2fps::F_15hz ){
        return RESS_NOT_FITTING_WITH_FPS;
    }
    int w,h,freq;
    convertRessToInt(ressolution, w, h);
    convertFPStoInt(fps,freq);
    _config.enable_stream(RS2_STREAM_COLOR,w,h, RS2_FORMAT_RGB8, freq);
    return SUCCESS;
}


void RealSense::startCamera()
{
    _pipe.start(_config);
}



void RealSense::captureFrame()
{
    _frames = _pipe.wait_for_frames();
}

Image RealSense::getColorImage()
{
    rs2::video_frame color_frame = _frames.get_color_frame();


    Image cur_image(reinterpret_cast<const unsigned char*>(color_frame.get_data()),color_frame.get_width(),color_frame.get_height(),
                    color_frame.get_frame_number(), color_frame.get_timestamp(), color_frame.get_bytes_per_pixel());


    return cur_image;
}



