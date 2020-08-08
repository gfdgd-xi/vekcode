#ifndef OBJECTAPPADDGAMEMT_H
#define OBJECTAPPADDGAMEMT_H

#include "objectJson.h"
#include "objectExtend.h"
#include "vekInitObject.h"
class objectAppAddMT :public QObject
{
    Q_OBJECT
public:
    objectAppAddMT(BaseAppData*,BaseAppData*);
    ~objectAppAddMT();
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
    BaseAppData* _BaseAppData=nullptr;
    BaseAppData* _oldAppData=nullptr;
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
signals:
    void ExecutetoObjectArgs(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);

};

#endif // VEKGAMEADDOBJECT_H
