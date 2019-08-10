#include <iostream>
#include <string>

//#include "ITcpClient.h"
#include "librealsense2/rs.hpp"

#include "RaceCar.h"
int main() {

//    rs2::context ctx;
//    rs2::device_list devices = ctx.query_devices();
//    rs2::pipeline _pipe;
//    rs2::config _config;

//    _config.enable_stream(RS2_STREAM_COLOR,640,480,RS2_FORMAT_RGB8,30);
//    _config.enable_stream(RS2_STREAM_DEPTH,480,270,RS2_FORMAT_Z16,30);

//    _pipe.start(_config);

//    while(1){
//        rs2::frameset _frames = _pipe.wait_for_frames();
//        rs2::video_frame color_frame = _frames.get_color_frame();
//        std::cout << color_frame.get_height() << std::endl;
//        color_frame.get_data();

//    }




    RaceCar car;
    car.connect("132.68.36.50",5555,"132.68.36.45");
    car.run();

    std::cout << " ok" << std::endl;


    std::thread thread([&car]()
    {
        while(true)
        {
            char ch;
            std::cin >> ch;
            if(ch == 'q')
            {
                car._is_running = false;
                break;
            }
        }
    });

    thread.join();
    return 0;
}
