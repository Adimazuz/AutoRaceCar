#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <memory>
#include <QTimer>

#include "ITcpClient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
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

private:
    static constexpr int KEY_LEFT = 16777234;
    static constexpr int KEY_RIGHT = 16777236;
    static constexpr int KEY_UP = 16777235;
    static constexpr int KEY_DOWN = 16777237;

    Ui::MainWindow *ui;
    QVector<int> _keys;
    std::shared_ptr<ITcpClient> _client;
    QTimer _key_timer;
    bool _is_stream_on;
};

#endif // MAINWINDOW_H
