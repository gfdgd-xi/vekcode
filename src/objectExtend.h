#ifndef OBJECTEXTEND_H
#define OBJECTEXTEND_H

#include "common.h"
#include "objectJson.h"
#include <QTextCodec>
#include "vekInitObject.h"
#include "objectProcManage.h"
class objectExtend :public QThread
{
    Q_OBJECT
public:
    explicit objectExtend(QObject *parent = nullptr);
    ~objectExtend();
    QProcess *m_cmd=nullptr;
protected:
    void run();
private:
    BaseAppData data;
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
    void extendPlugs();
    void monitorProc();
    void forcekill();
    void dyncDxvkRegs(std::map<QString,std::map<QString,QString>>);
private slots:
    void setDockOptionObjectData(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);
signals:
    void objexitTray(bool);
};

#endif // VEKSTARTOPTINOBJECT_H
