/********************************************************************************
** Form generated from reading UI file 'vekAppAddAT.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKAPPADDAT_H
#define UI_VEKAPPADDAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/view/jview/vekPanelAT.h"

QT_BEGIN_NAMESPACE

class Ui_vekAppAddAT
{
public:
    QGridLayout *gridLayout;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QComboBox *comboBox_SrcApp;
    QLabel *label_6;
    vekPanelAT *comboBox_JsonUrl;
    QPushButton *pushButton_AutoJson;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox_WinVersion;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_DockPath;
    QPushButton *pushButton_AutoDockPath;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QComboBox *comboBox_DockName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_AppExePath;
    QPushButton *pushButton_SetExePath;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_ProgText;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_DockDone;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *vekAppAddAT)
    {
        if (vekAppAddAT->objectName().isEmpty())
            vekAppAddAT->setObjectName(QString::fromUtf8("vekAppAddAT"));
        vekAppAddAT->resize(580, 218);
        vekAppAddAT->setMinimumSize(QSize(580, 200));
        vekAppAddAT->setMaximumSize(QSize(580, 220));
        gridLayout = new QGridLayout(vekAppAddAT);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        verticalFrame = new QFrame(vekAppAddAT);
        verticalFrame->setObjectName(QString::fromUtf8("verticalFrame"));
        verticalFrame->setMinimumSize(QSize(0, 0));
        verticalFrame->setMaximumSize(QSize(16777215, 16777215));
        verticalFrame->setFrameShape(QFrame::StyledPanel);
        verticalFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(3, 3, 3, -1);
        label_3 = new QLabel(verticalFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        comboBox_SrcApp = new QComboBox(verticalFrame);
        comboBox_SrcApp->setObjectName(QString::fromUtf8("comboBox_SrcApp"));

        horizontalLayout_7->addWidget(comboBox_SrcApp);

        label_6 = new QLabel(verticalFrame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_6);

        comboBox_JsonUrl = new vekPanelAT(verticalFrame);
        comboBox_JsonUrl->setObjectName(QString::fromUtf8("comboBox_JsonUrl"));
        comboBox_JsonUrl->setEditable(true);

        horizontalLayout_7->addWidget(comboBox_JsonUrl);

        pushButton_AutoJson = new QPushButton(verticalFrame);
        pushButton_AutoJson->setObjectName(QString::fromUtf8("pushButton_AutoJson"));

        horizontalLayout_7->addWidget(pushButton_AutoJson);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 20);
        horizontalLayout_7->setStretch(2, 1);
        horizontalLayout_7->setStretch(3, 40);
        horizontalLayout_7->setStretch(4, 10);

        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, -1, 3, -1);
        label = new QLabel(verticalFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        comboBox_WinVersion = new QComboBox(verticalFrame);
        comboBox_WinVersion->setObjectName(QString::fromUtf8("comboBox_WinVersion"));

        horizontalLayout_2->addWidget(comboBox_WinVersion);

        horizontalLayout_2->setStretch(0, 10);
        horizontalLayout_2->setStretch(1, 60);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(3, -1, 3, 0);
        label_4 = new QLabel(verticalFrame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_4);

        lineEdit_DockPath = new QLineEdit(verticalFrame);
        lineEdit_DockPath->setObjectName(QString::fromUtf8("lineEdit_DockPath"));

        horizontalLayout_5->addWidget(lineEdit_DockPath);

        pushButton_AutoDockPath = new QPushButton(verticalFrame);
        pushButton_AutoDockPath->setObjectName(QString::fromUtf8("pushButton_AutoDockPath"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_AutoDockPath->sizePolicy().hasHeightForWidth());
        pushButton_AutoDockPath->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(pushButton_AutoDockPath);

        horizontalLayout_5->setStretch(0, 10);
        horizontalLayout_5->setStretch(1, 50);
        horizontalLayout_5->setStretch(2, 10);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(3);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(3, -1, 3, -1);
        label_5 = new QLabel(verticalFrame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_5);

        comboBox_DockName = new QComboBox(verticalFrame);
        comboBox_DockName->setObjectName(QString::fromUtf8("comboBox_DockName"));
        comboBox_DockName->setEditable(true);

        horizontalLayout_6->addWidget(comboBox_DockName);

        horizontalLayout_6->setStretch(0, 10);
        horizontalLayout_6->setStretch(1, 60);

        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(3, -1, 3, -1);
        label_2 = new QLabel(verticalFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_2);

        lineEdit_AppExePath = new QLineEdit(verticalFrame);
        lineEdit_AppExePath->setObjectName(QString::fromUtf8("lineEdit_AppExePath"));

        horizontalLayout_3->addWidget(lineEdit_AppExePath);

        pushButton_SetExePath = new QPushButton(verticalFrame);
        pushButton_SetExePath->setObjectName(QString::fromUtf8("pushButton_SetExePath"));
        sizePolicy.setHeightForWidth(pushButton_SetExePath->sizePolicy().hasHeightForWidth());
        pushButton_SetExePath->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton_SetExePath);

        horizontalLayout_3->setStretch(0, 10);
        horizontalLayout_3->setStretch(1, 50);
        horizontalLayout_3->setStretch(2, 10);

        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, -1, 3, -1);
        label_ProgText = new QLabel(verticalFrame);
        label_ProgText->setObjectName(QString::fromUtf8("label_ProgText"));
        label_ProgText->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_ProgText);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 3);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_DockDone = new QPushButton(verticalFrame);
        pushButton_DockDone->setObjectName(QString::fromUtf8("pushButton_DockDone"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_DockDone->sizePolicy().hasHeightForWidth());
        pushButton_DockDone->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_DockDone);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 10);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 15);
        verticalLayout->setStretch(1, 15);
        verticalLayout->setStretch(2, 15);
        verticalLayout->setStretch(3, 15);
        verticalLayout->setStretch(4, 15);
        verticalLayout->setStretch(5, 15);
        verticalLayout->setStretch(6, 15);

        gridLayout->addWidget(verticalFrame, 0, 0, 1, 1);


        retranslateUi(vekAppAddAT);

        QMetaObject::connectSlotsByName(vekAppAddAT);
    } // setupUi

    void retranslateUi(QWidget *vekAppAddAT)
    {
        vekAppAddAT->setWindowTitle(QCoreApplication::translate("vekAppAddAT", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("vekAppAddAT", "\350\275\257\344\273\266\346\272\220:", nullptr));
        label_6->setText(QCoreApplication::translate("vekAppAddAT", "\351\205\215\347\275\256\350\204\232\346\234\254:", nullptr));
        pushButton_AutoJson->setText(QCoreApplication::translate("vekAppAddAT", "\350\256\276\347\275\256\350\204\232\346\234\254", nullptr));
        label->setText(QCoreApplication::translate("vekAppAddAT", "Wine\347\211\210\346\234\254:", nullptr));
        label_4->setText(QCoreApplication::translate("vekAppAddAT", "\345\256\271\345\231\250\347\233\256\345\275\225:", nullptr));
        pushButton_AutoDockPath->setText(QCoreApplication::translate("vekAppAddAT", "\350\256\276\347\275\256\350\267\257\345\276\204", nullptr));
        label_5->setText(QCoreApplication::translate("vekAppAddAT", " \345\256\271\345\231\250\345\220\215\345\255\227:", nullptr));
        label_2->setText(QCoreApplication::translate("vekAppAddAT", "\346\270\270\346\210\217Exe\350\267\257\345\276\204:", nullptr));
        pushButton_SetExePath->setText(QCoreApplication::translate("vekAppAddAT", "\350\256\276\347\275\256\350\267\257\345\276\204", nullptr));
        label_ProgText->setText(QString());
        pushButton_DockDone->setText(QCoreApplication::translate("vekAppAddAT", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekAppAddAT: public Ui_vekAppAddAT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKAPPADDAT_H
