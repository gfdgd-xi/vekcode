/********************************************************************************
** Form generated from reading UI file 'vekWineOption.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKWINEOPTION_H
#define UI_VEKWINEOPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vekWineOption
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QComboBox *comboBox_wineSrc;
    QLabel *label;
    QComboBox *comboBox_wineVer;
    QPushButton *pushButton_Install;
    QPushButton *pushButton_deleteWine;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_InstallPath;
    QToolButton *toolButton_SetInstallDir;
    QFrame *frame;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QTextEdit *textEdit;

    void setupUi(QWidget *vekWineOption)
    {
        if (vekWineOption->objectName().isEmpty())
            vekWineOption->setObjectName(QString::fromUtf8("vekWineOption"));
        vekWineOption->setWindowModality(Qt::NonModal);
        vekWineOption->setEnabled(true);
        vekWineOption->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vekWineOption->sizePolicy().hasHeightForWidth());
        vekWineOption->setSizePolicy(sizePolicy);
        vekWineOption->setMinimumSize(QSize(800, 600));
        vekWineOption->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft JhengHei UI"));
        vekWineOption->setFont(font);
        vekWineOption->setWindowOpacity(1.000000000000000);
        verticalLayout = new QVBoxLayout(vekWineOption);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        frame_3 = new QFrame(vekWineOption);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setMaximumSize(QSize(16777215, 38));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        comboBox_wineSrc = new QComboBox(frame_3);
        comboBox_wineSrc->setObjectName(QString::fromUtf8("comboBox_wineSrc"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_wineSrc->sizePolicy().hasHeightForWidth());
        comboBox_wineSrc->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(comboBox_wineSrc);

        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        comboBox_wineVer = new QComboBox(frame_3);
        comboBox_wineVer->setObjectName(QString::fromUtf8("comboBox_wineVer"));
        sizePolicy.setHeightForWidth(comboBox_wineVer->sizePolicy().hasHeightForWidth());
        comboBox_wineVer->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox_wineVer);

        pushButton_Install = new QPushButton(frame_3);
        pushButton_Install->setObjectName(QString::fromUtf8("pushButton_Install"));
        sizePolicy.setHeightForWidth(pushButton_Install->sizePolicy().hasHeightForWidth());
        pushButton_Install->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_Install);

        pushButton_deleteWine = new QPushButton(frame_3);
        pushButton_deleteWine->setObjectName(QString::fromUtf8("pushButton_deleteWine"));
        sizePolicy.setHeightForWidth(pushButton_deleteWine->sizePolicy().hasHeightForWidth());
        pushButton_deleteWine->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_deleteWine);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 30);
        horizontalLayout->setStretch(2, 10);
        horizontalLayout->setStretch(3, 80);
        horizontalLayout->setStretch(5, 1);

        verticalLayout_3->addWidget(frame_3);

        frame_2 = new QFrame(vekWineOption);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setMaximumSize(QSize(16777215, 38));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_InstallPath = new QLineEdit(frame_2);
        lineEdit_InstallPath->setObjectName(QString::fromUtf8("lineEdit_InstallPath"));
        sizePolicy.setHeightForWidth(lineEdit_InstallPath->sizePolicy().hasHeightForWidth());
        lineEdit_InstallPath->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_InstallPath);

        toolButton_SetInstallDir = new QToolButton(frame_2);
        toolButton_SetInstallDir->setObjectName(QString::fromUtf8("toolButton_SetInstallDir"));
        sizePolicy2.setHeightForWidth(toolButton_SetInstallDir->sizePolicy().hasHeightForWidth());
        toolButton_SetInstallDir->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(toolButton_SetInstallDir);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 15);
        horizontalLayout_2->setStretch(2, 5);

        verticalLayout_3->addWidget(frame_2);

        frame = new QFrame(vekWineOption);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        frame->setMidLineWidth(0);
        verticalLayout_5 = new QVBoxLayout(frame);
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(3, 3, 3, 3);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_4);

        textEdit = new QTextEdit(frame);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setAutoFillBackground(false);

        verticalLayout_5->addWidget(textEdit);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 15);

        verticalLayout_3->addWidget(frame);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 10);

        verticalLayout->addLayout(verticalLayout_3);


        retranslateUi(vekWineOption);

        QMetaObject::connectSlotsByName(vekWineOption);
    } // setupUi

    void retranslateUi(QWidget *vekWineOption)
    {
        vekWineOption->setWindowTitle(QCoreApplication::translate("vekWineOption", "Wine\345\256\211\350\243\205", nullptr));
        label_3->setText(QCoreApplication::translate("vekWineOption", "Wine\346\272\220:", nullptr));
        label->setText(QCoreApplication::translate("vekWineOption", "Wine\347\211\210\346\234\254:", nullptr));
        pushButton_Install->setText(QCoreApplication::translate("vekWineOption", "\345\256\211\350\243\205", nullptr));
        pushButton_deleteWine->setText(QCoreApplication::translate("vekWineOption", "\345\210\240\351\231\244", nullptr));
        label_2->setText(QCoreApplication::translate("vekWineOption", "Wine\345\256\211\350\243\205\347\233\256\345\275\225:", nullptr));
        toolButton_SetInstallDir->setText(QCoreApplication::translate("vekWineOption", "\350\256\276\347\275\256\347\233\256\345\275\225", nullptr));
        label_4->setText(QCoreApplication::translate("vekWineOption", "\345\256\211\350\243\205\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekWineOption: public Ui_vekWineOption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKWINEOPTION_H
