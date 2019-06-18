#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <memory>
#include <QTimer>

#include "ITcpClient.h"
#include "../TcpServer/ITcpServer.h"

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

    void on_btn_camera_clicked();

    void on_actionconnect_server_triggered();

    void on_actionconnect_triggered();

private:
    unsigned long receiveDataSize();

private:
    static constexpr int KEY_LEFT = 16777234;
    static constexpr int KEY_RIGHT = 16777236;
    static constexpr int KEY_UP = 16777235;
    static constexpr int KEY_DOWN = 16777237;

    Ui::MainWindow *ui;
    QVector<int> _keys;
    QTimer _key_timer;
    bool _is_stream_on;
    Socket _client_sock;
    bool _is_connected;
    std::shared_ptr<ITcpServer> _server;
    std::shared_ptr<ITcpClient> _client;
};

#endif // MAINWINDOW_H
