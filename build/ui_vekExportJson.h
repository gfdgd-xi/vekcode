/********************************************************************************
** Form generated from reading UI file 'vekExportJson.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKEXPORTJSON_H
#define UI_VEKEXPORTJSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vekExportJson
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit_OutPutStr;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_otherSave;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *vekExportJson)
    {
        if (vekExportJson->objectName().isEmpty())
            vekExportJson->setObjectName(QString::fromUtf8("vekExportJson"));
        vekExportJson->resize(500, 550);
        vekExportJson->setMinimumSize(QSize(500, 550));
        vekExportJson->setMaximumSize(QSize(500, 550));
        verticalLayout_2 = new QVBoxLayout(vekExportJson);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        textEdit_OutPutStr = new QTextEdit(vekExportJson);
        textEdit_OutPutStr->setObjectName(QString::fromUtf8("textEdit_OutPutStr"));

        verticalLayout_3->addWidget(textEdit_OutPutStr);


        verticalLayout->addLayout(verticalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_otherSave = new QPushButton(vekExportJson);
        pushButton_otherSave->setObjectName(QString::fromUtf8("pushButton_otherSave"));

        horizontalLayout->addWidget(pushButton_otherSave);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(vekExportJson);

        QMetaObject::connectSlotsByName(vekExportJson);
    } // setupUi

    void retranslateUi(QWidget *vekExportJson)
    {
        vekExportJson->setWindowTitle(QCoreApplication::translate("vekExportJson", "\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
        pushButton_otherSave->setText(QCoreApplication::translate("vekExportJson", "\345\217\246\345\255\230\344\270\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekExportJson: public Ui_vekExportJson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKEXPORTJSON_H
