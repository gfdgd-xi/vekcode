/********************************************************************************
** Form generated from reading UI file 'vekAbout.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEKABOUT_H
#define UI_VEKABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vekAbout
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *verticalTabWidget;
    QWidget *TabWidgetPage3;
    QVBoxLayout *verticalLayout2;
    QTextEdit *textEdit4;
    QWidget *TabWidgetPageA;
    QVBoxLayout *verticalLayout21;
    QTextEdit *textEdit2;
    QWidget *TabWidgetPage3_1;
    QVBoxLayout *verticalLayout3;
    QTextEdit *textEdit3;
    QWidget *TabWidgetPage21;
    QVBoxLayout *verticalLayout1;
    QTextEdit *textEdit1;
    QWidget *TabWidgetPage6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout4;
    QTextEdit *textEdit_2;

    void setupUi(QDialog *vekAbout)
    {
        if (vekAbout->objectName().isEmpty())
            vekAbout->setObjectName(QString::fromUtf8("vekAbout"));
        vekAbout->setWindowModality(Qt::NonModal);
        vekAbout->resize(500, 420);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vekAbout->sizePolicy().hasHeightForWidth());
        vekAbout->setSizePolicy(sizePolicy);
        vekAbout->setMinimumSize(QSize(500, 420));
        vekAbout->setMaximumSize(QSize(500, 420));
        verticalLayout_3 = new QVBoxLayout(vekAbout);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        verticalTabWidget = new QTabWidget(vekAbout);
        verticalTabWidget->setObjectName(QString::fromUtf8("verticalTabWidget"));
        TabWidgetPage3 = new QWidget();
        TabWidgetPage3->setObjectName(QString::fromUtf8("TabWidgetPage3"));
        verticalLayout2 = new QVBoxLayout(TabWidgetPage3);
        verticalLayout2->setSpacing(1);
        verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
        verticalLayout2->setContentsMargins(1, 1, 1, 1);
        textEdit4 = new QTextEdit(TabWidgetPage3);
        textEdit4->setObjectName(QString::fromUtf8("textEdit4"));
        textEdit4->setFocusPolicy(Qt::NoFocus);

        verticalLayout2->addWidget(textEdit4);

        verticalTabWidget->addTab(TabWidgetPage3, QString());
        TabWidgetPageA = new QWidget();
        TabWidgetPageA->setObjectName(QString::fromUtf8("TabWidgetPageA"));
        verticalLayout21 = new QVBoxLayout(TabWidgetPageA);
        verticalLayout21->setSpacing(1);
        verticalLayout21->setObjectName(QString::fromUtf8("verticalLayout21"));
        verticalLayout21->setContentsMargins(1, 1, 1, 1);
        textEdit2 = new QTextEdit(TabWidgetPageA);
        textEdit2->setObjectName(QString::fromUtf8("textEdit2"));
        textEdit2->setFocusPolicy(Qt::NoFocus);

        verticalLayout21->addWidget(textEdit2);

        verticalTabWidget->addTab(TabWidgetPageA, QString());
        TabWidgetPage3_1 = new QWidget();
        TabWidgetPage3_1->setObjectName(QString::fromUtf8("TabWidgetPage3_1"));
        verticalLayout3 = new QVBoxLayout(TabWidgetPage3_1);
        verticalLayout3->setSpacing(1);
        verticalLayout3->setObjectName(QString::fromUtf8("verticalLayout3"));
        verticalLayout3->setContentsMargins(1, 1, 1, 1);
        textEdit3 = new QTextEdit(TabWidgetPage3_1);
        textEdit3->setObjectName(QString::fromUtf8("textEdit3"));
        textEdit3->setFocusPolicy(Qt::NoFocus);

        verticalLayout3->addWidget(textEdit3);

        verticalTabWidget->addTab(TabWidgetPage3_1, QString());
        TabWidgetPage21 = new QWidget();
        TabWidgetPage21->setObjectName(QString::fromUtf8("TabWidgetPage21"));
        verticalLayout1 = new QVBoxLayout(TabWidgetPage21);
        verticalLayout1->setSpacing(1);
        verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
        verticalLayout1->setContentsMargins(1, 1, 1, 1);
        textEdit1 = new QTextEdit(TabWidgetPage21);
        textEdit1->setObjectName(QString::fromUtf8("textEdit1"));
        textEdit1->setFocusPolicy(Qt::NoFocus);

        verticalLayout1->addWidget(textEdit1);

        verticalTabWidget->addTab(TabWidgetPage21, QString());
        TabWidgetPage6 = new QWidget();
        TabWidgetPage6->setObjectName(QString::fromUtf8("TabWidgetPage6"));
        verticalLayout_4 = new QVBoxLayout(TabWidgetPage6);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(1, 1, 1, 1);
        verticalLayout4 = new QVBoxLayout();
        verticalLayout4->setObjectName(QString::fromUtf8("verticalLayout4"));
        textEdit_2 = new QTextEdit(TabWidgetPage6);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setFocusPolicy(Qt::NoFocus);

        verticalLayout4->addWidget(textEdit_2);


        verticalLayout_4->addLayout(verticalLayout4);

        verticalTabWidget->addTab(TabWidgetPage6, QString());

        verticalLayout_3->addWidget(verticalTabWidget);


        retranslateUi(vekAbout);

        verticalTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(vekAbout);
    } // setupUi

    void retranslateUi(QDialog *vekAbout)
    {
        vekAbout->setWindowTitle(QCoreApplication::translate("vekAbout", "\347\273\274\345\220\210\344\277\241\346\201\257", nullptr));
        textEdit4->setHtml(QCoreApplication::translate("vekAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans CJK SC'; font-size:10.5pt;\"><br /></p></body></html>", nullptr));
        verticalTabWidget->setTabText(verticalTabWidget->indexOf(TabWidgetPage3), QCoreApplication::translate("vekAbout", "\346\227\245\345\270\270\345\205\254\345\221\212", nullptr));
        textEdit2->setHtml(QCoreApplication::translate("vekAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">\344\275\277\347\224\250\346\225\231\347\250\213</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">VEK\344\275\277\347\224\250\350\247\206\351\242\221\346\225\231\347\250\213:https://www.bilibili.com/video/BV1pt4y1X7tx/</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">VEK Wine\346\272\220\345\210\266\344\275\234\346\225\231\347\250\213\357\274\232ht"
                        "tps://www.bilibili.com/video/BV1ki4y1G7zh/</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">winetricks\344\270\213\350\275\275\351\200\237\345\272\246\346\205\242(\344\270\273\350\246\201\351\227\256\351\242\230\346\230\257IPV6\345\257\274\350\207\264\347\232\204):</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\346\226\271\346\241\210\344\270\200(\344\270\264\346\227\266)\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1</p>\n"
"<p style=\" margin-top:0px; margi"
                        "n-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">sudo sysctl -w net.ipv6.conf.lo.disable_ipv6=1</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\226\271\346\241\210\344\272\214\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\234\250deepin\346\210\226\350\200\205uos\347\275\221\347\273\234\350\256\276\347\275\256\351\207\214\351\235\242\346\212\212IPV6\350\256\276\347\275\256\346\210\220\345\277\275\347\225\245</p></body></html>", nullptr));
        verticalTabWidget->setTabText(verticalTabWidget->indexOf(TabWidgetPageA), QCoreApplication::translate("vekAbout", "\344\275\277\347\224\250\351\241\273\347\237\245", nullptr));
        textEdit3->setHtml(QCoreApplication::translate("vekAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0055:err:vulkan:wine_vk_init Failed to load libvulkan.so.1.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0055:err:vulkan:wine_vk_init Failed to load Wine graphics driver supporting Vulkan.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350"
                        "\247\243\345\206\263\346\226\271\346\241\210\357\274\232sudo apt install libvulkan1 libvulkan1:i386</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ODBC_LoadDriverManager failed to open library &quot;libodbc.so&quot;</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\247\243\345\206\263\346\226\271\346\241\210:sudo apt install unixodbc</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">002d:err:wincodecs:JpegDecoder_CreateInstance Failed reading JPEG because unable to find libjpeg.so.62</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\247\243\345\206\263\346\226\271\346\241\210:sudo apt-get install libjpeg62 libjpeg62:i386</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">err:module:load_builtin_dll failed to load .so lib for builtin L&quot;winex11.drv&quot;: libSM.so.6: cannot open shared object file: No such file or directory"
                        "</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\247\243\345\206\263\346\226\271\346\241\210:sudo apt install libsm6:i386</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">err:winediag:SECUR32_initNTLMSP ntlm_auth was not found or is outdated. Make sure that ntlm_auth 3.0.25 is in your path. Usually, you can find it in the winbind package of your distribution.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p sty"
                        "le=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\247\243\345\206\263\346\226\271\346\241\210\357\274\232sudo apt install winbind</p></body></html>", nullptr));
        verticalTabWidget->setTabText(verticalTabWidget->indexOf(TabWidgetPage3_1), QCoreApplication::translate("vekAbout", "\351\224\231\350\257\257\350\247\243\345\206\263\346\214\207\345\215\227", nullptr));
        textEdit1->setHtml(QCoreApplication::translate("vekAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">\345\256\230\346\226\271\347\275\221\347\253\231:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">https://ptzqqc.coding-pages.com</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-"
                        "right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">Vek\346\272\220\347\240\201\345\234\260\345\235\200:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">https://jacklee_cn.coding.net/public/vekcode/vekcode</span><span style=\" font-family:'Sans'; color:#000000; background-color:#ffffff;\">/git/files</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; color:#00"
                        "0000; background-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">Vek\347\213\254\347\253\213\346\233\264\346\226\260\347\250\213\345\272\217\346\272\220\347\240\201\345\234\260\345\235\200:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">https://jacklee_cn.coding.net/public/vekUpdate/vekUpdate</span><span style=\" font-family:'Sans'; color:#000000; background-color:#ffffff;\">/git/files</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; color:#000000; background"
                        "-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">deepin-wine5\346\211\230\347\256\241\345\234\260\345\235\200:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">https://jacklee_cn.coding.net/public/vekDeepinWine/vekDeepinWine</span><span style=\" font-family:'Sans'; color:#000000; background-color:#ffffff;\">/git/files</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; color:#000000; background-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bot"
                        "tom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">WineHQ\346\211\230\347\256\241\345\234\260\345\235\200:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">https://jacklee_cn.coding.net/public/wineVekDev/wineVekDev</span><span style=\" font-family:'Sans'; color:#000000; background-color:#ffffff;\">/git/files</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; color:#000000; background-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; ba"
                        "ckground-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">Vek\346\225\260\346\215\256\346\211\230\347\256\241\345\234\260\345\235\200:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Sans'; font-size:8pt; color:#000000; background-color:#ffffff;\">https://gitee.com/JackLee02/vekGame</span></p></body></html>", nullptr));
        verticalTabWidget->setTabText(verticalTabWidget->indexOf(TabWidgetPage21), QCoreApplication::translate("vekAbout", "\345\274\200\346\272\220\344\277\241\346\201\257", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("vekAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/res/img/vek.ico\" /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\275\257\344\273\266\345\205\250\345\220\215:VEK\351\205\215\347\275\256\345\271\263\345\217\260</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\344\275\234\350\200\205:JackLee (QQ:809262979 EMAIL:809262979@qq.com)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0"
                        "px; -qt-block-indent:0; text-indent:0px;\">BUG\345\217\215\351\246\210:QQ\347\276\244(701625534)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\274\200\345\217\221\350\275\257\344\273\266:QT5.14.2</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\254\254\344\270\211\346\226\271\345\272\223:curl </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                   nlohmann json</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                   libgit2</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\224\257\346\214\201\345\271\263\345\217\260:Deepin Linux V20</p>\n"
"<p align=\"center\" style=\" margin-"
                        "top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\205\215\350\264\243\347\224\263\346\230\216</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\234\254\350\275\257\344\273\266\344\273\205\344\276\233\345\255\246\344\271\240\344\275\277\347\224\250\357\274\214\345\246\202\345\210\251\347\224\250\346\234\254\350\275\257\344\273\266\346\272\220\344\273\243\347\240\201\347\233\210\345\210\251\346\234\252\347\273\217\350\277\207\346\234\254\344\272\272\345\220\214\346\204\217\351\235\236\346\263\225\344\275\277\347\224\250\350\200\205\346\211\200\345\271\266\345\257\274\350\207\264\347\232\204\344\273\273\344\275\225\346\260\221\344\272\213\345\222\214\345\210\221\344\272\213\346\263\225\345\276\213\347\272\240\347\272\267\346\234\254\344\275\234\350\200\205\344\270\215\346\211\277\346\213\205\344\273\273\344\275\225\346\263\225\345\276\213\350\264\243\344\273"
                        "\273</p></body></html>", nullptr));
        verticalTabWidget->setTabText(verticalTabWidget->indexOf(TabWidgetPage6), QCoreApplication::translate("vekAbout", "\345\205\263\344\272\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vekAbout: public Ui_vekAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEKABOUT_H
