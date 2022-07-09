#ifndef VUPDATE_H
#define VUPDATE_H

#include <QWidget>
#include <QDir>
#include "datacurl.h"
#include <QFileInfo>
QT_BEGIN_NAMESPACE
namespace Ui { class vUpdate; }
QT_END_NAMESPACE

class vUpdate : public QWidget
{
    Q_OBJECT

public:
    vUpdate(QWidget *parent = nullptr);
    ~vUpdate(); 
    void GetVerInfo();
    void lableVersionShow(QString);
    void connectOBject();
    QString vUrlLogStr;
    QString vUrlFileStr;
    QString vUrlPassWord;
    QString vUrlFileSHA;
private:
    Ui::vUpdate *ui;
    bool mDragWindow;
    QPoint mMousePoint;
    QThread *obj_Thread=nullptr;
    datacurl* dcurl=nullptr;
    //QString log="https://gitee.com/JackLee02/vekGame/raw/master/upLogs.txt";
    //QString url="https://fancy-brook-66ae.vek.workers.dev/UEK/vek-1.0.1.8.zip";
    int nPos=0;
private:
    void lableLogShow(QString str);
    void downloadFile();
    void controlSatae(bool);
    QString fileHash(QString);
signals:
    void ToThread();
protected:
    void loadStyleSheet(const QString &styleSheetFile);
private slots:
    void on_ButtonClicked();
    void task_ProgressBarShow(long,long,int);
    void upVek();
    void overThread(bool,bool);
};
#endif // VUPDATE_H
