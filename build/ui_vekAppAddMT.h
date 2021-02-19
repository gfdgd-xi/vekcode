/********************************************************************************
** Form generated from reading UI file 'vekAppAddMT.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKAPPADDMT_H
#define UI_VEKAPPADDMT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vekAppAddMT
{
public:
    QGridLayout *gridLayout;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *verticalGroupBox_3;
    QVBoxLayout *verticalLayout_5;
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *lineEdit_RunDockPath;
    QPushButton *pushButton_SetDockPath;
    QLabel *label_5;
    QComboBox *comboBox_DockName;
    QPushButton *pushButton_initDock;
    QFrame *horizontalFrame_2;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *checkBox_DefaultFonts;
    QCheckBox *checkBox_wineMemorySharing;
    QCheckBox *checkBox_wineRealTimePriority;
    QCheckBox *checkBox_wineMemoryOptimization;
    QCheckBox *checkBox_winerunlog;
    QCheckBox *checkBox_Gecko;
    QCheckBox *checkBox_Mono;
    QCheckBox *checkBox_Ass;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_Set;
    QSpacerItem *horizontalSpacer_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_TipsText;
    QGroupBox *verticalGroupBox_4;
    QVBoxLayout *verticalLayout_9;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QComboBox *comboBox_dockSystemVersion;
    QLabel *label_11;
    QComboBox *comboBox_dockbit;
    QLabel *label_12;
    QComboBox *comboBox_winebit;
    QFrame *frame_4;
    QHBoxLayout *frame_3;
    QTextEdit *textEdit;
    QWidget *tab_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_otherAgrs;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_setIco;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QComboBox *comboBox_RunWine;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_AppName;
    QLabel *label_10;
    QLineEdit *lineEdit_MainProcName;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_AppInstallExe;
    QPushButton *pushButton_SetAppExe;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *lineEdit_workPath;
    QPushButton *pushButton_workPath;
    QWidget *tab_6;
    QGroupBox *groupBox_dxvk;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_stateDxvk;
    QComboBox *comboBox_dxvkversion;
    QCheckBox *checkBox_statedxvkhud;
    QCheckBox *checkBox_dxvkConfigState;
    QLabel *label_4;
    QLineEdit *lineEdit_dxvkConfigFIle;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QTextEdit *textEdit_dxvkConfigFileData;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_SaveDxvkConfFile;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab_4;
    QGroupBox *verticalGroupBox;
    QVBoxLayout *verticalLayout_4;
    QTableView *tableView_EnvList;
    QWidget *tab_5;
    QGroupBox *verticalGroupBox_2;
    QVBoxLayout *verticalLayout_6;
    QTableView *tableView_ProcList;
    QWidget *tab_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_8;
    QTableView *tableView_RegsList;

    void setupUi(QWidget *vekAppAddMT)
    {
        if (vekAppAddMT->objectName().isEmpty())
            vekAppAddMT->setObjectName(QString::fromUtf8("vekAppAddMT"));
        vekAppAddMT->setWindowModality(Qt::NonModal);
        vekAppAddMT->setEnabled(true);
        vekAppAddMT->resize(800, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vekAppAddMT->sizePolicy().hasHeightForWidth());
        vekAppAddMT->setSizePolicy(sizePolicy);
        vekAppAddMT->setMinimumSize(QSize(800, 500));
        vekAppAddMT->setMaximumSize(QSize(800, 500));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft JhengHei UI"));
        vekAppAddMT->setFont(font);
        vekAppAddMT->setMouseTracking(false);
        vekAppAddMT->setWindowOpacity(1.000000000000000);
        vekAppAddMT->setAutoFillBackground(false);
        gridLayout = new QGridLayout(vekAppAddMT);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame_5 = new QFrame(vekAppAddMT);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_5);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        tabWidget = new QTabWidget(frame_5);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalGroupBox_3 = new QGroupBox(tab);
        verticalGroupBox_3->setObjectName(QString::fromUtf8("verticalGroupBox_3"));
        verticalGroupBox_3->setGeometry(QRect(0, 0, 787, 121));
        verticalLayout_5 = new QVBoxLayout(verticalGroupBox_3);
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        horizontalFrame = new QFrame(verticalGroupBox_3);
        horizontalFrame->setObjectName(QString::fromUtf8("horizontalFrame"));
        horizontalFrame->setFrameShape(QFrame::StyledPanel);
        horizontalFrame->setFrameShadow(QFrame::Raised);
        horizontalFrame->setMidLineWidth(0);
        horizontalLayout_7 = new QHBoxLayout(horizontalFrame);
        horizontalLayout_7->setSpacing(3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(horizontalFrame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_7);

        lineEdit_RunDockPath = new QLineEdit(horizontalFrame);
        lineEdit_RunDockPath->setObjectName(QString::fromUtf8("lineEdit_RunDockPath"));
        sizePolicy1.setHeightForWidth(lineEdit_RunDockPath->sizePolicy().hasHeightForWidth());
        lineEdit_RunDockPath->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(lineEdit_RunDockPath);

        pushButton_SetDockPath = new QPushButton(horizontalFrame);
        pushButton_SetDockPath->setObjectName(QString::fromUtf8("pushButton_SetDockPath"));
        sizePolicy1.setHeightForWidth(pushButton_SetDockPath->sizePolicy().hasHeightForWidth());
        pushButton_SetDockPath->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(pushButton_SetDockPath);

        label_5 = new QLabel(horizontalFrame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(label_5);

        comboBox_DockName = new QComboBox(horizontalFrame);
        comboBox_DockName->setObjectName(QString::fromUtf8("comboBox_DockName"));
        comboBox_DockName->setFocusPolicy(Qt::WheelFocus);
        comboBox_DockName->setContextMenuPolicy(Qt::DefaultContextMenu);
        comboBox_DockName->setEditable(true);
        comboBox_DockName->setInsertPolicy(QComboBox::InsertAtBottom);
        comboBox_DockName->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        comboBox_DockName->setDuplicatesEnabled(false);
        comboBox_DockName->setFrame(true);

        horizontalLayout_7->addWidget(comboBox_DockName);

        pushButton_initDock = new QPushButton(horizontalFrame);
        pushButton_initDock->setObjectName(QString::fromUtf8("pushButton_initDock"));
        sizePolicy1.setHeightForWidth(pushButton_initDock->sizePolicy().hasHeightForWidth());
        pushButton_initDock->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(pushButton_initDock);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 50);
        horizontalLayout_7->setStretch(2, 10);
        horizontalLayout_7->setStretch(3, 1);
        horizontalLayout_7->setStretch(4, 10);
        horizontalLayout_7->setStretch(5, 10);

        verticalLayout_5->addWidget(horizontalFrame);

        horizontalFrame_2 = new QFrame(verticalGroupBox_3);
        horizontalFrame_2->setObjectName(QString::fromUtf8("horizontalFrame_2"));
        horizontalFrame_2->setFrameShape(QFrame::StyledPanel);
        horizontalFrame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_11 = new QHBoxLayout(horizontalFrame_2);
        horizontalLayout_11->setSpacing(3);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(1, 1, 1, 1);
        checkBox_DefaultFonts = new QCheckBox(horizontalFrame_2);
        checkBox_DefaultFonts->setObjectName(QString::fromUtf8("checkBox_DefaultFonts"));
        sizePolicy1.setHeightForWidth(checkBox_DefaultFonts->sizePolicy().hasHeightForWidth());
        checkBox_DefaultFonts->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(checkBox_DefaultFonts);

        checkBox_wineMemorySharing = new QCheckBox(horizontalFrame_2);
        checkBox_wineMemorySharing->setObjectName(QString::fromUtf8("checkBox_wineMemorySharing"));
        sizePolicy1.setHeightForWidth(checkBox_wineMemorySharing->sizePolicy().hasHeightForWidth());
        checkBox_wineMemorySharing->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(checkBox_wineMemorySharing);

        checkBox_wineRealTimePriority = new QCheckBox(horizontalFrame_2);
        checkBox_wineRealTimePriority->setObjectName(QString::fromUtf8("checkBox_wineRealTimePriority"));
        sizePolicy1.setHeightForWidth(checkBox_wineRealTimePriority->sizePolicy().hasHeightForWidth());
        checkBox_wineRealTimePriority->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(checkBox_wineRealTimePriority);

        checkBox_wineMemoryOptimization = new QCheckBox(horizontalFrame_2);
        checkBox_wineMemoryOptimization->setObjectName(QString::fromUtf8("checkBox_wineMemoryOptimization"));
        sizePolicy1.setHeightForWidth(checkBox_wineMemoryOptimization->sizePolicy().hasHeightForWidth());
        checkBox_wineMemoryOptimization->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(checkBox_wineMemoryOptimization);

        checkBox_winerunlog = new QCheckBox(horizontalFrame_2);
        checkBox_winerunlog->setObjectName(QString::fromUtf8("checkBox_winerunlog"));
        sizePolicy1.setHeightForWidth(checkBox_winerunlog->sizePolicy().hasHeightForWidth());
        checkBox_winerunlog->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(checkBox_winerunlog);

        checkBox_Gecko = new QCheckBox(horizontalFrame_2);
        checkBox_Gecko->setObjectName(QString::fromUtf8("checkBox_Gecko"));
        sizePolicy1.setHeightForWidth(checkBox_Gecko->sizePolicy().hasHeightForWidth());
        checkBox_Gecko->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(checkBox_Gecko);

        checkBox_Mono = new QCheckBox(horizontalFrame_2);
        checkBox_Mono->setObjectName(QString::fromUtf8("checkBox_Mono"));
        checkBox_Mono->setEnabled(true);
        sizePolicy1.setHeightForWidth(checkBox_Mono->sizePolicy().hasHeightForWidth());
        checkBox_Mono->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(checkBox_Mono);

        checkBox_Ass = new QCheckBox(horizontalFrame_2);
        checkBox_Ass->setObjectName(QString::fromUtf8("checkBox_Ass"));

        horizontalLayout_11->addWidget(checkBox_Ass);

        horizontalLayout_11->setStretch(0, 10);
        horizontalLayout_11->setStretch(1, 10);
        horizontalLayout_11->setStretch(2, 10);
        horizontalLayout_11->setStretch(3, 10);
        horizontalLayout_11->setStretch(4, 10);
        horizontalLayout_11->setStretch(5, 10);
        horizontalLayout_11->setStretch(6, 10);

        verticalLayout_5->addWidget(horizontalFrame_2);

        layoutWidget_2 = new QWidget(tab);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 431, 792, 38));
        horizontalLayout_13 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_13->setSpacing(3);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_5);

        pushButton_Set = new QPushButton(layoutWidget_2);
        pushButton_Set->setObjectName(QString::fromUtf8("pushButton_Set"));
        sizePolicy1.setHeightForWidth(pushButton_Set->sizePolicy().hasHeightForWidth());
        pushButton_Set->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(pushButton_Set);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);

        horizontalLayoutWidget_2 = new QWidget(tab);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 400, 791, 31));
        horizontalLayout_14 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_TipsText = new QLabel(horizontalLayoutWidget_2);
        label_TipsText->setObjectName(QString::fromUtf8("label_TipsText"));
        label_TipsText->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(label_TipsText);

        verticalGroupBox_4 = new QGroupBox(tab);
        verticalGroupBox_4->setObjectName(QString::fromUtf8("verticalGroupBox_4"));
        verticalGroupBox_4->setGeometry(QRect(0, 120, 787, 281));
        verticalLayout_9 = new QVBoxLayout(verticalGroupBox_4);
        verticalLayout_9->setSpacing(1);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(1, 1, 1, 1);
        frame_2 = new QFrame(verticalGroupBox_4);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_2);
        horizontalLayout_8->setSpacing(3);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(1, 1, 1, 1);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_9);

        comboBox_dockSystemVersion = new QComboBox(frame_2);
        comboBox_dockSystemVersion->setObjectName(QString::fromUtf8("comboBox_dockSystemVersion"));

        horizontalLayout_8->addWidget(comboBox_dockSystemVersion);

        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_8->addWidget(label_11);

        comboBox_dockbit = new QComboBox(frame_2);
        comboBox_dockbit->setObjectName(QString::fromUtf8("comboBox_dockbit"));

        horizontalLayout_8->addWidget(comboBox_dockbit);

        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_8->addWidget(label_12);

        comboBox_winebit = new QComboBox(frame_2);
        comboBox_winebit->setObjectName(QString::fromUtf8("comboBox_winebit"));

        horizontalLayout_8->addWidget(comboBox_winebit);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 10);
        horizontalLayout_8->setStretch(2, 1);
        horizontalLayout_8->setStretch(3, 10);
        horizontalLayout_8->setStretch(4, 1);
        horizontalLayout_8->setStretch(5, 10);

        verticalLayout_9->addWidget(frame_2);

        frame_4 = new QFrame(verticalGroupBox_4);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        frame_3 = new QHBoxLayout(frame_4);
        frame_3->setSpacing(0);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(frame_4);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setFocusPolicy(Qt::NoFocus);

        frame_3->addWidget(textEdit);


        verticalLayout_9->addWidget(frame_4);

        verticalLayout_9->setStretch(0, 2);
        verticalLayout_9->setStretch(1, 10);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 160, 787, 71));
        horizontalLayout_6 = new QHBoxLayout(groupBox_4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(label_6);

        lineEdit_otherAgrs = new QLineEdit(groupBox_4);
        lineEdit_otherAgrs->setObjectName(QString::fromUtf8("lineEdit_otherAgrs"));
        sizePolicy1.setHeightForWidth(lineEdit_otherAgrs->sizePolicy().hasHeightForWidth());
        lineEdit_otherAgrs->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(lineEdit_otherAgrs);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 10);
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 787, 156));
        groupBox_3->setMinimumSize(QSize(787, 156));
        groupBox_3->setMaximumSize(QSize(0, 0));
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(3, 3, 3, 3);
        pushButton_setIco = new QPushButton(groupBox_3);
        pushButton_setIco->setObjectName(QString::fromUtf8("pushButton_setIco"));
        sizePolicy.setHeightForWidth(pushButton_setIco->sizePolicy().hasHeightForWidth());
        pushButton_setIco->setSizePolicy(sizePolicy);
        pushButton_setIco->setMinimumSize(QSize(100, 100));

        horizontalLayout_5->addWidget(pushButton_setIco);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_3);

        comboBox_RunWine = new QComboBox(groupBox_3);
        comboBox_RunWine->setObjectName(QString::fromUtf8("comboBox_RunWine"));

        horizontalLayout->addWidget(comboBox_RunWine);

        horizontalLayout->setStretch(0, 13);
        horizontalLayout->setStretch(1, 69);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label);

        lineEdit_AppName = new QLineEdit(groupBox_3);
        lineEdit_AppName->setObjectName(QString::fromUtf8("lineEdit_AppName"));
        sizePolicy1.setHeightForWidth(lineEdit_AppName->sizePolicy().hasHeightForWidth());
        lineEdit_AppName->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit_AppName);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_3->addWidget(label_10);

        lineEdit_MainProcName = new QLineEdit(groupBox_3);
        lineEdit_MainProcName->setObjectName(QString::fromUtf8("lineEdit_MainProcName"));
        sizePolicy1.setHeightForWidth(lineEdit_MainProcName->sizePolicy().hasHeightForWidth());
        lineEdit_MainProcName->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit_MainProcName);

        horizontalLayout_3->setStretch(0, 7);
        horizontalLayout_3->setStretch(1, 21);
        horizontalLayout_3->setStretch(2, 1);
        horizontalLayout_3->setStretch(3, 10);

        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);

        lineEdit_AppInstallExe = new QLineEdit(groupBox_3);
        lineEdit_AppInstallExe->setObjectName(QString::fromUtf8("lineEdit_AppInstallExe"));
        sizePolicy1.setHeightForWidth(lineEdit_AppInstallExe->sizePolicy().hasHeightForWidth());
        lineEdit_AppInstallExe->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(lineEdit_AppInstallExe);

        pushButton_SetAppExe = new QPushButton(groupBox_3);
        pushButton_SetAppExe->setObjectName(QString::fromUtf8("pushButton_SetAppExe"));
        sizePolicy1.setHeightForWidth(pushButton_SetAppExe->sizePolicy().hasHeightForWidth());
        pushButton_SetAppExe->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(pushButton_SetAppExe);

        horizontalLayout_4->setStretch(0, 13);
        horizontalLayout_4->setStretch(1, 55);
        horizontalLayout_4->setStretch(2, 13);

        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(3);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_8);

        lineEdit_workPath = new QLineEdit(groupBox_3);
        lineEdit_workPath->setObjectName(QString::fromUtf8("lineEdit_workPath"));
        sizePolicy1.setHeightForWidth(lineEdit_workPath->sizePolicy().hasHeightForWidth());
        lineEdit_workPath->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(lineEdit_workPath);

        pushButton_workPath = new QPushButton(groupBox_3);
        pushButton_workPath->setObjectName(QString::fromUtf8("pushButton_workPath"));
        sizePolicy1.setHeightForWidth(pushButton_workPath->sizePolicy().hasHeightForWidth());
        pushButton_workPath->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(pushButton_workPath);

        horizontalLayout_9->setStretch(0, 13);
        horizontalLayout_9->setStretch(1, 55);
        horizontalLayout_9->setStretch(2, 13);

        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 1);
        verticalLayout_3->setStretch(3, 1);

        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalLayout_5->setStretch(0, 10);
        horizontalLayout_5->setStretch(1, 50);
        tabWidget->addTab(tab_3, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        groupBox_dxvk = new QGroupBox(tab_6);
        groupBox_dxvk->setObjectName(QString::fromUtf8("groupBox_dxvk"));
        groupBox_dxvk->setGeometry(QRect(0, 0, 787, 61));
        horizontalLayout_10 = new QHBoxLayout(groupBox_dxvk);
        horizontalLayout_10->setSpacing(3);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(3, 3, 3, 3);
        checkBox_stateDxvk = new QCheckBox(groupBox_dxvk);
        checkBox_stateDxvk->setObjectName(QString::fromUtf8("checkBox_stateDxvk"));
        sizePolicy1.setHeightForWidth(checkBox_stateDxvk->sizePolicy().hasHeightForWidth());
        checkBox_stateDxvk->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(checkBox_stateDxvk);

        comboBox_dxvkversion = new QComboBox(groupBox_dxvk);
        comboBox_dxvkversion->setObjectName(QString::fromUtf8("comboBox_dxvkversion"));

        horizontalLayout_10->addWidget(comboBox_dxvkversion);

        checkBox_statedxvkhud = new QCheckBox(groupBox_dxvk);
        checkBox_statedxvkhud->setObjectName(QString::fromUtf8("checkBox_statedxvkhud"));
        sizePolicy1.setHeightForWidth(checkBox_statedxvkhud->sizePolicy().hasHeightForWidth());
        checkBox_statedxvkhud->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(checkBox_statedxvkhud);

        checkBox_dxvkConfigState = new QCheckBox(groupBox_dxvk);
        checkBox_dxvkConfigState->setObjectName(QString::fromUtf8("checkBox_dxvkConfigState"));
        sizePolicy1.setHeightForWidth(checkBox_dxvkConfigState->sizePolicy().hasHeightForWidth());
        checkBox_dxvkConfigState->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(checkBox_dxvkConfigState);

        label_4 = new QLabel(groupBox_dxvk);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(label_4);

        lineEdit_dxvkConfigFIle = new QLineEdit(groupBox_dxvk);
        lineEdit_dxvkConfigFIle->setObjectName(QString::fromUtf8("lineEdit_dxvkConfigFIle"));
        sizePolicy1.setHeightForWidth(lineEdit_dxvkConfigFIle->sizePolicy().hasHeightForWidth());
        lineEdit_dxvkConfigFIle->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(lineEdit_dxvkConfigFIle);

        horizontalLayout_10->setStretch(0, 5);
        horizontalLayout_10->setStretch(1, 12);
        horizontalLayout_10->setStretch(2, 10);
        horizontalLayout_10->setStretch(4, 8);
        horizontalLayout_10->setStretch(5, 25);
        groupBox = new QGroupBox(tab_6);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 60, 787, 401));
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setSpacing(3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(3, 3, 3, 3);
        textEdit_dxvkConfigFileData = new QTextEdit(groupBox);
        textEdit_dxvkConfigFileData->setObjectName(QString::fromUtf8("textEdit_dxvkConfigFileData"));

        verticalLayout_7->addWidget(textEdit_dxvkConfigFileData);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_SaveDxvkConfFile = new QPushButton(groupBox);
        pushButton_SaveDxvkConfFile->setObjectName(QString::fromUtf8("pushButton_SaveDxvkConfFile"));
        sizePolicy1.setHeightForWidth(pushButton_SaveDxvkConfFile->sizePolicy().hasHeightForWidth());
        pushButton_SaveDxvkConfFile->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(pushButton_SaveDxvkConfFile);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_2);

        verticalLayout_7->setStretch(0, 50);
        verticalLayout_7->setStretch(1, 5);
        tabWidget->addTab(tab_6, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalGroupBox = new QGroupBox(tab_4);
        verticalGroupBox->setObjectName(QString::fromUtf8("verticalGroupBox"));
        verticalGroupBox->setGeometry(QRect(0, 0, 787, 457));
        verticalLayout_4 = new QVBoxLayout(verticalGroupBox);
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        tableView_EnvList = new QTableView(verticalGroupBox);
        tableView_EnvList->setObjectName(QString::fromUtf8("tableView_EnvList"));

        verticalLayout_4->addWidget(tableView_EnvList);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalGroupBox_2 = new QGroupBox(tab_5);
        verticalGroupBox_2->setObjectName(QString::fromUtf8("verticalGroupBox_2"));
        verticalGroupBox_2->setGeometry(QRect(0, 0, 787, 457));
        verticalLayout_6 = new QVBoxLayout(verticalGroupBox_2);
        verticalLayout_6->setSpacing(3);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(3, 3, 3, 3);
        tableView_ProcList = new QTableView(verticalGroupBox_2);
        tableView_ProcList->setObjectName(QString::fromUtf8("tableView_ProcList"));

        verticalLayout_6->addWidget(tableView_ProcList);

        tabWidget->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 787, 457));
        verticalLayout_8 = new QVBoxLayout(groupBox_2);
        verticalLayout_8->setSpacing(3);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(3, 3, 3, 3);
        tableView_RegsList = new QTableView(groupBox_2);
        tableView_RegsList->setObjectName(QString::fromUtf8("tableView_RegsList"));

        verticalLayout_8->addWidget(tableView_RegsList);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);


        gridLayout->addWidget(frame_5, 0, 0, 1, 1);


        retranslateUi(vekAppAddMT);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(vekAppAddMT);
    } // setupUi

    void retranslateUi(QWidget *vekAppAddMT)
    {
        vekAppAddMT->setWindowTitle(QCoreApplication::translate("vekAppAddMT", "Vek Game Add&Set", nullptr));
        verticalGroupBox_3->setTitle(QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\345\237\272\347\241\200\345\217\202\346\225\260", nullptr));
        label_7->setText(QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\350\267\257\345\276\204:", nullptr));
        pushButton_SetDockPath->setText(QCoreApplication::translate("vekAppAddMT", "\351\200\211\346\213\251\345\256\271\345\231\250\350\267\257\345\276\204", nullptr));
        label_5->setText(QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\345\220\215:", nullptr));
        pushButton_initDock->setText(QCoreApplication::translate("vekAppAddMT", "\345\210\235\345\247\213\345\214\226\345\256\271\345\231\250", nullptr));
        checkBox_DefaultFonts->setText(QCoreApplication::translate("vekAppAddMT", "\351\273\230\350\256\244\345\255\227\344\275\223", nullptr));
        checkBox_wineMemorySharing->setText(QCoreApplication::translate("vekAppAddMT", "\345\206\205\345\255\230\345\205\261\344\272\253", nullptr));
        checkBox_wineRealTimePriority->setText(QCoreApplication::translate("vekAppAddMT", "\345\256\236\346\227\266\344\274\230\345\205\210\347\272\247", nullptr));
        checkBox_wineMemoryOptimization->setText(QCoreApplication::translate("vekAppAddMT", "\345\244\232\344\273\273\345\212\241\345\206\205\345\255\230\344\274\230\345\214\226", nullptr));
        checkBox_winerunlog->setText(QCoreApplication::translate("vekAppAddMT", "\345\205\263\351\227\255\350\277\220\350\241\214\346\227\245\345\277\227\350\276\223\345\207\272", nullptr));
        checkBox_Gecko->setText(QCoreApplication::translate("vekAppAddMT", "Gecko\347\273\204\344\273\266", nullptr));
        checkBox_Mono->setText(QCoreApplication::translate("vekAppAddMT", "Mono\347\273\204\344\273\266", nullptr));
        checkBox_Ass->setText(QCoreApplication::translate("vekAppAddMT", "\347\246\201\347\224\250\346\226\207\344\273\266\345\205\263\350\201\224", nullptr));
        pushButton_Set->setText(QCoreApplication::translate("vekAppAddMT", "\344\277\235\345\255\230", nullptr));
        label_TipsText->setText(QString());
        verticalGroupBox_4->setTitle(QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\351\253\230\347\272\247\345\217\202\346\225\260->\350\255\246\345\221\212:\346\227\240\347\211\271\346\256\212\351\234\200\346\261\202\350\257\267\345\213\277\344\277\256\346\224\271,\345\234\250\346\234\252\345\256\214\345\205\250\347\220\206\350\247\243\350\257\245\351\200\211\351\241\271\346\227\266\350\257\267\345\213\277\344\277\256\346\224\271", nullptr));
        label_9->setText(QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\347\263\273\347\273\237:", nullptr));
        label_11->setText(QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\347\263\273\347\273\237\347\211\210\346\234\254:", nullptr));
        label_12->setText(QCoreApplication::translate("vekAppAddMT", "wine\346\211\247\350\241\214\347\211\210\346\234\254:", nullptr));
        textEdit->setHtml(QCoreApplication::translate("vekAppAddMT", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft JhengHei UI'; font-size:10.5pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\345\256\271\345\231\250\347\263\273\347\273\237:\344\270\273\350\246\201\347\224\250\344\272\216\350\264\237\350\264\243\350\256\276\347\275\256\345\256\271\345\231\250\347\232\204\347\263\273\347\273\237\347\211\210\346\234\254,\345\275\261\345\223\215\345\210\260\351\203\250\345\210\206\350\277\220\350\241\214\345\272\223\345\256\211\350\243\205</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\350"
                        "\277\220\350\241\214APP\347\263\273\347\273\237:APP\351\200\202\351\205\215\350\277\220\350\241\214\346\227\266\345\200\231\347\232\204\345\256\271\345\231\250\347\211\210\346\234\254\357\274\214\346\257\217\344\270\200\344\270\252APP\345\217\257\350\203\275\345\255\230\345\234\250\350\277\220\350\241\214\347\263\273\347\273\237\347\211\210\346\234\254\347\232\204\345\267\256\345\274\202\357\274\214\350\257\245\345\217\202\346\225\260\344\270\272\345\215\225\344\270\252APP\347\213\254\346\234\211\347\232\204\357\274\214\344\270\215\344\274\232\350\267\237\347\235\200\345\256\271\345\231\250\347\263\273\347\273\237\346\224\271\345\217\230\350\200\214\346\224\271\345\217\230</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\345\256\271\345\231\250\347\263\273\347\273\237\347\211\210\346\234\254:\344\270\273\350\246\201\346\230\257\347\224\250\344\272\216\345\210\244\346\226\255\345\222\214\350\256"
                        "\276\347\275\256\344\275\240\347\232\204\345\256\271\345\231\250\346\230\25732\344\275\215\350\277\230\346\230\25764\344\275\215</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">wine\346\211\247\350\241\214\347\211\210\346\234\254:\344\270\273\350\246\201\346\230\257\347\224\250\346\235\245\350\256\276\347\275\256\344\275\240\350\277\220\350\241\214APP\347\232\204\346\211\200\347\224\250\347\232\204wine\347\232\204\346\211\247\350\241\214\346\226\207\344\273\266\357\274\214\350\277\231\351\207\214\345\210\206\344\270\272wine\345\222\214wine64</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\345\205\263\350"
                        "\201\224\346\200\247\345\257\271\345\272\224\350\257\264\346\230\216\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\345\256\271\345\231\250\347\263\273\347\273\237\347\211\210\346\234\254\344\270\27232\344\275\215(win32):&quot;\345\256\271\345\231\250\347\263\273\347\273\237&quot;\345\222\214&quot;\350\277\220\350\241\214APP\347\263\273\347\273\237&quot;\345\217\257\344\270\272xp win10 win8 win7          \346\211\247\350\241\214wine:\344\273\205wine</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\345\256\271\345\231\250\347\263\273\347\273\237\347\211\210\346\234\254\344\270\27264\344\275\215(win64):&quot;\345\256\271\345\231\250\347\263\273\347\273\237&quot;\345\222\214&quot;\350\277\220\350\241\214APP\347\263\273\347\273\237&quot;\345\217\257\344\270\272xp64"
                        " win10 win8 win7     \346\211\247\350\241\214wine:wine or wine64</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">\345\256\271\345\231\250\351\253\230\347\272\247\345\217\202\346\225\260\344\270\215\345\273\272\350\256\256\344\277\256\346\224\271</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\345\217\202\346\225\260", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("vekAppAddMT", "\350\275\257\344\273\266\351\200\211\351\241\271->\350\257\245\345\212\237\350\203\275\344\270\273\350\246\201\351\222\210\345\257\271\347\211\271\346\256\212\346\203\205\345\206\265\345\220\257\345\212\250\351\231\204\345\212\240\346\214\207\344\273\244\344\273\245\350\276\276\345\210\260\347\273\225\350\277\207\351\203\250\345\210\206\346\243\200\346\265\213\346\210\226\350\200\205\346\262\231\347\233\222\347\232\204\345\212\237\350\203\275", nullptr));
        label_6->setText(QCoreApplication::translate("vekAppAddMT", "\346\211\247\350\241\214\351\231\204\345\212\240\345\221\275\344\273\244:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("vekAppAddMT", "\350\275\257\344\273\266\345\217\202\346\225\260", nullptr));
        pushButton_setIco->setText(QString());
        label_3->setText(QCoreApplication::translate("vekAppAddMT", "\350\277\220\350\241\214\350\275\257\344\273\266Win\347\211\210\346\234\254:", nullptr));
        label->setText(QCoreApplication::translate("vekAppAddMT", "\346\270\270\346\210\217&\350\275\257\344\273\266\345\220\215:", nullptr));
        label_10->setText(QCoreApplication::translate("vekAppAddMT", "\344\270\273\350\277\233\347\250\213\346\226\207\344\273\266\345\220\215:", nullptr));
        label_2->setText(QCoreApplication::translate("vekAppAddMT", "\350\256\276\347\275\256\350\275\257\344\273\266\345\220\257\345\212\250\347\250\213\345\272\217", nullptr));
        pushButton_SetAppExe->setText(QCoreApplication::translate("vekAppAddMT", "\351\200\211\346\213\251\350\267\257\345\276\204", nullptr));
        label_8->setText(QCoreApplication::translate("vekAppAddMT", "\350\256\276\347\275\256\350\275\257\344\273\266\345\267\245\344\275\234\347\233\256\345\275\225:", nullptr));
        pushButton_workPath->setText(QCoreApplication::translate("vekAppAddMT", "\351\200\211\346\213\251\350\267\257\345\276\204", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("vekAppAddMT", "\345\272\224\347\224\250\345\217\202\346\225\260", nullptr));
        groupBox_dxvk->setTitle(QCoreApplication::translate("vekAppAddMT", "Dxvk\350\256\276\347\275\256->\346\233\277\344\273\243windows\345\233\276\345\275\242\346\216\245\345\217\243dx\357\274\214\351\207\207\347\224\250vulkan\345\256\236\347\216\260", nullptr));
        checkBox_stateDxvk->setText(QCoreApplication::translate("vekAppAddMT", "\345\274\200\345\220\257dxvk", nullptr));
        checkBox_statedxvkhud->setText(QCoreApplication::translate("vekAppAddMT", "\345\274\200\345\220\257DXVK HUD", nullptr));
        checkBox_dxvkConfigState->setText(QCoreApplication::translate("vekAppAddMT", "\345\274\200\345\220\257DXVK\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
        label_4->setText(QCoreApplication::translate("vekAppAddMT", "DXVK\351\205\215\347\275\256\346\226\207\344\273\266:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("vekAppAddMT", "DXVK\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
        pushButton_SaveDxvkConfFile->setText(QCoreApplication::translate("vekAppAddMT", "\344\277\235\345\255\230dxvk.conf", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("vekAppAddMT", "DXVK", nullptr));
        verticalGroupBox->setTitle(QCoreApplication::translate("vekAppAddMT", "\347\216\257\345\242\203\345\217\230\351\207\217\345\210\227\350\241\250->\346\255\244\345\210\227\350\241\250\346\234\252\345\215\225\344\270\200\346\211\247\350\241\214\351\231\204\345\212\240\357\274\214\344\270\273\350\246\201\350\247\243\345\206\263\351\203\250\345\210\206\350\275\257\344\273\266\346\210\226\346\270\270\346\210\217\347\211\271\346\256\212\350\246\201\346\261\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("vekAppAddMT", "\347\216\257\345\242\203\345\217\230\351\207\217", nullptr));
        verticalGroupBox_2->setTitle(QCoreApplication::translate("vekAppAddMT", "\351\231\204\345\212\240\350\277\233\347\250\213\345\210\227\350\241\250->\346\255\244\345\210\227\350\241\250\344\270\273\350\246\201\347\224\250\344\272\216\347\256\241\347\220\206\350\277\233\347\250\213\351\200\200\345\207\272\346\234\272\345\210\266\345\246\202\357\274\232\350\205\276\350\256\257WeGame\357\274\214\344\270\273\350\277\233\347\250\213\344\270\272WeGame\351\231\204\345\212\240\350\277\233\347\250\213\344\270\272TASlogin.exe", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("vekAppAddMT", "\351\231\204\345\212\240\350\277\233\347\250\213", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("vekAppAddMT", "\345\256\271\345\231\250\346\263\250\345\206\214\350\241\250->\345\272\224\347\224\250\344\272\216\345\256\271\345\231\250\347\232\204\346\263\250\345\206\214\350\241\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("vekAppAddMT", "\346\263\250\345\206\214\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekAppAddMT: public Ui_vekAppAddMT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKAPPADDMT_H
