#include <QDebug>
#include <QKeyEvent>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _keys(),
    _client(nullptr),
    _is_stream_on(false)
{
    ui->setupUi(this);
    showMaximized();
    _key_timer.setInterval(50);
    connect(&_key_timer, SIGNAL(timeout()), this, SLOT(handleKey()));
    _key_timer.start();

    _client = ITcpClient::create();
    _client->connect("127.0.0.1", 5555);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!_keys.contains(event->key()))
    {
        _keys.push_back(event->key());
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()){
        return;
    }
    _keys.removeOne(event->key());
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

void MainWindow::on_btn_camera_clicked()
{
    _is_stream_on = !_is_stream_on;

    while(_is_stream_on)
    {
        auto data = _client->receive(500*500);
        QImage image(reinterpret_cast<unsigned char*>(data.data()), 500, 500, QImage::Format_Indexed8);
        ui->lbl_img->setPixmap(QPixmap::fromImage(image));
        QCoreApplication::processEvents();
    }
}
