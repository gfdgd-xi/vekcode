#ifndef BASEDATA_H
#define BASEDATA_H

#include <QString>
#include <iostream>
#include <map>
#include <vector>
typedef struct{
    QString rPath=nullptr;
    QString rKey=nullptr;
    QString rTValue=nullptr;
    QString rValue=nullptr;
}BaseDockRegs;

typedef struct {
    QString AppCID=nullptr;
    QString AppName=nullptr;
    QString AppIco=":/res/img/vek.ico";
    QString AppExe=nullptr;
    QString AppOtherAgrs=nullptr;
    QString WorkPath=nullptr;
    QString DxvkVerson=nullptr;
    QString DxvkConfigFile=nullptr;
    QString MainPrcoName=nullptr;
    QString DockSysVersion=nullptr;
    bool DxvkState=false;
    bool DxvkHUD=false;
    bool DxvkConfigFileState=false;
    bool TaskLog=false;
    bool WriteCopy=false;
    bool SharedMemory=false;
    bool RtServer=false;
    bool DefaultFonts=false;
    bool DisableAss=false;
    std::vector<QString> AttachProc={};
    std::map<QString,QString> DockerEnv={};
    std::vector<QString> DockerLibs={};
    std::vector<BaseDockRegs> DockerRegs={};
}BaseAppData;

//本地安装wine数据结构
typedef struct{
    QString IwineName=nullptr;
    QString IwineVer=nullptr;
    QString IwinePath=nullptr;
    QString IwineUrl=nullptr;
    QString IwineSrc=nullptr;
    QString IwineMono=nullptr;
    QString IwineGeckoX86=nullptr;
    QString IwineGeckoX86_64=nullptr;
    std::vector<QString> IwineDxvk={};
}BaseWineData;

//远程wine数据结构
typedef struct {
    QString WineName=nullptr;
    QString WineVersion=nullptr;
    QString WineGit=nullptr;
    QString Mono=nullptr;
    QString GeckoX86=nullptr;
    QString GeckoX86_64=nullptr;
    std::vector<QString> WineDxvk={};
}BaseWineGit;

typedef struct {
    QString pDockPath=nullptr;
    QString pDockName=nullptr;
    QString pWinePath=nullptr;
    QString pMainProc=nullptr;
    std::vector<QString> pAttachProc={};
}procInfo;

typedef struct {
    std::map<QString,QString> Option={};
    std::map<QString,QString> Docker={};
    std::vector<QString> AttachProc={};
    std::map<QString,QString> Env={};
    std::vector<QString> Libs={};
    std::map<QString,QString> Dxvk={};
    std::vector<BaseDockRegs> Regs={};
    QString Args=nullptr;
}BaseAutoSetJson;

typedef struct{
    QString appName=nullptr;
    QString appJson=nullptr;
    QString appIco=":/res/img/vek.ico";
}BaseAppJson;

typedef struct{
    std::map<QString,BaseAppData> dData;
    QString WinePath=nullptr;
    QString WineVersion=nullptr;
    QString DockerPath=nullptr;
    QString DockerName="vekON1";
    QString DockerSystemVersion="win7";
    QString DockerWineVersion="wine";
    QString DockerVer="win32";
    bool MonoState=false;
    bool GeckoState=false;
}BaseDockData;

typedef struct {
    std::map<QString,BaseDockData> dockerVec={};
    std::map<QString,BaseWineData> wineVec={};
    std::map<QString,QString> appScrSource={};
    //std::map<QString,std::map<QString,QString>> appJsonList={};
    std::map<QString,std::map<QString,std::map<QString,BaseAppJson>>> appJsonList={};
    std::map<QString,QString> wineSource={};
    std::map<QString,std::map<QString,BaseWineGit>> wineJsonList={};
}BaseLocalData;
typedef enum{
    object_winecfg,
    object_regedit,
    object_control,
    object_uninstall,
    object_winetricks_gui,
    object_start,
    object_debugstart,
    object_setgame,
    object_exportJson,
    object_forcekill,
    object_deletegame,
    object_regobject,
    object_wineboot,
    object_wineserver,
    object_dockSysver,
    object_disable,
    object_winetricks_libs,
    object_plugs,
    object_default
}objectType;
typedef enum{
    object_wineboot_e,
    object_wineboot_f,
    object_wineboot_i,
    object_wineboot_k,
    object_wineboot_r,
    object_wineboot_s,
    object_wineboot_u,
    object_wineboot_default
}objectWineBoot;
typedef enum{
    object_wineserver_k,
    object_wineserver_p,
    object_wineserver_w,
    object_wineserver_default
}objectWineServer;
typedef enum{
    object_delApp,
    object_setApp,
    object_addApp
}objectTypeView;
extern BaseLocalData g_vekLocalData;
extern std::map<QString,std::map<QString,QString>> fontRes;
extern std::map<QString,std::map<QString,QString>> dxvkResCof;
extern std::map<QString,std::map<QString,QString>> dxvkResHUD;
extern std::map<QString,std::map<QString,QString>> winebuilder;
extern std::map<QString,std::map<QString,QString>> winemine;
extern std::map<QString,std::map<QString,QString>> dxvkRes;
extern std::map<QString,std::map<QString,QString>> dxvkResCache;
extern std::map<QString,std::map<QString,QString>> dxvkResLog;
extern std::vector<QString> taskList;
#endif // BASEDATA_H
