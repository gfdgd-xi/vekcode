/********************************************************************************
** Form generated from reading UI file 'vekAppAddMulti.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKAPPADDMULTI_H
#define UI_VEKAPPADDMULTI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_vekAppAddMulti
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_AddDiy;
    QPushButton *pushButton_AddAuto;

    void setupUi(QDialog *vekAppAddMulti)
    {
        if (vekAppAddMulti->objectName().isEmpty())
            vekAppAddMulti->setObjectName(QString::fromUtf8("vekAppAddMulti"));
        vekAppAddMulti->resize(400, 80);
        vekAppAddMulti->setMinimumSize(QSize(400, 80));
        vekAppAddMulti->setMaximumSize(QSize(400, 80));
        gridLayout = new QGridLayout(vekAppAddMulti);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_AddDiy = new QPushButton(vekAppAddMulti);
        pushButton_AddDiy->setObjectName(QString::fromUtf8("pushButton_AddDiy"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_AddDiy->sizePolicy().hasHeightForWidth());
        pushButton_AddDiy->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_AddDiy);

        pushButton_AddAuto = new QPushButton(vekAppAddMulti);
        pushButton_AddAuto->setObjectName(QString::fromUtf8("pushButton_AddAuto"));
        sizePolicy.setHeightForWidth(pushButton_AddAuto->sizePolicy().hasHeightForWidth());
        pushButton_AddAuto->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_AddAuto);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(vekAppAddMulti);

        QMetaObject::connectSlotsByName(vekAppAddMulti);
    } // setupUi

    void retranslateUi(QDialog *vekAppAddMulti)
    {
        vekAppAddMulti->setWindowTitle(QCoreApplication::translate("vekAppAddMulti", "Dialog", nullptr));
        pushButton_AddDiy->setText(QCoreApplication::translate("vekAppAddMulti", "\346\211\213\345\212\250\350\256\276\347\275\256", nullptr));
        pushButton_AddAuto->setText(QCoreApplication::translate("vekAppAddMulti", "\350\207\252\345\212\250\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekAppAddMulti: public Ui_vekAppAddMulti {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKAPPADDMULTI_H
