#ifndef OBJECTADDGAMEMT_H
#define OBJECTADDGAMEMT_H

#include "objectJson.h"
#include "objectExtend.h"
#include "vekInitObject.h"
class objectAddGameMT :public QObject
{
    Q_OBJECT
public:
    objectAddGameMT(BaseGameData*,BaseGameData*);
    ~objectAddGameMT();
    QString GetRandomCID();
    bool InitDockObj(bool);
    std::vector<QStringList> argsList;
    //写入数据
    void SaveDataToJson(QString dockName,BaseGameData writeData);
    void DockLibsInstall();
    void ExecuteObj(objectType,objectWineBoot,objectWineServer);
    void newDock();
    void optionRegs();
private:
    BaseGameData* _baseGameData=nullptr;
    BaseGameData* _oldGameData=nullptr;   
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
    void ExecutetoObjectArgs(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);

};

#endif // VEKGAMEADDOBJECT_H
