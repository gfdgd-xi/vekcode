#ifndef VUPDATE_H
#define VUPDATE_H

#include <QWidget>
#include <QDir>

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
private:
    Ui::vUpdate *ui;
    bool mDragWindow;
    QPoint mMousePoint;
    //="https://gitee.com/JackLee02/vekGame/raw/master/upLogs.txt";
    //="https://JackLee_CN.coding.net/api/share/download/c155f744-7aba-4a31-95a9-d28cd4e5b39b";
    int nPos=0;
private:
    void lableLogShow(QString str);
    void downloadFile();
signals:
    void ToThread();
protected:
    void loadStyleSheet(const QString &styleSheetFile);
private slots:
    void on_ButtonClicked();
    void task_ProgressBarShow(long,long,int);
    void runVek();
};
#endif // VUPDATE_H
