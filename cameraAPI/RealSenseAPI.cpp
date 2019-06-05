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
    if (sensors.size < NUM_OF_RS_SENSORS){
        return ONE_OF_THE_SENSORS_FAIL;
    }

   _sensor1 = sensors[0]; //TODO CHANGE SENSORS NAMEs
   _sensor2 = sensors[1];
   _sensor3 = sensors[2];

   return SUCCESS;
}

