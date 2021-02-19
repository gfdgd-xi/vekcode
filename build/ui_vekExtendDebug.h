/********************************************************************************
** Form generated from reading UI file 'vekExtendDebug.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKEXTENDDEBUG_H
#define UI_VEKEXTENDDEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_vekExtendDebug
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *logTextEdit;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_DebugDllStr;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox_DebugDllList;
    QPushButton *pushButton_DebugDllAdd;
    QPushButton *pushButton_DebugDllDel;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_DebugStart;
    QPushButton *pushButton_DebugForceExit;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *vekExtendDebug)
    {
        if (vekExtendDebug->objectName().isEmpty())
            vekExtendDebug->setObjectName(QString::fromUtf8("vekExtendDebug"));
        vekExtendDebug->setWindowModality(Qt::NonModal);
        vekExtendDebug->resize(800, 600);
        vekExtendDebug->setMinimumSize(QSize(800, 600));
        vekExtendDebug->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_3 = new QVBoxLayout(vekExtendDebug);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, -1, 0);
        logTextEdit = new QTextEdit(vekExtendDebug);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));

        horizontalLayout_2->addWidget(logTextEdit);

        horizontalLayout_2->setStretch(0, 55);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 50);

        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(vekExtendDebug);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        lineEdit_DebugDllStr = new QLineEdit(vekExtendDebug);
        lineEdit_DebugDllStr->setObjectName(QString::fromUtf8("lineEdit_DebugDllStr"));

        horizontalLayout_3->addWidget(lineEdit_DebugDllStr);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(vekExtendDebug);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_DebugDllList = new QComboBox(vekExtendDebug);
        comboBox_DebugDllList->setObjectName(QString::fromUtf8("comboBox_DebugDllList"));

        horizontalLayout->addWidget(comboBox_DebugDllList);

        pushButton_DebugDllAdd = new QPushButton(vekExtendDebug);
        pushButton_DebugDllAdd->setObjectName(QString::fromUtf8("pushButton_DebugDllAdd"));

        horizontalLayout->addWidget(pushButton_DebugDllAdd);

        pushButton_DebugDllDel = new QPushButton(vekExtendDebug);
        pushButton_DebugDllDel->setObjectName(QString::fromUtf8("pushButton_DebugDllDel"));

        horizontalLayout->addWidget(pushButton_DebugDllDel);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 10);
        horizontalLayout->setStretch(2, 3);
        horizontalLayout->setStretch(3, 3);

        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_DebugStart = new QPushButton(vekExtendDebug);
        pushButton_DebugStart->setObjectName(QString::fromUtf8("pushButton_DebugStart"));

        horizontalLayout_4->addWidget(pushButton_DebugStart);

        pushButton_DebugForceExit = new QPushButton(vekExtendDebug);
        pushButton_DebugForceExit->setObjectName(QString::fromUtf8("pushButton_DebugForceExit"));

        horizontalLayout_4->addWidget(pushButton_DebugForceExit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3->setStretch(0, 80);
        verticalLayout_3->setStretch(1, 20);

        retranslateUi(vekExtendDebug);

        QMetaObject::connectSlotsByName(vekExtendDebug);
    } // setupUi

    void retranslateUi(QDialog *vekExtendDebug)
    {
        vekExtendDebug->setWindowTitle(QCoreApplication::translate("vekExtendDebug", "vek\350\260\203\350\257\225\345\267\245\345\205\267", nullptr));
        label->setText(QCoreApplication::translate("vekExtendDebug", "\351\231\204\345\212\240\350\260\203\350\257\225\345\272\223:", nullptr));
        label_2->setText(QCoreApplication::translate("vekExtendDebug", "\351\231\204\345\212\240\350\260\203\350\257\225\345\272\223\350\241\250:", nullptr));
        pushButton_DebugDllAdd->setText(QCoreApplication::translate("vekExtendDebug", "\345\242\236\345\212\240", nullptr));
        pushButton_DebugDllDel->setText(QCoreApplication::translate("vekExtendDebug", "\345\210\240\351\231\244", nullptr));
        pushButton_DebugStart->setText(QCoreApplication::translate("vekExtendDebug", "\350\260\203\350\257\225\350\277\220\350\241\214", nullptr));
        pushButton_DebugForceExit->setText(QCoreApplication::translate("vekExtendDebug", "\345\274\272\350\241\214\347\273\223\346\235\237\350\260\203\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekExtendDebug: public Ui_vekExtendDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKEXTENDDEBUG_H
