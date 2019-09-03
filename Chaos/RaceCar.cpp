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

    _is_bitcraze_connected = false;
    _is_cammera_connected = false;
    _is_motor_control_connected = false;
    _is_tcp_client_connected = false;
    _is_tcp_server_connected = false;
    _image_format_to_remote = RaceCar::format_to_remote::COLOR;
    _flow_data = {};
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
        std::cout << "connected to motor Control" <<std::endl;
    } else {
        std::cout << "motor Control NOT CONNECTED" <<std::endl;
    }

    if(_bitcraze.connect()){
        _is_bitcraze_connected = true;
        std::cout << "connected to Bitcraze" <<std::endl;
    } else {
        std::cout << "bitcraze NOT CONNECTED" <<std::endl;
    }



    _tcp_server->bind(server_ip, SERVER_PORT, MAX_NUM_USERS); //to allow athers to connect
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
            setCamAndJpegConfig();
            std::cout << "Camera setuped" <<std::endl;
            _camera.startCamera();
            std::cout << "Camera started" <<std::endl;
            _camera_thread = std::make_shared<std::thread>(&RaceCar::getCameraOutputAndSendToRemote,this);
    }
    if(_is_motor_control_connected && _tcp_server->isBind()){
            std::cout << "connected to Motor Control" <<std::endl;
            _carcontrol_thread = std::make_shared<std::thread>(&RaceCar::getCarControlCommands,this);

    }
//    _carcontrol_thread = std::make_shared<std::thread>(&RaceCar::doDonuts,this);
    if(_is_bitcraze_connected){
        std::cout << "connected to BitCraze" <<std::endl;
        _bitcraze_thread = std::make_shared<std::thread>(&RaceCar::getBitCrazeOutput,this);
    }
}


void RaceCar::setCamAndJpegConfig()
{
//    _camera.setupColorImage(RealSense::ColorFrameFormat::RGB8,RealSense::ColorRessolution::R_640x480, RealSense::ColorCamFps::F_30hz);
//    _camera.setupDepthImage(RealSense::DepthRessolution::R_640x480, RealSense::DepthCamFps::F_30hz);
    _camera.setupInfraredImage(RealSense::InfrarFrameFormat::Y8, RealSense::InfrarRessolution::R_640x480, RealSense::InfrarCamFps::F_30hz, RealSense::InfrarCamera::LEFT);
    _camera.setupGyro();
    _camera.setupAccel();

//    _jpeg_comp.setParams(640,480,JpegCompressor::Format::RGB,100);
    _jpeg_comp.setParams(640,480,JpegCompressor::Format::GREY_SCALE,100);

//    _image_format_to_remote = RaceCar::format_to_remote::DEPTH;
    _image_format_to_remote = RaceCar::format_to_remote::INFRARED;
//    _image_format_to_remote = RaceCar::format_to_remote::COLOR;
}


RaceCar &RaceCar::parseAndSendCmd(const char cmd)
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

RaceCar &RaceCar::getCarControlCommands()
{
    std::cout << "waiting for connection" << std::endl;


    while (_is_running)
    {
        if(_tcp_server->hasConnectionWithSocket(_socket))
        {
            char cmd = ' ';
            _tcp_server->receive(_socket,&cmd, 1);
            parseAndSendCmd(cmd);

        }

        else
        {
            _socket = _tcp_server->waitForConnections(1);
            std::cout << "wait to asafff" << std::endl;
            if(_socket > 0)
            {
                _tcp_server->setClientUnblocking(_socket,true);
                std::cout << "someone connected: " << std::endl;
            }
        }

    }
    std::cout <<"CarControl thread finished" << std::endl;
    _motor_control->stop();
    return *this;
}

RaceCar &RaceCar::doDonuts()
{
    _motor_control->changeAngle(90);
    _motor_control->changeSpeed(10);
    std::this_thread::sleep_for (std::chrono::milliseconds(200));

    int delta = 2;

    while(true)
    {
        std::this_thread::sleep_for (std::chrono::milliseconds(20));

        //change direction
        _motor_control->changeAngleBy(delta);
        int current_angle = _motor_control->getAngle();
        if(current_angle >= 120 || current_angle <= 60)
        {

            std::this_thread::sleep_for (std::chrono::milliseconds(2000));
            delta *= -1;
        }

    }

    return *this;
}


Chaos::ColorPacket RaceCar::buildColorPacket(const Camera::ColorImage &image){

    Chaos::ColorPacket packet = {};

    packet.accel_data = _camera.getAccelData();
    packet.euler_angl = _camera.getEulerAngels();

    _flow_mtx.lock();
    packet.flow_data = _flow_data;
    _flow_mtx.unlock();

    packet.image.frame_num = image.frame_num;
    packet.image.height = image.height;
    packet.image.width = image.width;
    packet.image.size = image.size;
    packet.image.host_ts_ms = image.host_ts_ms;
    packet.image.camera_ts_ms = image.camera_ts_ms;
    packet.image.bytes_per_pixel = image.bytes_per_pixel;


    _jpeg_comp.compress(image.data); //compress with jpeg!!
    packet.image.compressed_size = _jpeg_comp.getCompressedSize();
    packet.image.compresed_data = _jpeg_comp.getOutput();

    return packet;
}

