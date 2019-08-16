#include <iostream>
#include <QKeyEvent>
#include <zlib.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"
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
    _server->bind("132.68.36.50", 5555, 5);
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
    while(_is_run)
    {
        if(_server->hasConnectionWithSocket(_client_sock))
        {
            QCoreApplication::processEvents();

            markCameraConnection(true);

            ColorImage color_image = {};
            _server->receive(_client_sock, reinterpret_cast<char*>(&color_image), sizeof(color_image) - sizeof(color_image.data));
             color_image.data = new uint8[color_image.size];
            _server->receive(_client_sock, reinterpret_cast<char*>(color_image.data), static_cast<uint32>(color_image.size));

            QImage image(static_cast<unsigned char*>(color_image.data), static_cast<int>(color_image.width),
                         static_cast<int>(color_image.height), QImage::Format_RGB888);

            delete [] color_image.data;

            emit imageReady(image);
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
