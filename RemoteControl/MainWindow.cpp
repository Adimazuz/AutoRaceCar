#include <iostream>
#include <QKeyEvent>
#include <QColormap>
#include <fstream>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Chaos_types.h"
#include "RemoteControl_types.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _keys(),
    _key_timer(),
    _client_sock(-1),
    _server(nullptr),
    _controller(nullptr),
    _is_run(true),
    _camera_thread(nullptr),
    _is_jpeg_decompressor_initialized(false),
    _curr_camera_request("ColorImage")
{
    ui->setupUi(this);
    init();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(_controller->isConnected())
    {
        if(!_keys.contains(event->key()))
        {
            _keys.push_back(event->key());
        }

        setFocus();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(_controller->isConnected())
    {
        if(event->isAutoRepeat()){
            setFocus();
            return;
        }
        _keys.removeOne(event->key());

        setFocus();
    }
}

MainWindow::~MainWindow()
{
    _is_run = false;
    _camera_thread->join();
    delete ui;
}

void MainWindow::handleKey()
{
    if(_controller->isConnected())
    {
        for(auto &key : _keys)
        {
            if(isArrowKey(key))
            {
                _controller->send(keyToString(key));
            }
        }
    }
    else
    {
        markControllerConnection(false);
        _keys.clear();
    }
}

void MainWindow::on_acn_exit_triggered()
{
    close();
}

string MainWindow::keyToString(const int &key)
{
    if(key == KEY_LEFT)
    {
        return "l";
    }
    else if(key == KEY_RIGHT)
    {
        return "r";
    }
    else if(key == KEY_UP)
    {
        return "u";
    }

    return "d";
}

bool MainWindow::isArrowKey(const int &key)
{
    return key == KEY_LEFT || key == KEY_RIGHT ||
            key == KEY_UP || key == KEY_DOWN;
}

void MainWindow::info(const string &msg)
{
    std::cout << msg << std::endl;
}

void MainWindow::bindServer()
{
    _server->bind("132.68.36.138", 5555, 5);

    if(_server->isBind())
    {
        info("bind success");
        _server->setUnblocking(true);
    }
    else
    {
        info("bind failed");
    }
}

void MainWindow::signalConnections()
{
    qRegisterMetaType<QImage>("QImage&");

    connect(&_key_timer, SIGNAL(timeout()), this, SLOT(handleKey()));
}

void MainWindow::initTimer(const int &interval)
{
    _key_timer.setInterval(interval);
    _key_timer.start();
}

void MainWindow::initClient()
{
    _controller = ITcpClient::create();
}

void MainWindow::initServer()
{
    _server = ITcpServer::create();
    bindServer();
}

void MainWindow::initDesign()
{
    markCameraConnection(false);
    markControllerConnection(false);

    QPalette p;
    p.setColor(QPalette::ColorRole::Foreground, QColor(Qt::blue));

    ui->optical_flow->setPalette(p);
    ui->gyro->setPalette(p);
    ui->accelometer->setPalette(p);

}

void MainWindow::initThreads()
{
    _camera_thread = std::make_shared<std::thread>(&MainWindow::cameraThread, this);
}

void MainWindow::initJpegDecompressor(const Chaos::ColorPacket &packet)
{
    if(_is_jpeg_decompressor_initialized && packet.image.bytes_per_pixel == _decompressor.getBytesPerPixel())
    {
        return;
    }

    else
    {
        if(packet.image.bytes_per_pixel == 3)
        {
            _decompressor.setParams(packet.image.width, packet.image.height, JpegDecompressor::Format::RGB);
        }
        else if(packet.image.bytes_per_pixel == 1)
        {
            _decompressor.setParams(packet.image.width, packet.image.height, JpegDecompressor::Format::GREY_SCALE);
        }

        _is_jpeg_decompressor_initialized = true;
    }
}

void MainWindow::init()
{
    showMaximized();
    initDesign();
    signalConnections();
    initTimer(50);
    initClient();
    initServer();
    initThreads();
}

uint64 MainWindow::receiveCompressedSize()
{
    uint64 compressed_size = 0;

    _server->receive(_client_sock, reinterpret_cast<char*>(&compressed_size), sizeof(uint64));

    return compressed_size;
}

void MainWindow::markCameraConnection(const bool &is_connected)
{
    QPalette p;
    if(is_connected)
    {
        p.setColor(QPalette::ColorRole::Foreground, QColor(Qt::green));
    }
    else
    {
        p.setColor(QPalette::ColorRole::Foreground, QColor(Qt::red));
    }

    ui->camera->setPalette(p);
}

void MainWindow::markControllerConnection(const bool &is_connected)
{
    QPalette p;
    if(is_connected)
    {
        p.setColor(QPalette::ColorRole::Foreground, QColor(Qt::green));
    }
    else
    {
        p.setColor(QPalette::ColorRole::Foreground, QColor(Qt::red));
    }

    ui->controller->setPalette(p);
}

void MainWindow::cameraThread()
{
    std::vector<uint8> compressed_image(FULL_HD_SIZE);

    while(_is_run)
    {
        if(_server->hasConnectionWithSocket(_client_sock))
        {
            QCoreApplication::processEvents();
            markCameraConnection(true);

            Chaos::header header = readHeader();

            if(header.type_code == Chaos::COLOR_HEADER)
            {
                Chaos::ColorPacket packet = readColorPacket(compressed_image, header);
                handleColorPacket(compressed_image, packet);
            }
        }
        else
        {
            markCameraConnection(false);
            waitForConnection();
        }
    }
}

void MainWindow::updateOpticalFlow(const Flow &flow)
{
    ui->dx->setText(QString::number(flow.deltaX, 'f', 3));
    ui->dy->setText(QString::number(flow.deltaY, 'f', 3));
    ui->range->setText(QString::number(static_cast<real64>(flow.range), 'f', 3));
}

void MainWindow::updateEulerAngles(const Camera::EulerAngles &angles)
{
    ui->psi->setText(QString::number(static_cast<real64>(angles.x_pitch), 'f', 3));
    ui->theta->setText(QString::number(static_cast<real64>(angles.y_yaw), 'f', 3));
    ui->phi->setText(QString::number(static_cast<real64>(angles.z_roll), 'f', 3));
}

void MainWindow::updateAccelometer(const Camera::AccelData &accel_data)
{
    ui->x->setText(QString::number(static_cast<real64>(accel_data.x), 'f', 3));
    ui->y->setText(QString::number(static_cast<real64>(accel_data.y), 'f', 3));
    ui->z->setText(QString::number(static_cast<real64>(accel_data.z), 'f', 3));
}

void MainWindow::update(const QImage &image, const Chaos::ColorPacket &packet)
{
    updateImage(image);
    updateOpticalFlow(packet.flow_data);
    updateEulerAngles(packet.euler_angl);
    updateAccelometer(packet.accel_data);
}

Chaos::header MainWindow::readHeader()
{
    Chaos::header header = {};
    _server->receive(_client_sock, reinterpret_cast<char*>(&header), sizeof(header));

    return header;
}

Chaos::ColorPacket MainWindow::readColorPacket(std::vector<uint8> &compressed_image,
                                                                   const Chaos::header &header)
{
    Chaos::ColorPacket packet = {};

    _server->receive(_client_sock, reinterpret_cast<char*>(&packet),
                     static_cast<uint32>(header.total_size));

    _server->receive(_client_sock, reinterpret_cast<char*>(compressed_image.data()),
                     static_cast<uint32>(packet.image.compressed_size));

    return packet;
}

QImage MainWindow::makeImage(std::vector<uint8> &compressed_image,
                             const Chaos::ColorPacket &packet)
{
    _decompressor.decompress(compressed_image.data(), packet.image.compressed_size);
    uint8 *output = _decompressor.getOutput();

    QImage image;

    if(packet.image.bytes_per_pixel == 3)
    {
        image = QImage(static_cast<unsigned char*>(output), static_cast<int>(packet.image.width),
                     static_cast<int>(packet.image.height), QImage::Format_RGB888);
    }

    else if(packet.image.bytes_per_pixel == 1)
    {
        image = QImage(static_cast<unsigned char*>(output), static_cast<int>(packet.image.width),
                     static_cast<int>(packet.image.height), QImage::Format_Indexed8);
    }

    return image;
}

void MainWindow::waitForConnection()
{
    _client_sock = _server->waitForConnections(1);
    if(_client_sock > 0)
    {
        info("camera connected");
    }
}

void MainWindow::handleColorPacket(std::vector<uint8> &compressed_image, const Chaos::ColorPacket &packet)
{
    initJpegDecompressor(packet);

    if(packet.image.size > 0)
    {
        QImage image = makeImage(compressed_image, packet);
        update(image, packet);
    }
}

void MainWindow::updateImage(const QImage &image)
{
    QPixmap pixamp = QPixmap::fromImage(image);
    ui->lbl_img->setPixmap(pixamp.scaled(image.width(), image.height(), Qt::AspectRatioMode::KeepAspectRatio));
}

void MainWindow::connectToConroller()
{
    if(!ui->controller_ip->text().isEmpty())
    {
        string controller_ip = ui->controller_ip->text().toStdString();
        unsigned short controller_port = ui->controller_port->text().toUShort();

        _controller->connect(controller_ip, controller_port);
        if(_controller->isConnected())
        {
            info("controller connection established successfully");
            markControllerConnection(true);
        }
    }
    setFocus();
}

void MainWindow::on_connect_clicked()
{
    connectToConroller();
}

//TODO unblocking for server and client

void MainWindow::on_camera_request_currentTextChanged(const QString &str)
{
    if(_server->isBind() && _server->hasConnectionWithSocket(_client_sock))
    {
        if(str == "ColorImage")
        {
            _server->send(_client_sock, "c");
        }
        else if(str == "DepthImage")
        {
            _server->send(_client_sock, "d");
        }
        else if(str == "InfraRed")
        {
            _server->send(_client_sock, "i");
        }

        _curr_camera_request = str;
    }
    else
    {
        std::cout << "cannot send request, thers is no connection with the camera" << std::endl;
        ui->camera_request->setCurrentText(_curr_camera_request);
    }
}
