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
}SRegs;

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
    std::vector<SRegs> stdDockerRegs={};
}SappData;

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
}SwineData;

//远程wine数据结构
typedef struct {
    QString WineName=nullptr;
    QString WineVersion=nullptr;
    QString WineGit=nullptr;
    QString Mono=nullptr;
    QString GeckoX86=nullptr;
    QString GeckoX86_64=nullptr;
    std::vector<QString> WineDxvk={};
}SwineRemoteData;

typedef struct {
    QString pDockPath=nullptr;
    QString pDockName=nullptr;
    QString pWinePath=nullptr;
    QString pMainProc=nullptr;
    std::vector<QString> pAttachProc={};
}SappProcData;

typedef struct {
    std::map<QString,QString> Option={};
    std::map<QString,QString> Docker={};
    std::vector<QString> AttachProc={};
    std::map<QString,QString> Env={};
    std::vector<QString> Libs={};
    std::map<QString,QString> Dxvk={};
    std::vector<SRegs> Regs={};
    QString Args=nullptr;
}SappDeployData;

typedef struct{
    QString appName=nullptr;
    QString appJson=nullptr;
    QString appIco=":/res/img/vek.ico";
}SappDeployInfo;

typedef struct{
    std::map<QString,SappData> dData;
    QString WinePath=nullptr;
    QString WineVersion=nullptr;
    QString DockerPath=nullptr;
    QString DockerName="vekON1";
    QString DockerSystemVersion="win7";
    QString DockerWineVersion="wine";
    QString DockerVer="win32";
    bool MonoState=false;
    bool GeckoState=false;
}SdockerData;

typedef struct{
    QString vekStyle="styleDefault";
    QString vekLang="langChinese";
}SvekOptions;

typedef struct {
    std::map<QString,SdockerData> dockerVec={};
    std::map<QString,SwineData> wineVec={};
    std::map<QString,QString> appScrSource={};
    std::map<QString,std::map<QString,std::map<QString,SappDeployInfo>>> appJsonList={};
    std::map<QString,QString> wineSource={};
    std::map<QString,std::map<QString,SwineRemoteData>> wineJsonList={};
    SvekOptions vekOptions={};
}SlocalGloablData;

typedef struct{
    std::map<QString,QString> wtServer={};
}BaseWtServer;

typedef enum{
    object_winecfg,
    object_regedit,
    object_control,
    object_uninstall,
    object_winetricks_gui,
    object_winetricks_cmd_libs,
    object_start,
    object_debugstart,
    object_setgame,
    object_exportJson,
    object_packageDeb,
    object_forcekill,
    object_deletegame,
    object_regobject,
    object_wineboot,
    object_wineserver,
    object_dockSysver,
    object_disable,
    object_plugs,
    object_default
}ExtendType;
typedef enum{
    object_wineboot_e,
    object_wineboot_f,
    object_wineboot_i,
    object_wineboot_k,
    object_wineboot_r,
    object_wineboot_s,
    object_wineboot_u,
    object_wineboot_default
}ExtendBootType;
typedef enum{
    object_wineserver_k,
    object_wineserver_p,
    object_wineserver_w,
    object_wineserver_default
}ExtendServerType;
typedef enum{
    object_delApp,
    object_setApp,
    object_addApp
}EADEType;
extern SlocalGloablData g_vekLocalData;
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
