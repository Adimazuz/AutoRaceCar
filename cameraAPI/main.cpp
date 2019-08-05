#include <iostream>
#include <librealsense2/rs.hpp>
#include <fstream>
//#include "Camera_types.h"

using namespace std;

#include "RealSenseAPI.h"
int main()
{
    cout << "Hello World!" << endl;
    RealSense camera;
    camera.connectCamera();
    cout << "camera connected" << endl;
    camera.setupDepthImage(RealSense::DepthRessolution::R_640x480,RealSense::DepthCamFps::F_15hz);
    camera.setupColorImage(RealSense::ColorFrameFormat::RGB8,RealSense::ColorRessolution::R_424x240,RealSense::ColorCamFps::F_15hz);

    cout << "framesetuped" << endl;
    camera.startCamera();
//    std::fstream out("depth_image",std::ios::out | std::ios::binary);
//    camera._stereo_module.get_option(RS2_OPTION_DEPTH_UNITS);
    std::cout << sizeof(Camera::real32)  <<std::endl;

    Camera::Intrinsics d_intr = camera.getDepthCamIntrinsics();

    std::cout << d_intr.ppx << ", " << d_intr.ppy << std::endl;
    std::cout << d_intr.fx << ", " << d_intr.fy << std::endl;

    Camera::Extrinsics color_to_depth_extr = camera.getExtrinsics(RealSense::Stream::COLOR,RealSense::Stream::DEPTH);
    std::cout << "Translation Vector : [" << color_to_depth_extr.translation[0] << "," << color_to_depth_extr.translation[1] << "," << color_to_depth_extr.translation[2] << "]\n";
    std::cout << "Rotation Matrix    : [" << color_to_depth_extr.rotation[0] << "," << color_to_depth_extr.rotation[3] << "," << color_to_depth_extr.rotation[6] << "]\n";
    std::cout << "                   : [" << color_to_depth_extr.rotation[1] << "," << color_to_depth_extr.rotation[4] << "," << color_to_depth_extr.rotation[7] << "]\n";
    std::cout << "                   : [" << color_to_depth_extr.rotation[2] << "," << color_to_depth_extr.rotation[5] << "," << color_to_depth_extr.rotation[8] << "]" << std::endl;

    Camera::Extrinsics depth_to_color_extr = camera.getExtrinsics(RealSense::Stream::DEPTH,RealSense::Stream::COLOR);
    std::cout << "Translation Vector : [" << depth_to_color_extr.translation[0] << "," << depth_to_color_extr.translation[1] << "," << depth_to_color_extr.translation[2] << "]\n";
    std::cout << "Rotation Matrix    : [" << depth_to_color_extr.rotation[0] << "," << depth_to_color_extr.rotation[3] << "," << depth_to_color_extr.rotation[6] << "]\n";
    std::cout << "                   : [" << depth_to_color_extr.rotation[1] << "," << depth_to_color_extr.rotation[4] << "," << depth_to_color_extr.rotation[7] << "]\n";
    std::cout << "                   : [" << depth_to_color_extr.rotation[2] << "," << depth_to_color_extr.rotation[5] << "," << depth_to_color_extr.rotation[8] << "]" << std::endl;



//    while (1){
//        camera.captureFrame();
//        Camera::ColorImage color_test = camera.getColorImage();
//        Camera::DepthImage depth_test = camera.getDepthImage();

//        const unsigned char *d = depth_test.data;
//        const unsigned char *c = depth_test.data;

////        out.write(reinterpret_cast<const char*>(d),depth_test.getSize());

//        float dist_fix = camera.get_depth_units() ;
//        std::cout << "from option: " <<  dist_fix << std::endl;
//    }


    return 0;



}