Chaos::header RaceCar::buildColorHeader(){
    Chaos::header header = {};
    header.type_code = Chaos::COLOR_HEADER;
    header.total_size = sizeof(Chaos::ColorPacket)-sizeof(Chaos::ColorImage::compresed_data);
    return header;
}

Chaos::DepthPacket RaceCar::buildDepthPacket(const Camera::DepthImage &image, std::vector<unsigned char> &compresed_image){
    
    Chaos::DepthPacket packet = {};
    
    packet.accel_data = _camera.getAccelData();
    packet.euler_angl = _camera.getEulerAngels();
    
    _flow_mtx.lock();
    packet.flow_data = _flow_data;
    _flow_mtx.unlock();
    
    packet.image.frame_num = image.frame_num;
    packet.image.height = image.height;
    packet.image.width = image.width;
    packet.image.size = image.size;
    packet.image.host_ts_ms = image.host_ts_ms;
    packet.image.camera_ts_ms = image.camera_ts_ms;
    packet.image.depth_scale = image.depth_scale;
    packet.image.bytes_per_pixel = image.bytes_per_pixel;
    
    auto len = image.size;
    auto len_orig = len;

    compress(compresed_image.data(), &len, image.data, len_orig); //compress with zlib!

    packet.image.compressed_size = len;
    packet.image.compresed_data = compresed_image.data();

    //test to send non compresed data
//    packet.image.compressed_size = image.size;
//    packet.image.compresed_data = nullptr;
    
    return packet;
}

Chaos::header RaceCar::buildDepthHeader(){
    Chaos::header header = {};
    header.type_code = Chaos::DEPTH_HEADER;
    header.total_size = sizeof(Chaos::DepthPacket)-sizeof(Chaos::DepthImage::compresed_data);
    return header;
}


RaceCar &RaceCar::getCameraOutputAndSendToRemote()
{
    std::cout << "enter Camera thread" <<std::endl;
    while (_is_running && _tcp_client->isConnected())
    {
        //        std::cout << _is_running <<std::endl;

        _camera.captureFrame();

        //test for color image
        if (_image_format_to_remote != RaceCar::format_to_remote::DEPTH){
            Camera::ColorImage image;
            if (_image_format_to_remote == RaceCar::format_to_remote::COLOR){
                image = _camera.getColorImage();
            } else {
                image = _camera.getInfraredImage();
            }
            Chaos::ColorPacket packet = buildColorPacket(image);
            Chaos::header header = buildColorHeader();

            _tcp_client->send(reinterpret_cast<char*>(&header), sizeof(header));
            _tcp_client->send(reinterpret_cast<char*>(&packet), header.total_size);
            _tcp_client->send(reinterpret_cast<char*>(packet.image.compresed_data), packet.image.compressed_size);

        } else if (_image_format_to_remote == RaceCar::format_to_remote::DEPTH)
        {
            // if we send depth image we use zlib compressor
            Camera::DepthImage d_image = _camera.getDepthImage();
            std::vector<unsigned char> compresed_image(d_image.size);
            Chaos::DepthPacket d_packet = buildDepthPacket(d_image, compresed_image);
            Chaos::header d_header = buildDepthHeader();

//            std::cout << "sending depth in size: "<< d_packet.image.compressed_size << std::endl;

            _tcp_client->send(reinterpret_cast<char*>(&d_header), sizeof(d_header));
            _tcp_client->send(reinterpret_cast<char*>(&d_packet), d_header.total_size);
            _tcp_client->send(reinterpret_cast<char*>(d_packet.image.compresed_data), d_packet.image.compressed_size);
        }
    }
    std::cout << "Camera thread finished" <<std::endl;
    return *this;
}

RaceCar &RaceCar::getBitCrazeOutput()
{
    std::cout << "enter BitCraze thread" << std::endl;
    _bitcraze.requestFlowData();
    while (_is_running) {
        //TODO reset bitcrze arduino at start!

        Flow flow_data = _bitcraze.getFlowOutput();
//        std::cout << flow_data.deltaX <<"..." << flow_data.deltaY << "..."<<flow_data.range << "..." <<flow_data.dt << std::endl;

        std::lock_guard<std::mutex> lock(_flow_mtx);
        _flow_data = flow_data;
    }
    _bitcraze.stopStream();
    std::cout << "BitCraze thread finished" << std::endl;
}



