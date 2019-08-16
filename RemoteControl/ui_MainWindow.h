/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
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
    QPushButton *connect;
    QGridLayout *gridLayout_2;
    QLabel *psi;
    QLabel *optical_flow;
    QLabel *lbl_dx;
    QLabel *range;
    QLabel *lbl_dy;
    QLabel *gyro;
    QLabel *theta;
    QLabel *label_2;
    QLabel *lbl_phi;
    QLabel *accelometer;
    QLabel *dy;
    QLabel *lbl_range;
    QLabel *lbl_psi;
    QLabel *phi;
    QLabel *lbl_theta;
    QLabel *dx;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QLabel *controller;
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
        MainWindow->resize(808, 490);
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

        connect = new QPushButton(centralWidget);
        connect->setObjectName(QStringLiteral("connect"));

        gridLayout->addWidget(connect, 2, 0, 1, 4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        psi = new QLabel(centralWidget);
        psi->setObjectName(QStringLiteral("psi"));
        psi->setFrameShape(QFrame::StyledPanel);
        psi->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(psi, 2, 1, 1, 1);

        optical_flow = new QLabel(centralWidget);
        optical_flow->setObjectName(QStringLiteral("optical_flow"));
        QFont font;
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        optical_flow->setFont(font);
        optical_flow->setFrameShape(QFrame::NoFrame);
        optical_flow->setFrameShadow(QFrame::Plain);
        optical_flow->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(optical_flow, 0, 0, 1, 1);

        lbl_dx = new QLabel(centralWidget);
        lbl_dx->setObjectName(QStringLiteral("lbl_dx"));
        lbl_dx->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_dx, 1, 0, 1, 1);

        range = new QLabel(centralWidget);
        range->setObjectName(QStringLiteral("range"));
        range->setFrameShape(QFrame::StyledPanel);
        range->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(range, 7, 0, 1, 1);

        lbl_dy = new QLabel(centralWidget);
        lbl_dy->setObjectName(QStringLiteral("lbl_dy"));
        lbl_dy->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_dy, 3, 0, 1, 1);

        gyro = new QLabel(centralWidget);
        gyro->setObjectName(QStringLiteral("gyro"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        gyro->setFont(font1);
        gyro->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(gyro, 0, 1, 1, 1);

        theta = new QLabel(centralWidget);
        theta->setObjectName(QStringLiteral("theta"));
        theta->setFrameShape(QFrame::StyledPanel);
        theta->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(theta, 4, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 10, 0, 1, 1);

        lbl_phi = new QLabel(centralWidget);
        lbl_phi->setObjectName(QStringLiteral("lbl_phi"));
        lbl_phi->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_phi, 5, 1, 1, 1);

        accelometer = new QLabel(centralWidget);
        accelometer->setObjectName(QStringLiteral("accelometer"));
        accelometer->setFont(font1);
        accelometer->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(accelometer, 9, 0, 1, 1);

        dy = new QLabel(centralWidget);
        dy->setObjectName(QStringLiteral("dy"));
        dy->setFrameShape(QFrame::StyledPanel);
        dy->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(dy, 4, 0, 1, 1);

        lbl_range = new QLabel(centralWidget);
        lbl_range->setObjectName(QStringLiteral("lbl_range"));
        lbl_range->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_range, 5, 0, 1, 1);

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

        gridLayout_2->addWidget(dx, 2, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 14, 0, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFrameShape(QFrame::StyledPanel);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_9, 15, 0, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFrameShape(QFrame::StyledPanel);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 13, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 12, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 11, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_2, 8, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 3, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 3, 1, 1);

        controller = new QLabel(centralWidget);
        controller->setObjectName(QStringLiteral("controller"));
        controller->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(controller, 0, 2, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 808, 22));
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
        connect->setText(QApplication::translate("MainWindow", "connect", nullptr));
        psi->setText(QString());
        optical_flow->setText(QApplication::translate("MainWindow", "optical flow", nullptr));
        lbl_dx->setText(QApplication::translate("MainWindow", "dx", nullptr));
        range->setText(QString());
        lbl_dy->setText(QApplication::translate("MainWindow", "dy", nullptr));
        gyro->setText(QApplication::translate("MainWindow", "gyro", nullptr));
        theta->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "x", nullptr));
        lbl_phi->setText(QApplication::translate("MainWindow", "phi", nullptr));
        accelometer->setText(QApplication::translate("MainWindow", "accelometer", nullptr));
        dy->setText(QString());
        lbl_range->setText(QApplication::translate("MainWindow", "range", nullptr));
        lbl_psi->setText(QApplication::translate("MainWindow", "psi", nullptr));
        phi->setText(QString());
        lbl_theta->setText(QApplication::translate("MainWindow", "theta", nullptr));
        dx->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "z", nullptr));
        label_9->setText(QString());
        label_5->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "y", nullptr));
        label_3->setText(QString());
        controller->setText(QApplication::translate("MainWindow", "controller", nullptr));
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
