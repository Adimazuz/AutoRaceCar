/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *acn_exit;
    QAction *actionshow;
    QAction *actionimage;
    QAction *actiondepth;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *controller_port;
    QLineEdit *camera_port;
    QLabel *camera;
    QLineEdit *controller_ip;
    QLabel *lbl_img;
    QLineEdit *camera_ip;
    QSpacerItem *verticalSpacer;
    QComboBox *camera_request;
    QLabel *controller;
    QPushButton *connect;
    QGridLayout *gridLayout_2;
    QLabel *z;
    QLabel *dt;
    QLabel *label_2;
    QLabel *dy;
    QLabel *lbl_dx;
    QLabel *range;
    QLabel *label_4;
    QLabel *lbl_range;
    QLabel *psi;
    QLabel *gyro;
    QLabel *theta;
    QLabel *lbl_phi;
    QLabel *lbl_psi;
    QLabel *phi;
    QLabel *lbl_theta;
    QLabel *dx;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_7;
    QLabel *vx;
    QLabel *optical_flow;
    QLabel *label;
    QLabel *label_3;
    QLabel *x;
    QLabel *lbl_dy;
    QLabel *label_6;
    QLabel *y;
    QLabel *accelometer;
    QLabel *vy;
    QMenuBar *menuBar;
    QMenu *menufile;
    QMenu *menusettings;
    QMenu *menucamera;
    QMenu *menutype;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(934, 665);
        acn_exit = new QAction(MainWindow);
        acn_exit->setObjectName(QStringLiteral("acn_exit"));
        actionshow = new QAction(MainWindow);
        actionshow->setObjectName(QStringLiteral("actionshow"));
        actionshow->setCheckable(true);
        actionshow->setChecked(true);
        actionimage = new QAction(MainWindow);
        actionimage->setObjectName(QStringLiteral("actionimage"));
        actionimage->setCheckable(true);
        actionimage->setChecked(true);
        actiondepth = new QAction(MainWindow);
        actiondepth->setObjectName(QStringLiteral("actiondepth"));
        actiondepth->setCheckable(true);
        actiondepth->setChecked(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        controller_port = new QLineEdit(centralWidget);
        controller_port->setObjectName(QStringLiteral("controller_port"));
        controller_port->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(controller_port, 1, 3, 1, 1);

        camera_port = new QLineEdit(centralWidget);
        camera_port->setObjectName(QStringLiteral("camera_port"));
        camera_port->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(camera_port, 1, 1, 1, 1);

        camera = new QLabel(centralWidget);
        camera->setObjectName(QStringLiteral("camera"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(camera->sizePolicy().hasHeightForWidth());
        camera->setSizePolicy(sizePolicy);
        camera->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(camera, 0, 0, 1, 2);

        controller_ip = new QLineEdit(centralWidget);
        controller_ip->setObjectName(QStringLiteral("controller_ip"));
        controller_ip->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(controller_ip, 1, 2, 1, 1);

        lbl_img = new QLabel(centralWidget);
        lbl_img->setObjectName(QStringLiteral("lbl_img"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbl_img->sizePolicy().hasHeightForWidth());
        lbl_img->setSizePolicy(sizePolicy1);
        lbl_img->setFrameShape(QFrame::StyledPanel);
        lbl_img->setFrameShadow(QFrame::Plain);
        lbl_img->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_img, 3, 0, 2, 3);

        camera_ip = new QLineEdit(centralWidget);
        camera_ip->setObjectName(QStringLiteral("camera_ip"));
        camera_ip->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(camera_ip, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 3, 1, 1);

        camera_request = new QComboBox(centralWidget);
        camera_request->addItem(QString());
        camera_request->addItem(QString());
        camera_request->addItem(QString());
        camera_request->setObjectName(QStringLiteral("camera_request"));

        gridLayout->addWidget(camera_request, 2, 0, 1, 2);

        controller = new QLabel(centralWidget);
        controller->setObjectName(QStringLiteral("controller"));
        controller->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(controller, 0, 2, 1, 2);

        connect = new QPushButton(centralWidget);
        connect->setObjectName(QStringLiteral("connect"));

        gridLayout->addWidget(connect, 2, 2, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        z = new QLabel(centralWidget);
        z->setObjectName(QStringLiteral("z"));
        z->setFrameShape(QFrame::StyledPanel);
        z->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(z, 7, 0, 1, 1);

        dt = new QLabel(centralWidget);
        dt->setObjectName(QStringLiteral("dt"));
        dt->setFrameShape(QFrame::StyledPanel);
        dt->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(dt, 22, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        dy = new QLabel(centralWidget);
        dy->setObjectName(QStringLiteral("dy"));
        dy->setFrameShape(QFrame::StyledPanel);
        dy->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(dy, 17, 0, 1, 1);

        lbl_dx = new QLabel(centralWidget);
        lbl_dx->setObjectName(QStringLiteral("lbl_dx"));
        lbl_dx->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_dx, 11, 0, 1, 1);

        range = new QLabel(centralWidget);
        range->setObjectName(QStringLiteral("range"));
        range->setFrameShape(QFrame::StyledPanel);
        range->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(range, 20, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        lbl_range = new QLabel(centralWidget);
        lbl_range->setObjectName(QStringLiteral("lbl_range"));
        lbl_range->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_range, 19, 0, 1, 1);

        psi = new QLabel(centralWidget);
        psi->setObjectName(QStringLiteral("psi"));
        psi->setFrameShape(QFrame::StyledPanel);
        psi->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(psi, 2, 1, 1, 1);

        gyro = new QLabel(centralWidget);
        gyro->setObjectName(QStringLiteral("gyro"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        gyro->setFont(font);
        gyro->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(gyro, 0, 1, 1, 1);

        theta = new QLabel(centralWidget);
        theta->setObjectName(QStringLiteral("theta"));
        theta->setFrameShape(QFrame::StyledPanel);
        theta->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(theta, 4, 1, 1, 1);

        lbl_phi = new QLabel(centralWidget);
        lbl_phi->setObjectName(QStringLiteral("lbl_phi"));
        lbl_phi->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_phi, 5, 1, 1, 1);

        lbl_psi = new QLabel(centralWidget);
        lbl_psi->setObjectName(QStringLiteral("lbl_psi"));
        lbl_psi->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_psi, 1, 1, 1, 1);

        phi = new QLabel(centralWidget);
        phi->setObjectName(QStringLiteral("phi"));
        phi->setFrameShape(QFrame::StyledPanel);
        phi->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(phi, 7, 1, 1, 1);

        lbl_theta = new QLabel(centralWidget);
        lbl_theta->setObjectName(QStringLiteral("lbl_theta"));
        lbl_theta->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_theta, 3, 1, 1, 1);

        dx = new QLabel(centralWidget);
        dx->setObjectName(QStringLiteral("dx"));
        dx->setFrameShape(QFrame::StyledPanel);
        dx->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(dx, 13, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_2, 8, 0, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 25, 0, 1, 1);

        vx = new QLabel(centralWidget);
        vx->setObjectName(QStringLiteral("vx"));
        vx->setFrameShape(QFrame::StyledPanel);
        vx->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(vx, 24, 0, 1, 1);

        optical_flow = new QLabel(centralWidget);
        optical_flow->setObjectName(QStringLiteral("optical_flow"));
        QFont font1;
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        optical_flow->setFont(font1);
        optical_flow->setFrameShape(QFrame::NoFrame);
        optical_flow->setFrameShadow(QFrame::Plain);
        optical_flow->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(optical_flow, 9, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 21, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 23, 0, 1, 1);

        x = new QLabel(centralWidget);
        x->setObjectName(QStringLiteral("x"));
        x->setFrameShape(QFrame::StyledPanel);
        x->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(x, 2, 0, 1, 1);

        lbl_dy = new QLabel(centralWidget);
        lbl_dy->setObjectName(QStringLiteral("lbl_dy"));
        lbl_dy->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_dy, 15, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 5, 0, 1, 1);

        y = new QLabel(centralWidget);
        y->setObjectName(QStringLiteral("y"));
        y->setFrameShape(QFrame::StyledPanel);
        y->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(y, 4, 0, 1, 1);

        accelometer = new QLabel(centralWidget);
        accelometer->setObjectName(QStringLiteral("accelometer"));
        accelometer->setFont(font);
        accelometer->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(accelometer, 0, 0, 1, 1);

        vy = new QLabel(centralWidget);
        vy->setObjectName(QStringLiteral("vy"));
        vy->setFrameShape(QFrame::StyledPanel);
        vy->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(vy, 26, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 3, 3, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 934, 22));
        menufile = new QMenu(menuBar);
        menufile->setObjectName(QStringLiteral("menufile"));
        menusettings = new QMenu(menuBar);
        menusettings->setObjectName(QStringLiteral("menusettings"));
        menucamera = new QMenu(menusettings);
        menucamera->setObjectName(QStringLiteral("menucamera"));
        menutype = new QMenu(menucamera);
        menutype->setObjectName(QStringLiteral("menutype"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(camera_ip, camera_port);
        QWidget::setTabOrder(camera_port, controller_ip);
        QWidget::setTabOrder(controller_ip, controller_port);
        QWidget::setTabOrder(controller_port, connect);

        menuBar->addAction(menufile->menuAction());
        menuBar->addAction(menusettings->menuAction());
        menufile->addAction(acn_exit);
        menusettings->addAction(menucamera->menuAction());
        menucamera->addAction(actionshow);
        menucamera->addAction(menutype->menuAction());
        menutype->addAction(actionimage);
        menutype->addAction(actiondepth);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        acn_exit->setText(QApplication::translate("MainWindow", "exit", nullptr));
        actionshow->setText(QApplication::translate("MainWindow", "show", nullptr));
        actionimage->setText(QApplication::translate("MainWindow", "color image", nullptr));
        actiondepth->setText(QApplication::translate("MainWindow", "depth", nullptr));
        controller_port->setPlaceholderText(QApplication::translate("MainWindow", "port", nullptr));
        camera_port->setPlaceholderText(QApplication::translate("MainWindow", "port", nullptr));
        camera->setText(QApplication::translate("MainWindow", "camera", nullptr));
        controller_ip->setPlaceholderText(QApplication::translate("MainWindow", "ip", nullptr));
        lbl_img->setText(QString());
        camera_ip->setPlaceholderText(QApplication::translate("MainWindow", "ip", nullptr));
        camera_request->setItemText(0, QApplication::translate("MainWindow", "ColorImage", nullptr));
        camera_request->setItemText(1, QApplication::translate("MainWindow", "DepthImage", nullptr));
        camera_request->setItemText(2, QApplication::translate("MainWindow", "InfraRed", nullptr));

        controller->setText(QApplication::translate("MainWindow", "controller", nullptr));
        connect->setText(QApplication::translate("MainWindow", "connect", nullptr));
        z->setText(QString());
        dt->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "x [m/sec^2]", nullptr));
        dy->setText(QString());
        lbl_dx->setText(QApplication::translate("MainWindow", "dx [px]", nullptr));
        range->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "y [m/sec^2]", nullptr));
        lbl_range->setText(QApplication::translate("MainWindow", "range [mm]", nullptr));
        psi->setText(QString());
        gyro->setText(QApplication::translate("MainWindow", "gyro", nullptr));
        theta->setText(QString());
        lbl_phi->setText(QApplication::translate("MainWindow", "roll [rad/sec]", nullptr));
        lbl_psi->setText(QApplication::translate("MainWindow", "pitch [rad/sec]", nullptr));
        phi->setText(QString());
        lbl_theta->setText(QApplication::translate("MainWindow", "yaw [rad/sec]", nullptr));
        dx->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Vy [mm/s]", nullptr));
        vx->setText(QString());
        optical_flow->setText(QApplication::translate("MainWindow", "optical flow", nullptr));
        label->setText(QApplication::translate("MainWindow", "dt [ms]", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Vx [mm/s]", nullptr));
        x->setText(QString());
        lbl_dy->setText(QApplication::translate("MainWindow", "dy [px]", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "z [m/sec^2]", nullptr));
        y->setText(QString());
        accelometer->setText(QApplication::translate("MainWindow", "accelometer", nullptr));
        vy->setText(QString());
        menufile->setTitle(QApplication::translate("MainWindow", "file", nullptr));
        menusettings->setTitle(QApplication::translate("MainWindow", "settings", nullptr));
        menucamera->setTitle(QApplication::translate("MainWindow", "camera", nullptr));
        menutype->setTitle(QApplication::translate("MainWindow", "type", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
