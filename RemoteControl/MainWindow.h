#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <memory>
#include <QTimer>
#include <thread>

#include "ITcpClient.h"
#include "../UdpServer/IUdpServer.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    ~MainWindow() override;

public slots:
    void handleKey();

private slots:
    void on_acn_exit_triggered();
    string keyToString(const int &key);
    bool isArrowKey(const int &key);
    void on_connect_clicked();
    void checkConnections();
    void handleCamera(QImage &image);

private:
    void info(const string &msg);
    void bindServer();
    void signalConnections();
    void initTimer(const int &interval);
    void initClient();
    void initServer();
    void initDesign();
    void initThreads();
    void init();
    void markCameraConnection(const bool &is_connected);
    void markControllerConnection(const bool &is_connected);
    void cameraThread();

signals:
    void imageReady(QImage &image);


private:
    static constexpr int KEY_LEFT = 16777234;
    static constexpr int KEY_RIGHT = 16777236;
    static constexpr int KEY_UP = 16777235;
    static constexpr int KEY_DOWN = 16777237;

    Ui::MainWindow *ui;
    QVector<int> _keys;
    QTimer _key_timer;
    Socket _client_sock;
    bool _is_controller_connected;
    std::shared_ptr<IUdpServer> _server;
    std::shared_ptr<ITcpClient> _client;
    bool _is_run;
    std::shared_ptr<std::thread> _camera_thread;
};

#endif // MAINWINDOW_H
