#include <iostream>
#include <QKeyEvent>
#include <zlib.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _keys(),
    _key_timer(),
    _connections_timer(),
    _is_stream_on(true),
    _client_sock(-1),
    _is_controller_connected(false),
    _server(nullptr),
    _client(nullptr)
{
    ui->setupUi(this);
    init();
    checkConnections();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(_is_controller_connected)
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
    if(_is_controller_connected)
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
    delete ui;
}

void MainWindow::handleKey()
{
    for(auto &key : _keys)
    {
        if(isArrowKey(key))
        {
            _client->send(keyToString(key));
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

unsigned long MainWindow::receiveDataSize()
{
    auto len_data = _server->receive(_client_sock, sizeof(unsigned long));
    unsigned long* len = reinterpret_cast<unsigned long*>(len_data.data());

    return *len;
}

void MainWindow::info(const string &msg)
{
    std::cout << msg << std::endl;
}

void MainWindow::bindServer()
{
    _server->bind("192.168.1.100", 5555, 5);
    if(_server->isBind())
    {
        info("bind success");
    }
    else
    {
        info("bind failed");
    }
}

void MainWindow::signalConnections()
{
    connect(&_key_timer, SIGNAL(timeout()), this, SLOT(handleKey()));
    connect(&_connections_timer, SIGNAL(timeout()), this, SLOT(checkConnections()));
}

void MainWindow::initTimer(const int &interval)
{
    _key_timer.setInterval(interval);
    _key_timer.start();
}

void MainWindow::initClient()
{
    _client = ITcpClient::create();
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

void MainWindow::init()
{
    showMaximized();
    initDesign();
    signalConnections();
    initTimer(150);
    initClient();
    initServer();
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

void MainWindow::on_actionshow_triggered()
{
    if(ui->actionshow->isChecked())
    {
        _is_stream_on = !_is_stream_on;
    }
}

void MainWindow::checkConnections()
{
    if(_server->getNumOfConnectedClients() == 0)
    {
        _client_sock = _server->waitForConnections();
        info("camera connected");
        markCameraConnection(true);
    }

    unsigned long size = 320*180*3;

    while(_server->hasConnectionWithSocket(_client_sock))
    {
        auto len = receiveDataSize();

        auto data = _server->receive(_client_sock, static_cast<uint>(len));

        std::vector<unsigned char> uncompressed_data(size);

        uncompress(uncompressed_data.data(), &size, reinterpret_cast<unsigned char*>(data.data()), len);

        QImage image(reinterpret_cast<unsigned char*>(uncompressed_data.data()), 320, 180, QImage::Format_RGB888);
        QPixmap pixamp = QPixmap::fromImage(image);
        ui->lbl_img->setPixmap(pixamp.scaled(320, 180, Qt::AspectRatioMode::KeepAspectRatio));
        QCoreApplication::processEvents();
    }
}

void MainWindow::on_connect_clicked()
{
    if(!ui->controller_ip->text().isEmpty())
    {
        string controller_ip = ui->controller_ip->text().toStdString();
        unsigned short controller_port = ui->camera_port->text().toUShort();

        _client->connect(controller_ip, controller_port);
        if(_client->isConnected())
        {
            info("controller connection established successfully");
            markControllerConnection(true);
        }
    }
}
