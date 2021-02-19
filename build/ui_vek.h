/********************************************************************************
** Form generated from reading UI file 'vek.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEK_H
#define UI_VEK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/view/aview/vekAppPanel.h"

QT_BEGIN_NAMESPACE

class Ui_vek
{
public:
    QAction *action_AddApp;
    QAction *action_About;
    QAction *action_WineInstall;
    QAction *action_Exit;
    QAction *action_EditSource;
    QAction *styleDefault;
    QAction *styleDark;
    QAction *styleLight;
    QAction *langChinese;
    QAction *langEnglish;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuWine;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_InstallApp;
    QPushButton *pushButton_vekAddApp;
    QPushButton *pushButton_vekRunApp;
    QSpacerItem *horizontalSpacer;
    QFrame *frame3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_AppSize;
    QLabel *label_appSizeText;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_procRow;
    QGridLayout *gridLayout;
    vekAppPanel *tabWidget;

    void setupUi(QWidget *vek)
    {
        if (vek->objectName().isEmpty())
            vek->setObjectName(QString::fromUtf8("vek"));
        vek->setWindowModality(Qt::NonModal);
        vek->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vek->sizePolicy().hasHeightForWidth());
        vek->setSizePolicy(sizePolicy);
        vek->setMinimumSize(QSize(800, 600));
        vek->setMaximumSize(QSize(16777215, 16777215));
        action_AddApp = new QAction(vek);
        action_AddApp->setObjectName(QString::fromUtf8("action_AddApp"));
        action_About = new QAction(vek);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_WineInstall = new QAction(vek);
        action_WineInstall->setObjectName(QString::fromUtf8("action_WineInstall"));
        action_Exit = new QAction(vek);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_EditSource = new QAction(vek);
        action_EditSource->setObjectName(QString::fromUtf8("action_EditSource"));
        styleDefault = new QAction(vek);
        styleDefault->setObjectName(QString::fromUtf8("styleDefault"));
        styleDark = new QAction(vek);
        styleDark->setObjectName(QString::fromUtf8("styleDark"));
        styleLight = new QAction(vek);
        styleLight->setObjectName(QString::fromUtf8("styleLight"));
        langChinese = new QAction(vek);
        langChinese->setObjectName(QString::fromUtf8("langChinese"));
        langEnglish = new QAction(vek);
        langEnglish->setObjectName(QString::fromUtf8("langEnglish"));
        menubar = new QMenuBar(vek);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 600));
        sizePolicy.setHeightForWidth(menubar->sizePolicy().hasHeightForWidth());
        menubar->setSizePolicy(sizePolicy);
        menubar->setMinimumSize(QSize(800, 600));
        menubar->setNativeMenuBar(false);
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        sizePolicy.setHeightForWidth(menu->sizePolicy().hasHeightForWidth());
        menu->setSizePolicy(sizePolicy);
        menu->setContextMenuPolicy(Qt::DefaultContextMenu);
        menu->setAcceptDrops(true);
        menuWine = new QMenu(menubar);
        menuWine->setObjectName(QString::fromUtf8("menuWine"));
        sizePolicy.setHeightForWidth(menuWine->sizePolicy().hasHeightForWidth());
        menuWine->setSizePolicy(sizePolicy);
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        sizePolicy.setHeightForWidth(menu_2->sizePolicy().hasHeightForWidth());
        menu_2->setSizePolicy(sizePolicy);
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        sizePolicy.setHeightForWidth(menu_3->sizePolicy().hasHeightForWidth());
        menu_3->setSizePolicy(sizePolicy);
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        sizePolicy.setHeightForWidth(menu_4->sizePolicy().hasHeightForWidth());
        menu_4->setSizePolicy(sizePolicy);
        menu_5 = new QMenu(menu_4);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        gridLayout_2 = new QGridLayout(vek);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(vek);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_2->setLineWidth(1);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_InstallApp = new QPushButton(frame_2);
        pushButton_InstallApp->setObjectName(QString::fromUtf8("pushButton_InstallApp"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_InstallApp->sizePolicy().hasHeightForWidth());
        pushButton_InstallApp->setSizePolicy(sizePolicy2);
        pushButton_InstallApp->setMinimumSize(QSize(80, 50));

        horizontalLayout_2->addWidget(pushButton_InstallApp);

        pushButton_vekAddApp = new QPushButton(frame_2);
        pushButton_vekAddApp->setObjectName(QString::fromUtf8("pushButton_vekAddApp"));
        sizePolicy2.setHeightForWidth(pushButton_vekAddApp->sizePolicy().hasHeightForWidth());
        pushButton_vekAddApp->setSizePolicy(sizePolicy2);
        pushButton_vekAddApp->setMinimumSize(QSize(80, 50));

        horizontalLayout_2->addWidget(pushButton_vekAddApp);

        pushButton_vekRunApp = new QPushButton(frame_2);
        pushButton_vekRunApp->setObjectName(QString::fromUtf8("pushButton_vekRunApp"));
        sizePolicy2.setHeightForWidth(pushButton_vekRunApp->sizePolicy().hasHeightForWidth());
        pushButton_vekRunApp->setSizePolicy(sizePolicy2);
        pushButton_vekRunApp->setMinimumSize(QSize(80, 50));

        horizontalLayout_2->addWidget(pushButton_vekRunApp);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        frame3 = new QFrame(frame_2);
        frame3->setObjectName(QString::fromUtf8("frame3"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame3->sizePolicy().hasHeightForWidth());
        frame3->setSizePolicy(sizePolicy3);
        frame3->setMaximumSize(QSize(16777215, 125));
        verticalLayout_2 = new QVBoxLayout(frame3);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_AppSize = new QLabel(frame3);
        label_AppSize->setObjectName(QString::fromUtf8("label_AppSize"));
        label_AppSize->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_AppSize);

        label_appSizeText = new QLabel(frame3);
        label_appSizeText->setObjectName(QString::fromUtf8("label_appSizeText"));
        label_appSizeText->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_appSizeText);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(frame3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        label_procRow = new QLabel(frame3);
        label_procRow->setObjectName(QString::fromUtf8("label_procRow"));
        label_procRow->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_procRow);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addWidget(frame3);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 1);
        horizontalLayout_2->setStretch(3, 12);
        horizontalLayout_2->setStretch(4, 5);

        verticalLayout->addWidget(frame_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        tabWidget = new vekAppPanel(frame);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalLayout->setStretch(0, 10);
        verticalLayout->setStretch(1, 90);

        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 26);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuWine->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(action_AddApp);
        menu->addAction(action_Exit);
        menuWine->addAction(action_WineInstall);
        menu_2->addAction(action_About);
        menu_3->addAction(action_EditSource);
        menu_4->addAction(menu_5->menuAction());
        menu_5->addAction(styleDefault);
        menu_5->addAction(styleDark);
        menu_5->addAction(styleLight);

        retranslateUi(vek);

        QMetaObject::connectSlotsByName(vek);
    } // setupUi

    void retranslateUi(QWidget *vek)
    {
        vek->setWindowTitle(QCoreApplication::translate("vek", "Vek", nullptr));
        action_AddApp->setText(QCoreApplication::translate("vek", "\345\242\236\345\212\240\346\270\270\346\210\217", nullptr));
        action_About->setText(QCoreApplication::translate("vek", "\345\205\263\344\272\216", nullptr));
        action_WineInstall->setText(QCoreApplication::translate("vek", "Wine\345\256\211\350\243\205", nullptr));
        action_Exit->setText(QCoreApplication::translate("vek", "\351\200\200\345\207\272", nullptr));
        action_EditSource->setText(QCoreApplication::translate("vek", "\344\277\256\346\224\271\346\272\220", nullptr));
        styleDefault->setText(QCoreApplication::translate("vek", "Default", nullptr));
#if QT_CONFIG(tooltip)
        styleDefault->setToolTip(QCoreApplication::translate("vek", "Default", nullptr));
#endif // QT_CONFIG(tooltip)
        styleDark->setText(QCoreApplication::translate("vek", "Dark", nullptr));
#if QT_CONFIG(tooltip)
        styleDark->setToolTip(QCoreApplication::translate("vek", "Dark ", nullptr));
#endif // QT_CONFIG(tooltip)
        styleLight->setText(QCoreApplication::translate("vek", "Light", nullptr));
#if QT_CONFIG(tooltip)
        styleLight->setToolTip(QCoreApplication::translate("vek", "Light", nullptr));
#endif // QT_CONFIG(tooltip)
        langChinese->setText(QCoreApplication::translate("vek", "Chinese", nullptr));
        langEnglish->setText(QCoreApplication::translate("vek", "English", nullptr));
        menu->setTitle(QCoreApplication::translate("vek", "\350\217\234\345\215\225", nullptr));
        menuWine->setTitle(QCoreApplication::translate("vek", "Wine\347\256\241\347\220\206", nullptr));
        menu_2->setTitle(QCoreApplication::translate("vek", "\345\270\256\345\212\251", nullptr));
        menu_3->setTitle(QCoreApplication::translate("vek", "\346\272\220\347\256\241\347\220\206", nullptr));
        menu_4->setTitle(QCoreApplication::translate("vek", "\347\225\214\351\235\242\347\256\241\347\220\206", nullptr));
        menu_5->setTitle(QCoreApplication::translate("vek", "\344\270\273\351\242\230\346\240\267\345\274\217", nullptr));
        pushButton_InstallApp->setText(QCoreApplication::translate("vek", "\345\256\211\350\243\205\345\272\224\347\224\250", nullptr));
        pushButton_vekAddApp->setText(QCoreApplication::translate("vek", "\345\242\236\345\212\240\345\272\224\347\224\250", nullptr));
        pushButton_vekRunApp->setText(QCoreApplication::translate("vek", "\350\277\220\350\241\214\345\272\224\347\224\250", nullptr));
        label_AppSize->setText(QCoreApplication::translate("vek", "\345\272\224\347\224\250\346\200\273\346\225\260:", nullptr));
        label_appSizeText->setText(QString());
        label_2->setText(QCoreApplication::translate("vek", "\350\277\233\347\250\213\346\200\273\346\225\260:", nullptr));
        label_procRow->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class vek: public Ui_vek {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEK_H
