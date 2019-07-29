#include <iostream>
#include <librealsense2/rs.hpp>
#include <fstream>
#include "Data_types.h"

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
    while (1){
        camera.captureFrame();
        Image color_test = camera.getColorImage();
        Image depth_test = camera.getDepthImage();

        const unsigned char *d = depth_test.getData();
        const unsigned char *c = depth_test.getData();

//        out.write(reinterpret_cast<const char*>(d),depth_test.getSize());

        float dist_fix = camera.get_depth_units() ;
        std::cout << "from option: " <<  dist_fix << std::endl;
    }


    return 0;



}
