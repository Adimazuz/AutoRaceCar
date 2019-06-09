#include <QDebug>
#include <QKeyEvent>
#include <zlib.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _keys(),
    _key_timer(),
    _is_stream_on(false),
    _client_sock(-1),
    _is_connected(false),
    _server(nullptr)
{
    ui->setupUi(this);
    showMaximized();
    _key_timer.setInterval(50);
    connect(&_key_timer, SIGNAL(timeout()), this, SLOT(handleKey()));
    _key_timer.start();

    _server = ITcpServer::create("132.68.36.54", 5560, 5);
    qDebug() << "bind success";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!_keys.contains(event->key()))
    {
        _keys.push_back(event->key());
    }

    setFocus();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()){
        setFocus();
        return;
    }
    _keys.removeOne(event->key());

    setFocus();
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
//            _server->send(_client_sock, keyToString(key));
            qDebug() << key;
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

void MainWindow::on_btn_camera_clicked()
{
    if(!_is_connected)
    {
       _client_sock = _server->waitForConnections();
       qDebug() << "someone connected";
       _is_connected = true;
    }

    _is_stream_on = !_is_stream_on;

    unsigned long size = 640*480*3;

    while(_is_stream_on)
    {
        auto len = receiveDataSize();

        auto data = _server->receive(_client_sock, static_cast<uint>(len));

        std::vector<unsigned char> uncompressed_data(size);

        uncompress(uncompressed_data.data(), &size, reinterpret_cast<unsigned char*>(data.data()), len);

        QImage image(reinterpret_cast<unsigned char*>(uncompressed_data.data()), 640, 480, QImage::Format_RGB888);
        QPixmap pixamp = QPixmap::fromImage(image);
        ui->lbl_img->setPixmap(pixamp.scaled(640, 480, Qt::AspectRatioMode::KeepAspectRatio));
        QCoreApplication::processEvents();
    }
}

unsigned long MainWindow::receiveDataSize()
{
    auto len_data = _server->receive(_client_sock, sizeof(unsigned long));
    unsigned long* len = reinterpret_cast<unsigned long*>(len_data.data());

    return *len;
}
