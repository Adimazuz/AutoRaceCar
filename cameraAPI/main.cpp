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
    cout << sizeof(unsigned long int) << " " << sizeof(unsigned long long int) <<endl;

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
