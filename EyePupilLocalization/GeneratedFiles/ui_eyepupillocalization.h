/********************************************************************************
** Form generated from reading UI file 'eyepupillocalization.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EYEPUPILLOCALIZATION_H
#define UI_EYEPUPILLOCALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_EyePupilLocalizationClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_2;
    QLCDNumber *lcdNumber_Rx;
    QLCDNumber *lcdNumber_Ry;
    QLCDNumber *lcdNumber_Rr;
    QPushButton *Button_openvideo;
    QLabel *label_10;
    QLabel *label_Reye;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumber_Lx;
    QLCDNumber *lcdNumber_Ly;
    QLCDNumber *lcdNumber_Lr;
    QLabel *label_9;
    QLabel *label_Leye;
    QCustomPlot *customPlot_x;
    QCustomPlot *customPlot_print;
    QCustomPlot *customPlot_y;
    QPushButton *Button_print;
    QPushButton *Button_opencamera;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EyePupilLocalizationClass)
    {
        if (EyePupilLocalizationClass->objectName().isEmpty())
            EyePupilLocalizationClass->setObjectName(QStringLiteral("EyePupilLocalizationClass"));
        EyePupilLocalizationClass->resize(525, 711);
        centralWidget = new QWidget(EyePupilLocalizationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(310, 220, 191, 121));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_4->addWidget(label_4);

        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_4->addWidget(label_5);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_4->addWidget(label_6);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lcdNumber_Rx = new QLCDNumber(horizontalLayoutWidget_2);
        lcdNumber_Rx->setObjectName(QStringLiteral("lcdNumber_Rx"));

        verticalLayout_2->addWidget(lcdNumber_Rx);

        lcdNumber_Ry = new QLCDNumber(horizontalLayoutWidget_2);
        lcdNumber_Ry->setObjectName(QStringLiteral("lcdNumber_Ry"));

        verticalLayout_2->addWidget(lcdNumber_Ry);

        lcdNumber_Rr = new QLCDNumber(horizontalLayoutWidget_2);
        lcdNumber_Rr->setObjectName(QStringLiteral("lcdNumber_Rr"));

        verticalLayout_2->addWidget(lcdNumber_Rr);


        horizontalLayout_2->addLayout(verticalLayout_2);

        Button_openvideo = new QPushButton(centralWidget);
        Button_openvideo->setObjectName(QStringLiteral("Button_openvideo"));
        Button_openvideo->setGeometry(QRect(20, 10, 111, 31));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(380, 50, 54, 12));
        label_Reye = new QLabel(centralWidget);
        label_Reye->setObjectName(QStringLiteral("label_Reye"));
        label_Reye->setGeometry(QRect(310, 80, 191, 131));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 220, 191, 121));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lcdNumber_Lx = new QLCDNumber(horizontalLayoutWidget);
        lcdNumber_Lx->setObjectName(QStringLiteral("lcdNumber_Lx"));

        verticalLayout->addWidget(lcdNumber_Lx);

        lcdNumber_Ly = new QLCDNumber(horizontalLayoutWidget);
        lcdNumber_Ly->setObjectName(QStringLiteral("lcdNumber_Ly"));

        verticalLayout->addWidget(lcdNumber_Ly);

        lcdNumber_Lr = new QLCDNumber(horizontalLayoutWidget);
        lcdNumber_Lr->setObjectName(QStringLiteral("lcdNumber_Lr"));

        verticalLayout->addWidget(lcdNumber_Lr);


        horizontalLayout->addLayout(verticalLayout);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(90, 50, 54, 12));
        label_Leye = new QLabel(centralWidget);
        label_Leye->setObjectName(QStringLiteral("label_Leye"));
        label_Leye->setGeometry(QRect(40, 80, 191, 131));
        customPlot_x = new QCustomPlot(centralWidget);
        customPlot_x->setObjectName(QStringLiteral("customPlot_x"));
        customPlot_x->setGeometry(QRect(20, 350, 481, 141));
        customPlot_print = new QCustomPlot(customPlot_x);
        customPlot_print->setObjectName(QStringLiteral("customPlot_print"));
        customPlot_print->setEnabled(true);
        customPlot_print->setGeometry(QRect(0, 30, 680, 250));
        customPlot_y = new QCustomPlot(centralWidget);
        customPlot_y->setObjectName(QStringLiteral("customPlot_y"));
        customPlot_y->setGeometry(QRect(20, 510, 481, 141));
        Button_print = new QPushButton(centralWidget);
        Button_print->setObjectName(QStringLiteral("Button_print"));
        Button_print->setGeometry(QRect(390, 10, 111, 31));
        Button_opencamera = new QPushButton(centralWidget);
        Button_opencamera->setObjectName(QStringLiteral("Button_opencamera"));
        Button_opencamera->setGeometry(QRect(200, 10, 111, 31));
        EyePupilLocalizationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EyePupilLocalizationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 525, 23));
        EyePupilLocalizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EyePupilLocalizationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EyePupilLocalizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EyePupilLocalizationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EyePupilLocalizationClass->setStatusBar(statusBar);

        retranslateUi(EyePupilLocalizationClass);
        QObject::connect(Button_openvideo, SIGNAL(clicked()), EyePupilLocalizationClass, SLOT(on_pushButton_openvideo_clicked()));
        QObject::connect(Button_print, SIGNAL(clicked()), EyePupilLocalizationClass, SLOT(on_pushButton_print_clicked()));
        QObject::connect(Button_opencamera, SIGNAL(clicked()), EyePupilLocalizationClass, SLOT(on_pushButton_opencamera_clicked()));

        QMetaObject::connectSlotsByName(EyePupilLocalizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *EyePupilLocalizationClass)
    {
        EyePupilLocalizationClass->setWindowTitle(QApplication::translate("EyePupilLocalizationClass", "EyePupilLocalization", Q_NULLPTR));
        label_4->setText(QApplication::translate("EyePupilLocalizationClass", "X\347\273\235\345\257\271\345\234\260\345\235\200", Q_NULLPTR));
        label_5->setText(QApplication::translate("EyePupilLocalizationClass", "Y\347\273\235\345\257\271\345\234\260\345\235\200", Q_NULLPTR));
        label_6->setText(QApplication::translate("EyePupilLocalizationClass", "\347\236\263\345\255\224\345\215\212\345\276\204", Q_NULLPTR));
        Button_openvideo->setText(QApplication::translate("EyePupilLocalizationClass", "\346\211\223\345\274\200\346\234\254\345\234\260\350\247\206\351\242\221", Q_NULLPTR));
        label_10->setText(QApplication::translate("EyePupilLocalizationClass", "\345\217\263\347\234\274", Q_NULLPTR));
        label_Reye->setText(QString());
        label->setText(QApplication::translate("EyePupilLocalizationClass", "X\347\273\235\345\257\271\345\234\260\345\235\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("EyePupilLocalizationClass", "Y\347\273\235\345\257\271\345\234\260\345\235\200", Q_NULLPTR));
        label_3->setText(QApplication::translate("EyePupilLocalizationClass", "\347\236\263\345\255\224\345\215\212\345\276\204", Q_NULLPTR));
        label_9->setText(QApplication::translate("EyePupilLocalizationClass", "\345\267\246\347\234\274", Q_NULLPTR));
        label_Leye->setText(QString());
        Button_print->setText(QApplication::translate("EyePupilLocalizationClass", "\346\211\223\345\215\260", Q_NULLPTR));
        Button_opencamera->setText(QApplication::translate("EyePupilLocalizationClass", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EyePupilLocalizationClass: public Ui_EyePupilLocalizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EYEPUPILLOCALIZATION_H
