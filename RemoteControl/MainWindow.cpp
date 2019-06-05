#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _keys(),
    _client(nullptr),
    _serial()
{
    ui->setupUi(this);
    showMaximized();
    _key_timer.setInterval(50);
    connect(&_key_timer, SIGNAL(timeout()), this, SLOT(handleKey()));
    _key_timer.start();

    QImage image("/home/asaf/Desktop/Park/images/background.jpg");
    ui->lbl_img->setPixmap(QPixmap::fromImage(image).scaled(ui->lbl_img->width(), ui->lbl_img->height()));
    _client = ITcpClient::create();
//    _client->connect("127.0.0.1", 1234);
//    _serial.connect();
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
//            _client->send(keyToString(key));
//            _serial.write(keyToString(key));
            qDebug() << key << "pressed";
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
