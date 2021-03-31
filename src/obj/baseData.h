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
}regs;

typedef struct {
    QString app_CID=nullptr;
    QString app_Name=nullptr;
    QString app_ICO=":/res/img/vek.ico";
    QString app_Exe=nullptr;
    QString app_AgrsCode=nullptr;
    QString app_WorkPath=nullptr;
    QString app_DxvkVersion=nullptr;
    QString app_DxvkConfig=nullptr;
    QString app_MainProcName=nullptr;
    QString app_SystemVersion=nullptr;
    bool app_DxvkState=false;
    bool app_DxvkHUD=false;
    bool app_DxvkConfigFileState=false;
    bool app_TaskLog=false;
    bool app_WriteCopy=false;
    bool app_SharedMemory=false;
    bool app_RtServer=false;
    bool app_DefaultFonts=false;
    bool app_DisableAss=false;
    std::vector<QString> app_Attachproc={};
    std::map<QString,QString> app_DockerEnv={};
    std::vector<QString> app_DockerLibs={};
    std::vector<regs> app_DockerRegs={};
}AppData;

//本地安装wine数据结构
typedef struct{
    QString iWineName=nullptr;
    QString iWineVer=nullptr;
    QString iWinePath=nullptr;
    QString iWineUrl=nullptr;
    QString iWineSrc=nullptr;
    QString iWineMono=nullptr;
    QString iWineGeckoX86=nullptr;
    QString iWineGeckoX86_64=nullptr;
    std::vector<QString> IwineDxvk={};
}WineData;

//远程wine数据结构
typedef struct {
    QString rWineName=nullptr;
    QString rWineVersion=nullptr;
    QString rWineGit=nullptr;
    QString rMono=nullptr;
    QString rGeckoX86=nullptr;
    QString rGeckoX86_64=nullptr;
    std::vector<QString> rWineDxvk={};
}RemoteWine;

typedef struct {
    QString pDockPath=nullptr;
    QString pDockName=nullptr;
    QString pWinePath=nullptr;
    QString pMainProc=nullptr;
    std::vector<QString> pAttachProc={};
}ProcInfo;

typedef struct {
    std::map<QString,QString> auto_Option={};
    std::map<QString,QString> auto_Docker={};
    std::vector<QString> app_Attachproc={};
    std::map<QString,QString> auto_Env={};
    std::vector<QString> auto_Libs={};
    std::map<QString,QString> auto_Dxvk={};
    std::vector<regs> auto_Regs={};
    QString auto_Args=nullptr;
}AutoJson;

typedef struct{
    QString appName=nullptr;
    QString appJson=nullptr;
    QString appIco=":/res/img/vek.ico";
}AppJson;

typedef struct{
    std::map<QString,AppData> docker_Data;
    QString docker_WinePath=nullptr;
    QString docker_WineVersion=nullptr;
    QString docker_Path=nullptr;
    QString docker_Name="vekON1";
    QString docker_SystemVersion="win7";
    QString docker_WineExeVersion="wine";
    QString docker_SystemBitVersion="win32";
    bool docker_MonoState=false;
    bool docker_GeckoState=false;
}DockData;

typedef struct{
    QString vekStyle="styleDefault";
    QString vekLang="langChinese";
}Options;

typedef struct {
    std::map<QString,DockData> local_DockerData={};
    std::map<QString,WineData> local_WineData={};
    std::map<QString,QString> local_AppSrcData={};
    std::map<QString,std::map<QString,std::map<QString,AppJson>>> local_AppJsonData={};
    std::map<QString,QString> local_WineSrcData={};
    std::map<QString,std::map<QString,RemoteWine>> local_WineJsonData={};
    Options local_VekOptions={};
}LocalData;

typedef struct{
    std::map<QString,QString> wtServer={};
}BaseWtServer;

typedef enum{
    WINECFG,
    REGEDIT,
    CONTROL,
    REMOVE,
    WINETRICKSGUI,
    WINETRICKSLIBS,
    START,
    DEBUG,
    SETAPP,
    EXPORTJSON,
    PACKAGEDEB,
    FORCEKILL,
    DELETEAPP,
    REGOBJ,
    BOOT,
    SERVER,
    DOCKSYSVER,
    DISABLE,
    PLUGS,
    DEFAULT
}OBJTYPE;

typedef enum{
    BOOTE,
    BOOTF,
    BOOTI,
    BOOTK,
    BOOTR,
    BOOTS,
    BOOTU,
    BOOTDEFAULT
}BOOTTYPE;
typedef enum{
    SERVERK,
    SERVERP,
    SERVERW,
    SERVERDEFAULT
}SERVERTYPE;
typedef enum{
    DELETE,
    SEETING,
    ADD
}OBJAPP;
extern LocalData g_vekLocalData;
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
