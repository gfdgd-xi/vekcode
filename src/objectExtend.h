#ifndef OBJECTEXTEND_H
#define OBJECTEXTEND_H

#include "common.h"
#include "objectJson.h"
#include <QTextCodec>
#include "vekInitObject.h"
#include "objectProcManage.h"
#include "vekInitObject.h"
class objectExtend :public QThread
{
    Q_OBJECT
public:
    explicit objectExtend(QObject *parent = nullptr);
    ~objectExtend();
    QProcess *m_cmd=nullptr;
    void setDockOptionObjectData(BaseDockData,QString,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);
protected:
    void run();
private:
    BaseAppData appData;
    BaseDockData dockData;
    std::vector<QStringList> argsList;
    objectType objType;
    objectWineBoot objWineBootType;
    objectWineServer objWineServer;
    QString startArgs;
    void optionExtend();
    void extendApp();
    void executeArgsEnv();
    void baseExecuteWineCode(QString,QStringList);
    void baseExecuteAppCode(QString,QStringList);
    void extendWineRegeditCode(QString);
    void executeWineBoot(objectWineBoot);
    void executeWineServer(objectWineServer);
    void executeWinetricks();
    void executeWinetricksLibs();
    void waitObjectDone(bool);
    void dockEditSystemVersion();
    void appEditSystemVersion();
    void extendPlugs();
    void monitorProc();
    void forcekill();
    void dyncDxvkRegs(std::map<QString,std::map<QString,QString>>);
signals:
    void objexitTray(bool);
};

#endif // VEKSTARTOPTINOBJECT_H
