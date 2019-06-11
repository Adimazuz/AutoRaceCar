#pragma once

#include <thread>

#include "MotorController.h"
#include "RaceCar.h"
#include "ITcpClient.h"
#include "ITcpServer.h"
#include "RealSenseAPI.h"


class RaceCar {
public:
    RaceCar &connect(const string& ip, const unsigned short& port,const string& server_ip);
	RaceCar &run();
    RaceCar();
    ~RaceCar();

    bool _is_running;

private:
	std::shared_ptr<MotorController> _arduino;
    RealSense _camera;
	std::shared_ptr<ITcpClient> _tcp_client;
    std::shared_ptr<ITcpServer> _tcp_server;
    RaceCar &parseCmdString(const std::vector<char>& cmd);
    RaceCar &getDriveCmd();
    RaceCar &getCameraInput();
    std::shared_ptr<std::thread> _camera_thread;
    std::shared_ptr<std::thread> _serial_thread;
    Socket _socket;
};
