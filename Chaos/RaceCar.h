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
    RaceCar &connect(const string& client_ip, const unsigned short& client_port,const string& server_ip);
    RaceCar &run();
    RaceCar();
    ~RaceCar();


    bool _is_running;

private: // methods
    Chaos::ColorPacket buildColorPacket(const Camera::ColorImage &image);
    Chaos::header buildColorHeader();
    RaceCar &parseCmdString(const char cmd);
    RaceCar &arduinoCommunications();
    RaceCar &getCameraOutput();
//    RaceCar &sendFlowOutput(Flow data);
    RaceCar &getBitCrazeOutput();

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

    JpegCompressor _jpeg_comp;
	


};
