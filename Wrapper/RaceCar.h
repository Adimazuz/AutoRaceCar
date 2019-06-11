#pragma once
#include "../motorAPI/MotorController.h"
#include "../motorAPI/Arduino.h"
#include "../cameraAPI/RealSenseAPI.h"
#include "../TcpClient/ITcpClient.h"


class RaceCar {
public:
	RaceCar &connect(const string& ip, const unsigned short& port);
	RaceCar &run();
	RaceCar() ;
private:
	std::shared_ptr<MotorController> _arduino;
	RealSense _camera;
	std::shared_ptr<ITcpClient> _tcp_client;


    RaceCar &parseCmdString(const std::vector<char>& cmd);
};
