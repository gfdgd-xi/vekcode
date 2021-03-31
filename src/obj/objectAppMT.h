#ifndef OBJECTAPPMT_H
#define OBJECTAPPMT_H

#include "objectJson.h"
#include "objectExtend.h"
#include "pObject.h"
class objectAppMT :public QObject
{
    Q_OBJECT
public:
    objectAppMT(AppData*,DockData*);
    ~objectAppMT();
    QString GetRandomCID();
    bool InitDockObj(bool);
    std::vector<QStringList> argsList;
    void DockLibsInstall();
    void ExecuteObj(OBJTYPE,BOOTTYPE,SERVERTYPE);
    void newDock();
    void optionRegs();
    void sObjectInstall();
private:
    AppData* appData=new AppData;
    DockData* dockData=new DockData;
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
    void outAppIco();
    void DisableAss(std::map<QString,std::map<QString,QString>>);
};

#endif // VEKGAMEADDOBJECT_H
