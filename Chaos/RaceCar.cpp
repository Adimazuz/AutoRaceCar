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
    _motor_control = std::make_shared<Arduino>();
//    _bitcraze = std::make_shared<Bitcraze>();
    _tcp_client = ITcpClient::create();
    _tcp_server = ITcpServer::create();

    _camera_thread = nullptr;
    _carcontrol_thread = nullptr;
    _bitcraze_thread = nullptr;
    _is_running = true;

}

RaceCar::~RaceCar()
{

    std::cout << "enter diestruction" <<std::endl;
    if (_camera_thread){
        std::cout << "camera destructor" <<std::endl;
         _camera_thread->join();
         std::cout << "camera destruction finished" <<std::endl;
     }
    if (_carcontrol_thread){
        std::cout << "serial destructor" <<std::endl;
        _motor_control->stop();

        _carcontrol_thread->join();
        std::cout << "seial destruction finished" <<std::endl;
     }
    if (_bitcraze_thread){
        std::cout << "bitcraze destructor" <<std::endl;
//        _bitcraze->stop();

        _bitcraze_thread->join();
        std::cout << "bitcraze destruction finished" <<std::endl;

    }
}

RaceCar &RaceCar::connect(const string& ip, const unsigned short& port,const string& server_ip)
{
    std::cout << "enter conect()" <<std::endl;



    if(_camera.connectCamera()){
        _is_cammera_connected = true;
        std::cout << "Camera ON" <<std::endl;
    } else {
        std::cout << "Camera NOT CONNECTED" <<std::endl;
    }

    if ( _camera.isConnect() ){
         std::cout << "try _tcp_client" <<std::endl;
         _tcp_client->connect(ip, port);
         std::cout << "Camera connected" <<std::endl;
    } else {
        std::cout << "Camera NOT CONNECTED" <<std::endl;
    }
    if(_tcp_client->isConnected()){
        _is_tcp_client_connected = true;
        std::cout << "connected to sever" <<std::endl;
    } else {
        std::cout << "server NOT CONNECTED" <<std::endl;
    }

    if(_motor_control->connect()){
        _is_motor_control_connected = true;
        std::cout << "connected to Arduino" <<std::endl;
    } else {
        std::cout << "Arduino NOT CONNECTED" <<std::endl;
    }

    if(_bitcraze.connect()){
        _is_bitcraze_connected = true;
        std::cout << "connected to Bitcraze" <<std::endl;
    } else {
        std::cout << "bitcraze NOT CONNECTED" <<std::endl;
    }



    _tcp_server->bind(server_ip,SERVER_PORT,MAX_NUM_USERS); //to allow athers to connect
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
            _camera.setupColorImage(RealSense::ColorFrameFormat::RGB8,RealSense::ColorRessolution::R_640x480, RealSense::ColorCamFps::F_30hz);
            _camera.setupDepthImage(RealSense::DepthRessolution::R_480x270, RealSense::DepthCamFps::F_30hz);
            std::cout << "Camera setuped" <<std::endl;
            _camera.startCamera();
            std::cout << "Camera started" <<std::endl;
            _camera_thread = std::make_shared<std::thread>(&RaceCar::getCameraOutput,this);
    }
    if(_is_motor_control_connected && _tcp_server->isBind()){
            std::cout << "connected to Motor Control" <<std::endl;
            _carcontrol_thread = std::make_shared<std::thread>(&RaceCar::arduinoCommunications,this);
    }
    if(_is_bitcraze_connected){
        std::cout << "connected to BitCraze" <<std::endl;
        _bitcraze_thread = std::make_shared<std::thread>(&RaceCar::getBitCrazeOutput,this);

    }
}


RaceCar &RaceCar::parseCmdString(const char cmd)
{

    switch (cmd) {

    case 's': {
        _motor_control->stop();
        break;
    }
    case 'u': {
        _motor_control->changeSpeedBy(1);
        break;
    }
    case 'd': {
        _motor_control->changeSpeedBy(-1);
        break;
    }
    case 'l': {
        _motor_control->changeAngleBy(-2);
        break;
    }
    case 'r': {
        _motor_control->changeAngleBy(2);
        break;
    }
    case 'q': {
        _is_running=false;
        break;
    }
//    default: _motor_control->stop();
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
            _tcp_server->receive(_socket,&cmd, 1);
            parseCmdString(cmd);
//            std::cout << cmd << std::endl;

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
    std::cout <<"CarControl thread finished" << std::endl;
    _motor_control->stop();
    return *this;
}

RaceCar &RaceCar::getCameraOutput()
{
    std::cout << "enter Camera thread" <<std::endl;
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
    std::cout << "Camera thread finished" <<std::endl;
    return *this;
}

RaceCar &RaceCar::getBitCrazeOutput()
{
    std::cout << "enter BitCraze thread" << std::endl;
    _bitcraze.requestFlowData();
    while (_is_running) {
        Flow flow_data = _bitcraze.getFlowOutput(); //TODO send flow to asaf
//        std::cout << flow_data.deltaX <<"..." << flow_data.deltaY << "..."<<flow_data.range << "..." <<flow_data.mili_sec << std::endl;


    }
    std::cout << "BitCraze thread finished" << std::endl;
}

//RaceCar  &RaceCar::sendFlowOutput(Flow data)
//{
//    char* ptr = (char*) &data;
//    _tcp_server->send(_socket,ptr,sizeof(Flow));
//}
//static void splitString(const string &str, std::vector<string> &output)
//{
//    string::size_type start = 0; // Where to start
//    string::size_type last = str.find_first_of(" "); // Finds the first space

//    // npos means that the find_first_of wasn't able to find what it was looking for
//    // in this case it means it couldn't find another space so we are at the end of the
//    // words in the string.
//    while (last != string::npos)
//    {
//        // If last is greater then start we have a word ready
//        if (last > start)
//        {
//            output.push_back(str.substr(start, last - start)); // Puts the word into a vector look into how the method substr() works
//        }

//        start = ++last; // Reset start to the first character of the next word
//        last = str.find_first_of(" ", last); // This means find the first space and we start searching at the first character of the next word
//    }

//    // This will pickup the last word in the file since it won't be added to the vector inside our loop
//    output.push_back(str.substr(start));
//}


