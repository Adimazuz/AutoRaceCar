#pragma once

#include <thread>
#include <mutex>

#include "MotorController.h"
#include "RaceCar.h"
#include "ITcpClient.h"
#include "ITcpServer.h"
#include "RealSenseAPI.h"
#include "bitcraze_types.h"
#include "JpegCompressor.h"
#include "bitcraze.h"
#include "Chaos_types.h"



class RaceCar {
public:
    enum class format_to_remote
    {
        COLOR,
        INFRARED,
        DEPTH
    };


    /**
     * constructor - init. all the classes
     */
    RaceCar();
    
    /**
     * destructor - wait till all threads will be closed
     */
    ~RaceCar();
    
    
    /** connect all the sensors - open needed sockets, setup serials, connect camera, bind this pc (to allow remote
     * user to connect).
     *
     * @param client_ip - ip of remote user for open
     * @param client_port - port of rempotr user (with ip and port we open socket to remote user and via that socket
     * we will send packets of camera and bitcraze)
     * @param server_ip - local pc ip to setup bind
     * @return - none
     */
    RaceCar &connect(const string& client_ip, const unsigned short& client_port,const string& server_ip);
    
    /** this function checks witch sensor connected and for connected sensor lunch a
     * new thread that will procces output data from that sensor
     * ( when all the sensors connected this function open 3 threads:
     * 1. for camera outputs - that get images (according setups inside  _camera.setup***Image)
     * and build packet with compressed image, accel data , gyro data and bitcraze data then
     * send that packet via socket to remote user.
     * 2. for control commands from remote control - wait till remote user will connect and then got commands from him
     * via socket, thus commands transferred via serial connection to (Nano_)Arduino.
     * 3. for bitcraze - got raw data from the sensor (bitcraze) that connected to Arduino, transferred via Serial to
     * that pc.
     * @return - none
     */
    RaceCar &run();



    /**
     * stops the Chaos on user demand
     */
    bool _is_running;

private: // methods

    /**
     * @brief setCamAndJpegConfig
     * setup camera ressolution and fps
     * setup jpeg compressor for same ressolution as from camera
     * Note** that u can setup different frames to get from camera
     * and procces them but in this example we send only one type of frame
     * to remote
     */
    void setCamAndJpegConfig();
    /**
     *  build packet to remote user
     * data compressed with JPEG!
     *
     * @param image - the color frame the we got from camera
     * @return color packet that rdy to be send, with all relevant data (Image description data, accel data, gyro data,
     * flow (bitcraze) data and compressed image data)
     */
    Chaos::ColorPacket buildColorPacket(const Camera::ColorImage &image);
    
    /**
     * build Color header that need to send before the Color Packer (remote user need to know witch
     * data and the length of packet to expect)
     * Note - the length will be different between same type of packets because of the compress.
     * @return return header to Color Packet
     */
    Chaos::header buildColorHeader();
    

    /**
     * @brief buildDepthPacket
     * build packet to remote user
     * data compressed with Z-LIB!
     * @param image - the depth frame the we got from camera
     * @param compresed_image - vector in size of orig depth image
     * @return depth packet that rdy to be send, with all relevant data (Image description data, accel data, gyro data,
    * flow (bitcraze) data and compressed image data)
     */
    Chaos::DepthPacket buildDepthPacket(const Camera::DepthImage &image, std::vector<unsigned char> &compresed_image);

    Chaos::DepthPacket buildDepthPacket_v2(const Camera::DepthImage &image);
    
    /**
    * build Depth header that need to send before the Depth Packer (remote user need to know witch
    * data and the length of packet to expect)
    * Note - the length will be different between same type of packets because of the compress.
    * @return return header to Color Packet
    */
    Chaos::header buildDepthHeader();
    
    /**
     * this function get the control command that the remote user send parse and addapt to
     * motor/servo of the car and transfer relevant command to (Nano_)Arduino
     * @param cmd
     * @return  - none
     */
    RaceCar &parseAndSendCmd(const char cmd);
    
    /**
     * this function will be run on separate thread.
     * the function run as long as the user didnt stop the program.
     * first its wait tll the remote user will connect via socket and then
     * took and process drive commands from remote user.
     * @return - none
     */
    RaceCar &getCarControlCommands();
    
    /**
     * this function will be run on separate thread.
     * the function run as long as the user didnt stop the program and we connected to remote user via socket.
     * first get data from camera and build packet to send to remote user (with compressed data)
     * build needed header and then send to remote user.
     * @return - none
     */
    RaceCar &getCameraOutputAndSendToRemote();
    
    /**
     * this function will be run on separate thread.
     * the function run as long as the user didnt stop the program.
     * at the start tell Arduino that control bitcraze to start send data
     * and then just always receive the data and save the flow_data aside
     * (the thread the send data to remote will read that data, Note: need use mutex because of
     * shared data).
     * @return - none
     */
    RaceCar &getBitCrazeOutput();

    /**
     * makes the car do circles
     * @return pointer to class
     */
    RaceCar &doDonuts();

    /**
     * @brief setColorToSend
     * @return
     */
    RaceCar &setColorToSend();

    /**
     * @brief setIRToSend
     * @return
     */
    RaceCar &setIRToSend();

    /**
     * @brief setDepthToSend
     * @return
     */
    RaceCar &setDepthToSend();


private: //members
    std::shared_ptr<MotorController> _motor_control;
    Bitcraze _bitcraze;
    RealSense _camera;
    std::shared_ptr<ITcpClient> _tcp_client;
    Flow _flow_data;
    std::mutex _flow_mtx;

    std::shared_ptr<ITcpServer> _tcp_server;
    std::shared_ptr<std::thread> _camera_thread;
    std::shared_ptr<std::thread> _carcontrol_thread;
    std::shared_ptr<std::thread> _bitcraze_thread;
    Socket _socket;

    bool _is_tcp_client_connected;
    bool _is_cammera_connected;
    bool _is_motor_control_connected;
    bool _is_tcp_server_connected;
    bool _is_bitcraze_connected;

    RaceCar::format_to_remote _image_format_to_remote;

    JpegCompressor _jpeg_comp;
	


};
