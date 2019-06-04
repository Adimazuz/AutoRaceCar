#ifndef REALSENSEAPI_H
#define REALSENSEAPI_H

#include <librealsense2/rs.hpp>

enum Status {
    SUCCESS,
    CAMERA_NOT_CONNECTED,
    ONE_OF_THE_SENSORS_FAIL
};


class RealSense{

public:
        enum sensor_name //TODO update names
        {
            SENSOR1,
            SENSOR2,
            SENSOR3
        };


       RealSense();



       /**
        * @brief connectCamera - assumes that only 1 cammera connected to the divice
        * the function detect the cammera initilize the sensors of the camera
        * @return
        */
       Status connectCamera();

       /**TODO functions to:
        * get_depth_units :             //A Depth stream contains an image that is composed of pixels with depth information.
        //The value of each pixel is the distance from the camera, in some distance units.
        //To get the distance in units of meters, each pixel's value should be multiplied by the sensor's depth scale
        //Here is the way to grab this scale value for a "depth" sensor:
        *
        * get_field_of_view:
        *         // A sensor's stream (rs2::stream_profile) is in general a stream of data with no specific type.
        // For video streams (streams of images), the sensor that produces the data has a lens and thus has properties such
        //  as a focal point, distortion, and principal point.
        // To get these intrinsics parameters, we need to take a stream and first check if it is a video stream

        get_extrinsics:
        // If the device/sensor that you are using contains more than a single stream, and it was calibrated
        // then the SDK provides a way of getting the transformation between any two streams (if such exists)

       */


private:
      rs2::device m_camera;
      rs2::sensor m_sensor1; //TODO change name of the sensors
      rs2::sensor m_sensor1;
      rs2::sensor m_sensor1;


}

#endif // REALSENSEAPI_H
