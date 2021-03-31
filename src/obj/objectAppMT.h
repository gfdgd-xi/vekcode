#ifndef OBJECTAPPMT_H
#define OBJECTAPPMT_H

#include "objectJson.h"
#include "objectExtend.h"
#include "pObject.h"
class objectAppMT :public QObject
{
    Q_OBJECT
public:
    objectAppMT(SappData*,SdockerData*);
    ~objectAppMT();
    QString GetRandomCID();
    bool InitDockObj(bool);
    std::vector<QStringList> argsList;
    void DockLibsInstall();
    void ExecuteObj(ExtendType,ExtendBootType,ExtendServerType);
    void newDock();
    void optionRegs();
    void sObjectInstall();
private:
    SappData* appData=new SappData;
    SdockerData* dockData=new SdockerData;
    void InitDockDir(bool foceState,QDir _dockPath,QDir _dockDir);
    QStringList GetDxvkFileList(QString basedxvkDir);
    void DxvkFileInstall();
    void DxvkRegedit(QStringList dxvkFileList);
    void DxvkHUDRegs();
    void s_dxvk_config_file();
    void DefaultFontsFileInstall();
    void DefaultFontsRegs();
    void WaitObjectDone(objectExtend*);  
    void DockEditSystemVersion();
    void addJsonAuto(QString);
    void installMonoPlugs();
    void installGeckoPlugs();
    void outAppIco();
    void b_disable_ass(std::map<QString,std::map<QString,QString>>);
};

#endif // VEKGAMEADDOBJECT_H
