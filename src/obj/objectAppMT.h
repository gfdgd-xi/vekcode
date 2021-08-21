#ifndef OBJECTAPPMT_H
#define OBJECTAPPMT_H

#include "objectJson.h"
#include "objectExtend.h"
#include "pObject.h"

typedef enum{
    CHANGETYPEDOCKER,
    CHANGETYPTEAPP
}CHANGETYPE;
class objectAppMT :public QObject
{
    Q_OBJECT
public:
    objectAppMT(SdockerData*,SappData*);
    ~objectAppMT();
    QString GetRandomCID();
    bool InitDocker(bool);
    std::vector<QStringList> argsList;
    void DockLibsInstall();
    void changeSettings(CHANGETYPE);
    void optionRegs();
    void InstallDXVK();
private:
    SappData* appData=new SappData;
    SdockerData* dockData=new SdockerData;
    void InitDockDir(bool foceState,QDir _dockPath,QDir _dockDir);
    QStringList GetDxvkFileList(QString basedxvkDir);
    void DxvkFileInstall();
    void DxvkRegedit(QStringList dxvkFileList);
    void DxvkHUDRegs();
    void s_dxvk_config_file();
    void DefaultFontsFileInstall(CHANGETYPE _type);
    void DefaultFontsRegs();
    void WaitObjectDone(objectExtend*);  
    void DockEditSystemVersion();
    void addJsonAuto(QString);
    void installMonoPlugs();
    void installGeckoPlugs();
    void outAppIco();
    void ExecuteObject(ExtendArgs ex_Args,ExtendType ex_Type);
    void b_disable_ass(std::map<QString,std::map<QString,QString>>);
};

#endif // VEKGAMEADDOBJECT_H
