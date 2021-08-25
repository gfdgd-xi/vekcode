#ifndef VEKMESSAGE_H
#define VEKMESSAGE_H
#include <QWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QKeyEvent>

class vekMessage : public QWidget
{
    Q_OBJECT
    bool is_finished;

    QTextBrowser *browser;
    QPushButton * start_button ;
    QPushButton * clear_button;
public:
    explicit vekMessage(QWidget *parent = nullptr);
    void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
public:
    void start();
signals:

};

#endif // VEKMESSAGE_H
