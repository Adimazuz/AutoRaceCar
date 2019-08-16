#include <iostream>
#include <QKeyEvent>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Image.h"
#include "Chaos_types.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _keys(),
    _key_timer(),
    _client_sock(-1),
    _server(nullptr),
    _controller(nullptr),
    _is_run(true),
    _camera_thread(nullptr)
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
    for(auto &key : _keys)
    {
        if(isArrowKey(key))
        {
            if(_controller->isConnected())
            {
                _controller->send(keyToString(key));
            }
            else
            {
                _controller->disconnect();
                markControllerConnection(false);
            }
        }
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
//    _server->bind("132.68.36.50", 5555, 5);
    _server->bind("192.168.1.75", 5555, 5);
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
    connect(this, SIGNAL(imageReady(QImage&)), this, SLOT(handleCamera(QImage&)));
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

void MainWindow::receiveImageMetadata(Image &image)
{

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
    std::vector<uint8> compressed_image(1920*1200*3);

    while(_is_run)
    {
        if(_server->hasConnectionWithSocket(_client_sock))
        {
            QCoreApplication::processEvents();

            markCameraConnection(true);

            PacketToRemote::header header = {};
            _server->receive(_client_sock, reinterpret_cast<char*>(&header), sizeof(header));

            PacketToRemote::ColorDataAndPeriphelSensors packet = {};

            _server->receive(_client_sock, reinterpret_cast<char*>(&packet),
                             static_cast<uint32>(header.total_size));

//            packet.image.compresed_data = new uint8[packet.image.compressed_size];

//            _server->receive(_client_sock, reinterpret_cast<char*>(packet.image.compresed_data),
//                             static_cast<uint32>(packet.image.compressed_size));

            _server->receive(_client_sock, reinterpret_cast<char*>(compressed_image.data()),
                             static_cast<uint32>(packet.image.compressed_size));

//            std::vector<uint8> uncompressed_data(packet.image.size);

            _decompressor.decompress(compressed_image.data(), packet.image.compressed_size);
            uint8 *output = _decompressor.getOutput();


            QImage q_image(static_cast<unsigned char*>(output), static_cast<int>(packet.image.width),
                         static_cast<int>(packet.image.height), QImage::Format_RGB888);

            handleCamera(q_image);
            ui->dx->setText(QString::number(packet.flow_data.deltaX));
            ui->dy->setText(QString::number(packet.flow_data.deltaY));
            ui->range->setText(QString::number(packet.flow_data.range));
            ui->x->setText(QString::number(packet.accel_data.x));
            ui->y->setText(QString::number(packet.accel_data.y));
            ui->z->setText(QString::number(packet.accel_data.z));
            ui->psi->setText(QString::number(packet.euler_angl.x_pitch));
            ui->theta->setText(QString::number(packet.euler_angl.y_yaw));
            ui->phi->setText(QString::number(packet.euler_angl.z_roll));

//            delete [] packet.image.compresed_data;
        }
        else
        {
            markCameraConnection(false);
            _client_sock = _server->waitForConnections(1);
            if(_client_sock > 0)
            {
                info("camera connected");
            }
        }
    }
}

void MainWindow::handleCamera(QImage &image)
{
    QPixmap pixamp = QPixmap::fromImage(image);
    ui->lbl_img->setPixmap(pixamp.scaled(image.width(), image.height(), Qt::AspectRatioMode::KeepAspectRatio));
}

void MainWindow::on_connect_clicked()
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
