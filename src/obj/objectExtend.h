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
enum SWITCH_WINE_SYSTEM_VERSION{
    WINEHQ,
    DEEPIN
};

class objectExtend :public QThread
{
    Q_OBJECT
public:
    explicit objectExtend(QObject *parent = nullptr);
    ~objectExtend();
    QProcess *m_cmd=nullptr;
    void setDockOptionObjectData(DockData,QString,std::vector<QStringList>,OBJTYPE,BOOTTYPE,SERVERTYPE);
protected:
    void run();
private:
    AppData appData;
    DockData dockData;
    std::vector<QStringList> argsList;
    OBJTYPE objType;
    BOOTTYPE objWineBootType;
    SERVERTYPE objWineServer;
    QString startArgs;
    void optionExtend();
    void extendApp();
    void executeArgsEnv();
    void baseExecuteWineCode(QString,QStringList);
    void baseExecuteAppCode(QString,QStringList);
    void extendWineRegeditCode(QString);
    void executeWineBoot(BOOTTYPE);
    void executeWineServer(SERVERTYPE);
    void executeWinetricks(OBJTYPE);
    void executeWinetricks_gui(QStringList);
    void executeWinetricks_cmd_libs(QStringList);
    void ExtendWinetricksCode(QStringList,bool);
    void switchSysVersion(SWITCH_SYSTEM_VERSION,SWITCH_WINE_SYSTEM_VERSION);
    void waitObjectDone(bool);
    void hqSwitchSysVersion(SWITCH_SYSTEM_VERSION ssv);
    void deepinSwitchSysVerion(SWITCH_SYSTEM_VERSION ssv);
    void extendPlugs();
    void monitorProc();
    void forcekill();
    void dyncDxvkRegs(std::map<QString,std::map<QString,QString>>);
signals:
    void objexitTray(bool);
};

#endif // VEKSTARTOPTINOBJECT_H
