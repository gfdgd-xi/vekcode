﻿#ifndef BASEDATA_H
#define BASEDATA_H

#include <QString>
#include <iostream>
#include <map>
#include <vector>
#include "objectTray.h"
typedef struct{
    QString rPath=nullptr;
    QString rKey=nullptr;
    QString rTValue=nullptr;
    QString rValue=nullptr;
}SRegs;

typedef struct {
    QString s_uid=nullptr;
    QString s_name=nullptr;
    QString s_ico=":/res/img/vek.ico";
    QString s_exe=nullptr;
    QString s_agrs_code=nullptr;
    QString s_work_path=nullptr;
    QString s_dxvk_version=nullptr;
    QString s_dxvk_config_file=nullptr;
    QString s_main_proc_name=nullptr;
    QString s_dock_system_version=nullptr;
    bool b_dxvk_state=false;
    bool b_dxvk_hud=false;
    bool b_dxvk_config_file_state=false;
    bool b_task_log=false;
    bool b_writecopy=false;
    bool b_sharedmemory=false;
    bool b_rtserver=false;
    bool b_default_fonts=false;
    bool b_disable_ass=false;
    bool b_mono_state=false;
    bool b_gecko_state=false;
    bool b_ICMP_state=false;
    std::vector<QString> vec_proc_attach_list={};
    std::map<QString,QString> map_docker_envs={};
    std::vector<QString> vec_docker_libs={};
    std::vector<SRegs> vec_docker_regs={};
}SappData;

//本地安装wine数据结构
typedef struct{
    QString s_local_wine_name=nullptr;
    QString s_local_wine_version=nullptr;
    QString s_local_wine_path=nullptr;
    QString s_local_wine_url=nullptr;
    QString s_local_wine_src=nullptr;
    QString s_local_wine_mono=nullptr;
    QString s_local_wine_gecko_86=nullptr;
    QString s_local_wine_gecko_8664=nullptr;
    std::vector<QString> s_local_wine_dxvk={};
}SwineData;

//远程wine数据结构
typedef struct {
    QString s_remote_wine_name=nullptr;
    QString s_remote_wine_version=nullptr;
    QString s_remote_wine_git=nullptr;
    QString s_remote_wine_mono=nullptr;
    QString s_remote_wine_gecko_86=nullptr;
    QString s_remote_wine_gecko_8664=nullptr;
    std::vector<QString> vec_remote_wine_dxvk={};
}SwineRemoteData;

typedef struct {
    QString s_proc_docker_path=nullptr;
    QString s_proc_docker_name=nullptr;
    QString s_proc_wine_path=nullptr;
    QString s_proc_main_name=nullptr;
    std::vector<QString> vec_proc_attach_list={};
}SappProcData;

typedef struct {
    std::map<QString,QString> map_deploy_option={};
    std::map<QString,QString> map_deploy_docker={};
    std::vector<QString> vec_deploy_attach_proc={};
    std::map<QString,QString> map_deploy_env={};
    std::vector<QString> vec_deploy_libs={};
    std::map<QString,QString> map_deploy_dxvk={};
    std::vector<SRegs> vec_deploy_regs={};
    QString map_deploy_args=nullptr;
}SappDeployData;

typedef struct{
    QString s_deploy_app_name=nullptr;
    QString s_deploy_app_json=nullptr;
    QString s_deploy_app_ico=":/res/img/vek.ico";
}SappDeployInfo;

typedef struct{
    std::map<QString,SappData> map_dockers_data;
    QString s_dockers_wine_path=nullptr;
    QString s_dockers_wine_version=nullptr;
    QString s_dockers_path=nullptr;
    QString s_dockers_name="vekON1";
    QString s_dockers_system_version="win7";
    QString s_dockers_wine_exe_version="wine";
    QString s_dockers_bit_version="win32";
    QString s_dockers_download_engine="wget";
    bool s_dockers_mono_state=false;
    bool s_dockers_gecko_state=false;
    bool s_dockers_task_log=false;
    bool s_dockers_writecopy=false;
    bool s_dockers_sharedmemory=false;
    bool s_dockers_rtserver=false;
    bool s_dockers_default_fonts=false;
    bool s_dockers_disable_ass=false;
    bool s_dockers_ICMP_state=false;
}SdockerData;

