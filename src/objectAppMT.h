#ifndef OBJECTAPPMT_H
#define OBJECTAPPMT_H

#include "objectJson.h"
#include "objectExtend.h"
#include "vekInitObject.h"
class objectAppMT :public QObject
{
    Q_OBJECT
public:
    objectAppMT(BaseAppData*,BaseDockData*);
    ~objectAppMT();
    QString GetRandomCID();
    bool InitDockObj(bool);
    std::vector<QStringList> argsList;
    //写入数据
    void SaveDataToJson(QString dockName,BaseAppData writeData);
    void DockLibsInstall();
    void ExecuteObj(objectType,objectWineBoot,objectWineServer);
    void newDock();
    void optionRegs();
    void sObjectInstall();
private:
    BaseAppData* appData=nullptr;
    BaseDockData* dockData=nullptr;
    void InitDockDir(bool foceState,QDir _dockPath,QDir _dockDir);
    QStringList GetDxvkFileList(QString basedxvkDir);
    void DxvkFileInstall();
    void DxvkRegedit(QStringList dxvkFileList);
    void DxvkHUDRegs();
    void DxvkConfigFile();
    void DefaultFontsFileInstall();
    void DefaultFontsRegs();
    void WaitObjectDone(objectExtend*);  
    void DockEditSystemVersion();
    void addJsonAuto(QString);
    void installMonoPlugs();
    void installGeckoPlugs();
};

#endif // VEKGAMEADDOBJECT_H
