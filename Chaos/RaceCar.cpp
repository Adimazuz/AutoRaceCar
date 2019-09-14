#include <thread>
#include <vector>

#include "RaceCar.h"
#include "Arduino.h"
#include "iostream"


#define SERVER_PORT 5556
#define MAX_NUM_USERS 5

#define COLOR_WIDTH 640
#define COLOR_HEIGHT 480

#define IR_WIDTH 640
#define IR_HEIGHT 480

#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480

#define WAIT_AFTER_BC_FLUSH 3000



RaceCar::RaceCar()
{
    _motor_control = std::make_shared<Arduino>();
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
        _bitcraze.stopStream();
        _bitcraze.flush();
        std::this_thread::sleep_for (std::chrono::milliseconds(WAIT_AFTER_BC_FLUSH));
        std::cout << "connected to Bitcraze" <<std::endl;
    } else {
        std::cout << "bitcraze NOT CONNECTED" <<std::endl;
    }


    //to allow others to connect
    _tcp_server->bind(server_ip, SERVER_PORT, MAX_NUM_USERS);
    if(_tcp_server->isBind()){
        std::cout << "bind success" << std::endl;
//        _tcp_server->setUnblocking(true);
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
    if(_is_bitcraze_connected){
        std::cout << "connected to BitCraze" <<std::endl;
        _bitcraze_thread = std::make_shared<std::thread>(&RaceCar::getBitCrazeOutput,this);
    }
}




RaceCar &RaceCar::setColorToSend()
{
    _camera.setupColorImage(RealSense::ColorFrameFormat::RGB8,RealSense::ColorRessolution::R_640x480, RealSense::ColorCamFps::F_30hz);
}

RaceCar &RaceCar::setIRToSend()
{
    _camera.setupInfraredImage(RealSense::InfrarFrameFormat::Y8, RealSense::InfrarRessolution::R_640x480, RealSense::InfrarCamFps::F_30hz, RealSense::InfrarCamera::LEFT);
}

RaceCar &RaceCar::setDepthToSend(){
    _camera.setupDepthImage(RealSense::DepthRessolution::R_640x480, RealSense::DepthCamFps::F_30hz);

}

void RaceCar::setCamAndJpegConfig()
{

    _camera.setupGyro();
    _camera.setupAccel();
    //choose one to send to remote (depth, color or IR)
    //Note that u can setup different frames to get from camera
    //and procces them but in this example we send only one type of frame
    //to remote
    setDepthToSend();
    setColorToSend();
    setIRToSend();


}


RaceCar &RaceCar::parseAndSendCmd(const char cmd)
{

    switch (cmd) {

    case 's': {
        _motor_control->stop();
        break;
    }
    case 'u': {
        _motor_control->changeSpeedBy(5);
        break;
    }
    case 'd': {
        _motor_control->changeSpeedBy(-5);
        break;
    }
    case 'l': {
        _motor_control->changeAngleBy(-30);
        break;
    }
    case 'r': {
        _motor_control->changeAngleBy(30);
        break;
    }
    case 'q': { //not supported
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
            _tcp_server->receive(_socket,&cmd, 1, 0);
            parseAndSendCmd(cmd);
        }

        else
        {
            _socket = _tcp_server->waitForConnections(1);
            std::cout << "wait to asafff" << std::endl;
            if(_socket > 0)
            {
//                _tcp_server->setClientUnblocking(_socket,true);
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
    _flow_data = {};
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



RaceCar &RaceCar::getCameraOutputAndSendToRemote()
{
    std::cout << "enter Camera thread" <<std::endl;

    bool new_settings_availible = true;

    while (_is_running && _tcp_client->isConnected())
    {


        char cmd = ' ';
        //non blocking receive if remote user didnt ask different frame stream
        //the fuction return -1
        _tcp_client->receive(&cmd, 1, 0);
        if (cmd == 'c')
        {
            _image_format_to_remote = RaceCar::format_to_remote::COLOR;
            new_settings_availible = true;
        }else if (cmd == 'i')
        {
            _image_format_to_remote = RaceCar::format_to_remote::INFRARED;
            new_settings_availible = true;
        }else if (cmd == 'd')
        {
            _image_format_to_remote = RaceCar::format_to_remote::DEPTH;
            new_settings_availible = true;
        }

        _camera.captureFrame();

        Camera::ColorImage image;

        Chaos::ColorPacket packet;
        Chaos::header header;
        //only one type of frame can be sent (jpeg conpressor configurated to that type)
        //if the remote user asked for different frame stream
        //we need to setup jpeg compressor according the frames type
        if (_image_format_to_remote == RaceCar::format_to_remote::COLOR)
        {
            image = _camera.getColorImage();
            if (new_settings_availible)
            {
                _jpeg_comp.setParams(COLOR_WIDTH,COLOR_HEIGHT,JpegCompressor::Format::RGB,100);
                new_settings_availible = false;
            }
        } else if (_image_format_to_remote == RaceCar::format_to_remote::INFRARED)
        {
            image = _camera.getInfraredImage();
            if (new_settings_availible)
            {
                _jpeg_comp.setParams(IR_WIDTH,IR_HEIGHT,JpegCompressor::Format::GREY_SCALE,100);
                new_settings_availible = false;
            }
        } else
        {
            image = _camera.getDepthColorizedImage();
            if (new_settings_availible)
            {
               _jpeg_comp.setParams(DEPTH_WIDTH,DEPTH_HEIGHT,JpegCompressor::Format::RGB,100);
               new_settings_availible = false;
            }
        }

        packet = buildColorPacket(image);
        header = buildColorHeader();
        //send to remote
        _tcp_client->send(reinterpret_cast<char*>(&header), sizeof(header));
        _tcp_client->send(reinterpret_cast<char*>(&packet), header.total_size);
        _tcp_client->send(reinterpret_cast<char*>(packet.image.compresed_data), packet.image.compressed_size);

    }
    _is_running = false;
    std::cout << "Camera thread finished" <<std::endl;
    return *this;
}

RaceCar &RaceCar::getBitCrazeOutput()
{
    std::cout << "enter BitCraze thread" << std::endl;
    _bitcraze.requestFlowData();
    while (_is_running) {

        Flow flow_data = _bitcraze.getFlowOutput();
//        std::cout << flow_data.deltaX <<"..." << flow_data.deltaY << "..."<<flow_data.range << "..." <<flow_data.dt << std::endl;

        std::lock_guard<std::mutex> lock(_flow_mtx);
        _flow_data.deltaX += flow_data.deltaX;
        _flow_data.deltaY += flow_data.deltaY;
        _flow_data.dt += flow_data.dt;
        _flow_data.range = flow_data.range;
//        _flow_data = flow_data;

    }
    _bitcraze.stopStream();
    std::cout << "BitCraze thread finished" << std::endl;
}