typedef struct{
    QString vekStyle="styleDefault";
    QString vekLang="langChinese";
}SvekOptions;

typedef struct {
    std::map<QString,SdockerData> map_docker_list={};
    std::map<QString,SwineData> map_wine_list={};
    std::map<QString,QString> map_wine_src_list={};
    std::map<QString,QString> map_app_src_list={};
    std::map<QString,std::map<QString,std::map<QString,SappDeployInfo>>> map_app_json_list={};
    std::map<QString,std::map<QString,SwineRemoteData>> map_wine_json_list={};
    SvekOptions vekOptions={};
}SlocalGloablData;

typedef struct{
    QString sDesrc;
    QString sAppNameEN;
    QString sAppNameCN;
    QString sDockerName;
    QString sAppType;
    QString sAppIco;
    QString sAppExeName;
    QString sAppExePath;
    QString sAppDebName;
    QString sAppDebNamePro;
    QString sAppDebVersion;
    QString sAppOldDebName;
}Spackage;


typedef struct{
    std::map<QString,QString> wtServer={};
}BaseWtServer;

typedef enum{
    object_docker_default,
    object_docker_winecfg,
    object_docker_regedit,
    object_docker_control,
    object_docker_uninstall,
    object_docker_winetricks_gui,
    object_docker_winetricks_cmd_libs,
    object_docker_allforcekill,
    object_docker_reggedit_extend,
    object_docker_wineboot_extend,
    object_docker_wineserver_extend,
    object_docker_switch_version,
    object_docker_plugs_extend
}Extend_Docker;

typedef enum{
    object_app_start,
    object_app_debugstart,
    object_app_setgame,
    object_app_exportJson,
    object_app_packageDeb,
    object_app_forcekill,
    object_app_deletegame
}Extend_App;

typedef enum{
    object_wineboot_default,
    object_wineboot_e,
    object_wineboot_f,
    object_wineboot_i,
    object_wineboot_k,
    object_wineboot_r,
    object_wineboot_s,
    object_wineboot_u
}Extend_Boot;

typedef enum{
    object_wineserver_default,
    object_wineserver_k,
    object_wineserver_p,
    object_wineserver_w,   
}Extend_Server;

typedef enum{
    object_delApp,
    object_setApp,
    object_addApp
}EADEType;

typedef struct{
     Extend_Docker ex_docker;
     Extend_App ex_app;
     Extend_Boot ex_boot;
     Extend_Server ex_Server;
}ExtendArgs;

typedef struct{
    QString SrcWineUrl;
    QString SrcAppUrl;
    QString SrcWinetrickServerUrl;
    QString SrcUpLogs;
    QString SrcLogShow;
    QString SrcUpInfo;
}GSrcUrl;

extern SlocalGloablData g_vekLocalData;
extern GSrcUrl g_srcUrl;
extern std::map<QString,QString> winetricks_server_url_list;
extern QString sWinetrickUrl;
extern std::map<QString,std::map<QString,QString>> fontRes;
extern std::map<QString,std::map<QString,QString>> dxvkResCof;
extern std::map<QString,std::map<QString,QString>> dxvkResHUD;
extern std::map<QString,std::map<QString,QString>> winebuilder;
extern std::map<QString,std::map<QString,QString>> winemine;
extern std::map<QString,std::map<QString,QString>> dxvkRes;
extern std::map<QString,std::map<QString,QString>> dxvkResCache;
extern std::map<QString,std::map<QString,QString>> dxvkResLog;
extern objectTray* objTray;
#endif // BASEDATA_H
