#ifndef OBJECTEXTEND_H
#define OBJECTEXTEND_H

#include "common.h"
#include "objectJson.h"
#include "pObject.h"
#include "objectProcManage.h"

enum SWITCH_SYSTEM_VERSION{
    APP,
    DOCKER
};

enum ExtendType{
    EX_DOCKER,
    EX_APP
};
enum KillArgsType{
    CHECK,
    KILL
};

class objectExtend :public QThread
{
    Q_OBJECT
public:
    explicit objectExtend(QObject *parent = nullptr);
    ~objectExtend();
    QProcess *m_cmd=nullptr;
    void setDockOptionObjectData(SdockerData,QString,std::vector<QStringList>,ExtendArgs ex_type,ExtendType);
protected:
    void run();
private:
    SappData appData;
    SdockerData dockData;
    std::vector<QStringList> argsList;
    ExtendArgs exArgs;
    ExtendType exType;
    QString startArgs;
    void optionExtend();
    void extendAppType();
    void extendApp();
    void executeDockerEnv();
    void baseExecuteWineCode(QString,QStringList);
    void baseExecuteAppCode(QString,QStringList);
    void extendWineRegeditCode(QString);
    void executeWineBoot(Extend_Boot);
    void executeWineServer(Extend_Server);
    void executeWinetricks(ExtendType);
    void executeWinetricks_gui(QStringList);
    void executeWinetricks_cmd_libs(QStringList);
    void ExtendWinetricksCode(QStringList,bool);
    void ExtendForceKill(QString,QStringList);
    void waitObjectDone(bool);
    void hqSwitchSysVersion(SWITCH_SYSTEM_VERSION ssv);
    void SwitchSysVerion(SWITCH_SYSTEM_VERSION ssv);
    void extendPlugs();
    void forceKill();
    void forceAllKill();
    SappProcData forceKillArgs(SappProcData,KillArgsType);
    void dyncDxvkRegs(std::map<QString,std::map<QString,QString>>);
signals:
    void objexitTray(bool);
};

#endif // VEKSTARTOPTINOBJECT_H
