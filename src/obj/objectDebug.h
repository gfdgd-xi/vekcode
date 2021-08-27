#ifndef OBJECTDEBUG_H
#define OBJECTDEBUG_H
#include <QThread>
#include "common.h"
#include "objectExtend.h"
class objectDebug:public QThread
{
    Q_OBJECT
public:   
    explicit objectDebug(QObject *parent = nullptr);
    void setArgs(SdockerData,SappData,QStringList);
    void exitDebug();
protected:
    void run();
private:
    QProcess* xProcess=nullptr;
    QStringList dArgs;
    SappData appData;
    SdockerData dockData;
    void executeArgsEnv();
};

#endif // OBJECTDEBUG_H
