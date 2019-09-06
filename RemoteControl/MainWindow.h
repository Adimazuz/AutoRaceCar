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
#include "Chaos_types.h"

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
    void connectToConroller();
    void on_camera_request_currentTextChanged(const QString &str);

private:
    void info(const string &msg);
    void bindServer();
    void signalConnections();
    void initTimer(const int &interval);
    void initClient();
    void initServer();
    void initDesign();
    void initThreads();
    void initJpegDecompressor(const Chaos::ColorPacket &packet);
    void init();
    uint64 receiveCompressedSize();
    void markCameraConnection(const bool &is_connected);
    void markControllerConnection(const bool &is_connected);
    void cameraThread();
    void updateImage(const QImage &image);
    void updateOpticalFlow(const Flow &flow);
    void updateEulerAngles(const Camera::EulerAngles &angles);
    void updateAccelometer(const Camera::AccelData &accel_data);
    void update(const QImage &image, const Chaos::ColorPacket &packet);
    Chaos::header readHeader();
    Chaos::ColorPacket readColorPacket(std::vector<uint8> &compressed_image,
                                       const Chaos::header &header);
    QImage makeImage(std::vector<uint8> &compressed_image,
                     const Chaos::ColorPacket &packet);
    void waitForConnection();
    void handleColorPacket(std::vector<uint8> &compressed_image, const Chaos::ColorPacket &packet);


signals:
    void imageReady(QImage &image);


private:
    static constexpr int KEY_LEFT = 16777234;
    static constexpr int KEY_RIGHT = 16777236;
    static constexpr int KEY_UP = 16777235;
    static constexpr int KEY_DOWN = 16777237;
    static constexpr int FULL_HD_SIZE = 1920*1200*3;

    Ui::MainWindow *ui;
    QVector<int> _keys;
    QTimer _key_timer;
    Socket _client_sock;
    std::shared_ptr<ITcpServer> _server;
    std::shared_ptr<ITcpClient> _controller;
    bool _is_run;
    std::shared_ptr<std::thread> _camera_thread;
    JpegDecompressor _decompressor;
    bool _is_jpeg_decompressor_initialized;
    QString _curr_camera_request;
};

#endif // MAINWINDOW_H
