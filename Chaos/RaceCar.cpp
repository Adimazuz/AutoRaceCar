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
    _tcp_server = ITcpServer::create();

    _camera_thread = nullptr;
    _serial_thread = nullptr;
    _is_running = true;
    _is_bitcraze_connected = true;

}

RaceCar::~RaceCar()
{

    std::cout << "enter distruction" <<std::endl;
    if (_camera_thread){
        std::cout << "camera distructor" <<std::endl;
         _camera_thread->join();
         std::cout << "camera finished" <<std::endl;
     }
    if (_serial_thread){
        std::cout << "serial distructor" <<std::endl;
        _arduino->stop();

        _serial_thread->join();
        std::cout << "seial finished" <<std::endl;
     }
}

RaceCar &RaceCar::connect(const string& ip, const unsigned short& port,const string& server_ip)
{
    std::cout << "enter conect()" <<std::endl;



    if(_camera.connectCamera()){
        _is_cammera_connected = true;
        std::cout << "camera on" <<std::endl;
    } else {
        std::cout << "camera NOT CONNECTED" <<std::endl;
    }

    if ( _camera.isConnect() ){
         std::cout << "try _tcp_client" <<std::endl;
         _tcp_client->connect(ip, port);
         std::cout << "camera connected" <<std::endl;
    } else {
        std::cout << "camera NOT CONNECTED" <<std::endl;
    }
    if(_tcp_client->isConnected()){
        _is_tcp_client_connected = true;
        std::cout << "connected to sever" <<std::endl;
    } else {
        std::cout << "server NOT CONNECTED" <<std::endl;
    }

    if(_arduino->connect()){
        _is_arduino_connected = true;
        std::cout << "connected to Arduino" <<std::endl;
    } else {
        std::cout << "Arduino NOT CONNECTED" <<std::endl;
    }

    _tcp_server->bind(server_ip,SERVER_PORT,MAX_NUM_USERS);
    if(_tcp_server->isBind()){
        std::cout << "bind success" << std::endl;
        _tcp_server->setUnblocking(true);
        _is_tcp_server_connected = true;
    } else {
        std::cout << "bind FAILED" <<std::endl;
    }

    std::cout << "end connections" <<std::endl;
    return *this;

}

RaceCar &RaceCar::run()
{
    std::cout << "enter run" <<std::endl;
    if(_is_tcp_client_connected && _is_cammera_connected){
             std::cout << "camera before setuped" <<std::endl;
            _camera.setupColorImage(RealSense::ColorFrameFormat::RGB8,RealSense::ColorRessolution::R_640x480, RealSense::ColorCamFps::F_30hz);
            _camera.setupDepthImage(RealSense::DepthRessolution::R_480x270, RealSense::DepthCamFps::F_30hz);
            std::cout << "camera setuped" <<std::endl;
            _camera.startCamera();
            std::cout << "camera started" <<std::endl;
            _camera_thread = std::make_shared<std::thread>(&RaceCar::getCameraOutput,this);
            std::cout << "camera thread opened" <<std::endl;
    }
    if(_is_arduino_connected){
             std::cout << "connected to Arduino" <<std::endl;

           _serial_thread = std::make_shared<std::thread>(&RaceCar::arduinoCommunications,this);
    }
}


RaceCar &RaceCar::parseCmdString(const char cmd)
{
//    std::cout << "cmd " << cmd[0]<< std::endl;
    switch (cmd) {

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
    case '#': {
        //TODO add function
        //TODO return to private
        break;
    }
    default: _arduino->stop();
	}

}

RaceCar &RaceCar::arduinoCommunications()
{
    //TODO in case of crash, arduino should stop itself
    //TODO avoid terminate from write
    //TODO ardoino functions for "#"
    std::cout << "waiting for connection" << std::endl;


    while (_is_running)
    {
        if(_tcp_server->hasConnectionWithSocket(_socket))
        {
            char cmd = ' ';
            Flow data;
            _tcp_server->receive(_socket,&cmd, 1);
            if(cmd == ' ' && _is_bitcraze_connected)
            {
                data =_arduino->getFlowOutput();
                if (!data.range){ // check if bitcraze connected
                    _is_bitcraze_connected = false;
                    std::cout << "bitcraze DISCONNECTED" << std::endl;
                } else {
                    _is_bitcraze_connected = true;
                    std::cout << data.deltaX <<"..."<< data.deltaY << "..." << data.range <<"..." << data.mili_sec <<std::endl;
                }
            }else {
                parseCmdString(cmd);
            }
        }

        else
        {
            _socket = _tcp_server->waitForConnections(1);
            std::cout << "wait to asafff" << std::endl;
            if(_socket > 0)
            {
                _tcp_server->setClientUnblocking(_socket,true);
                std::cout << "someone connected" << std::endl;
            }
        }

    }
    std::cout <<" exit from arduino looop "<< _is_running << std::endl;
    _arduino->stop();
    return *this;
}

RaceCar &RaceCar::getCameraOutput()
{
    std::cout << "from camera thread " <<std::endl;
    while (_is_running && _tcp_client->isConnected())
    {
//        std::cout << _is_running <<std::endl;
        _camera.captureFrame();
        Camera::ColorImage image=_camera.getColorImage();
//        Camera::DepthImage depth_image = _camera.getDepthImage();

        auto len = image.size;
//        auto depth_len = depth_image.size;

//        std::cout << "image len:"<< len <<std::endl;

//        std::cout << "image len:"<< depth_len <<std::endl;
//        std::cout << depth_image.depth_scale  <<std::endl;

        //compresed send test
//        auto len_orig=len;
//        std::vector<unsigned char> compresed_image(len);
//        compress(compresed_image.data(),&len,image.data,len_orig);
        //std::cout << "org len: "<< len_orig <<" compresed len:"<< len <<std::endl;

        //color send test
//        std::cout << "send data " << _tcp_client->isConnected() << std::endl;
//        _jpeg_comp.compress(image.data);
        auto compressed_size = _jpeg_comp.getCompressedSize();
//        std::cout << "origin size: " << len << " but wait, the commpressed size is: " << compressed_size << std::endl;
        _tcp_client->send(reinterpret_cast<char*>(&image),sizeof(image)-sizeof(image.data));
        //std::cout << "sent len" <<std::endl;
        _tcp_client->send(reinterpret_cast<const char*>(image.data),len);
//        std::cout << "finished send data" << _tcp_client->isConnected() << std::endl;

//        //depth send test
//        _tcp_client->send(reinterpret_cast<char*>(&depth_image),sizeof(depth_image)-sizeof(depth_image.data));
//        //std::cout << "sent len" <<std::endl;
//        _tcp_client->send(reinterpret_cast<const char*>(depth_image.data),depth_len);






    }
    std::cout << "end camera thread" <<std::endl;
    return *this;
}

RaceCar  &RaceCar::sendFlowOutput(Flow data)
{
    char* ptr = (char*) &data;
    _tcp_server->send(_socket,ptr,sizeof(Flow));
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


