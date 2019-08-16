#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <memory>
#include <QTimer>
#include <thread>

#include "ITcpClient.h"
#include "ITcpServer.h"
#include "JpegDecompressor.h"
#include "Image.h"

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
    void receiveImageMetadata(Image &image);
    uint64 receiveCompressedSize();
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
    std::shared_ptr<ITcpServer> _server;
    std::shared_ptr<ITcpClient> _controller;
    bool _is_run;
    std::shared_ptr<std::thread> _camera_thread;
    JpegDecompressor _decompressor;
};

#endif // MAINWINDOW_H
