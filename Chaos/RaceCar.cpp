#include "RaceCar.h"
#include <vector>
#include "Arduino.h"
#include <thread>
#include "zlib.h"

#include "iostream"

//#define DEBUG_MODE
#define SERVER_PORT 5556
#define MAX_NUM_USERS 5
RaceCar::RaceCar()
{
	_arduino = std::make_shared<Arduino>();
    _tcp_client = ITcpClient::create();
    _camera_thread = nullptr;
    _serial_thread = nullptr;
    _is_running = true;

}

RaceCar::~RaceCar()
{
    if (!_camera_thread){
         _camera_thread->join();
     }
    if (!_serial_thread){
         _serial_thread->join();
     }
}

RaceCar &RaceCar::connect(const string& ip, const unsigned short& port,const string& server_ip)
{
    std::cout << "enter conect()" <<std::endl;
    _tcp_client->connect(ip, port);
    if(_tcp_client->isConnected()){
        _is_tcp_client_connected = true;
        std::cout << "connected to sever" <<std::endl;
    }
    if(_camera.connectCamera()){
        _is_cammera_connected = true;
        std::cout << "camera on" <<std::endl;
    }

    if(_arduino->connect()){
        _is_arduino_connected = true;
        std::cout << "connected to Arduino" <<std::endl;
    }
    return *this;
}

RaceCar &RaceCar::run()
{
    if(_is_tcp_client_connected && _is_cammera_connected){
            _camera.setupColorImage(RealSense::ColorFrameFormat::RGB8,RealSense::ColorRessolution::R_320x180, RealSense::ColorCamFps::F_6hz);
            _camera.setupDepthImage(RealSense::DepthRessolution::R_480x270, RealSense::DepthCamFps::F_6hz);
            std::cout << "camera setuped" <<std::endl;
            _camera.startCamera();
            std::cout << "camera started" <<std::endl;
            _camera_thread = std::make_shared<std::thread>(&RaceCar::getCameraInput,this);
            std::cout << "camera thread opened" <<std::endl;
    }
//    if(_is_arduino_connected){
//             std::cout << "connected to Arduino" <<std::endl;
//            _tcp_server = ITcpServer::create(server_ip,SERVER_PORT,MAX_NUM_USERS);
//            std::cout << "waiting for connection" << std::endl;
//            _socket = _tcp_server->waitForConnections();
//            std::cout << "someone connected" << std::endl;
//           _serial_thread = std::make_shared<std::thread>(&RaceCar::getDriveCmd,this);
//    }


}


RaceCar &RaceCar::parseCmdString(const std::vector<char>& cmd)
{
    if (cmd.size() < 1)
	{
        return *this;
	}


	switch (cmd[0]) {
#ifdef DEBUG_MODE
        std::cout << "cmd " <<cmd[0]<< std::endl;
#endif

	case 's': {
        _arduino->stop();
		break;
	}
	case 'u': {
        _arduino->changeSpeedBy(1);
        break;
	}
	case 'd': {
        _arduino->changeSpeedBy(-1);
		break;
	}
	case 'l': {
        _arduino->changeAngleBy(-2);
		break;
	}
	case 'r': {
        _arduino->changeAngleBy(2);
		break;
	}
    case 'q': {
        _is_running=false;
        break;
    }
	default: _arduino->driveCurrentState();
	}

}

RaceCar &RaceCar::getDriveCmd()
{
    while (_is_running)
    {
        std::vector<char> cmd = _tcp_server->receive(_socket, 1);
        parseCmdString(cmd);
    }
    return *this;

}

RaceCar &RaceCar::getCameraInput()
{
    std::cout << "from camera thread " <<std::endl;
    while (_is_running)
    {
//        std::cout << _is_running <<std::endl;
        _camera.captureFrame();
        Camera::ColorImage image=_camera.getColorImage();
        Camera::DepthImage depth_image = _camera.getDepthImage();

        auto len = image.size;
        auto depth_len = depth_image.size;

        std::cout << "image len:"<< depth_len <<std::endl;
        std::cout << depth_image.depth_scale  <<std::endl;
//        auto len_orig=len;
//        std::vector<unsigned char> compresed_image(len);
//        compress(compresed_image.data(),&len,image.data,len_orig);
        //std::cout << "org len: "<< len_orig <<" compresed len:"<< len <<std::endl;

        _tcp_client->send(reinterpret_cast<char*>(&depth_image),sizeof(depth_image)-sizeof(depth_image.data));
        //std::cout << "sent len" <<std::endl;
        _tcp_client->send(reinterpret_cast<const char*>(depth_image.data),depth_len);

        //std::cout << _is_running <<std::endl;
    }
    return *this;

}

static void splitString(const string &str, std::vector<string> &output)
{
	string::size_type start = 0; // Where to start
	string::size_type last = str.find_first_of(" "); // Finds the first space

	// npos means that the find_first_of wasn't able to find what it was looking for
	// in this case it means it couldn't find another space so we are at the end of the
	// words in the string.
	while (last != string::npos)
	{
		// If last is greater then start we have a word ready
		if (last > start)
		{
			output.push_back(str.substr(start, last - start)); // Puts the word into a vector look into how the method substr() works
		}

		start = ++last; // Reset start to the first character of the next word
		last = str.find_first_of(" ", last); // This means find the first space and we start searching at the first character of the next word
	}

	// This will pickup the last word in the file since it won't be added to the vector inside our loop
	output.push_back(str.substr(start));
}


