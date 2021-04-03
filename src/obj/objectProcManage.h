#ifndef OBJECTPROCMANAGE_H
#define OBJECTPROCMANAGE_H

#include "common.h"
#include <QMutex>

class objectProcManage:public QThread
{
    Q_OBJECT
public:
   explicit objectProcManage(QObject *parent = nullptr);
    SappProcData iprocInfo;
    ~objectProcManage();    
protected:
    void run();
private:
    QProcess *m_cmd=nullptr;
    QProcess *prc=nullptr;
    //所有当前运行的程序容器的进程列表的表
    std::map<QString,QString> procAllInfoStr;
    void getAllProc();
    QString objGetProcList(SappProcData);
    void objWineHQKillProc(QString,SappProcData);
    void objKillProc(QString prPid);
    void delAttachProc(SappProcData pInfo);
    void objDeepinKillProc(QString,SappProcData);
};

#endif // OBJECTPROCMANAGE_H
