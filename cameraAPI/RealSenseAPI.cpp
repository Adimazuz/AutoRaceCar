#include "RealSenseAPI.h"

#define NUM_OF_RS_SENSORS 3


Status RealSense::connectCamera(){

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

   _sensor1 = sensors[0]; //TODO CHANGE SENSORS NAMEs
   _sensor2 = sensors[1];
   _sensor3 = sensors[2];

   return SUCCESS;
}

Image RealSense::getInfraredImage(RealSense::rs2_frame_format format, RealSense::rs2_ressolution_and_fps ress_fps_set)
{
    std::vector<rs2::stream_profile> stream_profiles = _sensor1.get_stream_profiles();

    //TODO figure out what profile was choosen via ress_fps_set&format
    int choosen_index=0;
    rs2::stream_profile chosen_profile = stream_profiles[choosen_index];
    // Open can be called with a single profile, or with a collection of profiles
    // Calling open() tries to get exclusive access to the sensor.
    // Opening a sensor may have side effects such as actually
    //  running, consume power, produce data, etc.
    _sensor1.open(chosen_profile);


}

