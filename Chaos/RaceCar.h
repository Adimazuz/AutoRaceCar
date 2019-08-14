#pragma once

#include <thread>

#include "MotorController.h"
#include "RaceCar.h"
#include "ITcpClient.h"
#include "ITcpServer.h"
#include "RealSenseAPI.h"
#include "Arduino_types.h"
#include "JpegCompressor.h"


class RaceCar {
public:
    RaceCar &connect(const string& client_ip, const unsigned short& client_port,const string& server_ip);
	RaceCar &run();
    RaceCar();
    ~RaceCar();

    bool _is_running;



private:
	std::shared_ptr<MotorController> _arduino;
    RealSense _camera;
	std::shared_ptr<ITcpClient> _tcp_client;

    std::shared_ptr<ITcpServer> _tcp_server;
    std::shared_ptr<std::thread> _camera_thread;
    std::shared_ptr<std::thread> _serial_thread;
    Socket _socket;

    bool _is_tcp_client_connected;
    bool _is_cammera_connected;
    bool _is_arduino_connected;
    bool _is_tcp_server_connected;
    bool _is_bitcraze_connected;

    JpegCompressor _jpeg_comp;
	
    RaceCar &parseCmdString(const string &cmd);
    RaceCar &arduinoCommunications();
    RaceCar &getCameraOutput();
    RaceCar &sendFlowOutput();

};
