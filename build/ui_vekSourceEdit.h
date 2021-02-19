/********************************************************************************
** Form generated from reading UI file 'vekSourceEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKSOURCEEDIT_H
#define UI_VEKSOURCEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_vekSourceEdit
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *verticalGroupBox;
    QVBoxLayout *verticalLayout;
    QTableView *tableView_WineSrcList;
    QGroupBox *verticalGroupBox_2;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView_GameSrcList;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Done;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *vekSourceEdit)
    {
        if (vekSourceEdit->objectName().isEmpty())
            vekSourceEdit->setObjectName(QString::fromUtf8("vekSourceEdit"));
        vekSourceEdit->resize(800, 600);
        vekSourceEdit->setMinimumSize(QSize(800, 600));
        vekSourceEdit->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(vekSourceEdit);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(12);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, -1, 3, -1);
        verticalGroupBox = new QGroupBox(vekSourceEdit);
        verticalGroupBox->setObjectName(QString::fromUtf8("verticalGroupBox"));
        verticalGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(verticalGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableView_WineSrcList = new QTableView(verticalGroupBox);
        tableView_WineSrcList->setObjectName(QString::fromUtf8("tableView_WineSrcList"));

        verticalLayout->addWidget(tableView_WineSrcList);


        horizontalLayout_2->addWidget(verticalGroupBox);

        verticalGroupBox_2 = new QGroupBox(vekSourceEdit);
        verticalGroupBox_2->setObjectName(QString::fromUtf8("verticalGroupBox_2"));
        verticalGroupBox_2->setLayoutDirection(Qt::LeftToRight);
        verticalGroupBox_2->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(verticalGroupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableView_GameSrcList = new QTableView(verticalGroupBox_2);
        tableView_GameSrcList->setObjectName(QString::fromUtf8("tableView_GameSrcList"));

        verticalLayout_2->addWidget(tableView_GameSrcList);


        horizontalLayout_2->addWidget(verticalGroupBox_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Done = new QPushButton(vekSourceEdit);
        pushButton_Done->setObjectName(QString::fromUtf8("pushButton_Done"));

        horizontalLayout->addWidget(pushButton_Done);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_3->setStretch(0, 50);
        verticalLayout_3->setStretch(1, 5);

        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(vekSourceEdit);

        QMetaObject::connectSlotsByName(vekSourceEdit);
    } // setupUi

    void retranslateUi(QDialog *vekSourceEdit)
    {
        vekSourceEdit->setWindowTitle(QCoreApplication::translate("vekSourceEdit", "\346\272\220\344\277\256\346\224\271", nullptr));
        verticalGroupBox->setTitle(QCoreApplication::translate("vekSourceEdit", "Wine\346\272\220", nullptr));
        verticalGroupBox_2->setTitle(QCoreApplication::translate("vekSourceEdit", "\350\275\257\344\273\266\346\272\220", nullptr));
        pushButton_Done->setText(QCoreApplication::translate("vekSourceEdit", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekSourceEdit: public Ui_vekSourceEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKSOURCEEDIT_H
