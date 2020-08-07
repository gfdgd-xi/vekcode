#ifndef BASERES_H
#define BASERES_H
#include "common.h"
//全局数据结构
BaseLocalData g_vekLocalData={};
std::vector<QString> taskList={};

static QString vekUpInfo="https://gitee.com/JackLee02/vekGame/raw/master/vekUpdateInfo.json";
//dxvk
std::map<QString,std::map<QString,QString>> dxvkRes={
   {"HKEY_CURRENT_USER\\Software\\Wine\\DllOverrides",{{"","native"}}}
};
//dxvkHUD
std::map<QString,std::map<QString,QString>> dxvkResHUD={
   {"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment",{{"DXVK_HUD","devinfo,fps,frametimes,submissions,drawcalls,pipelines,memory,version"}}}
};
//dxvkConfig
std::map<QString,std::map<QString,QString>> dxvkResCof={
   {"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment",{{"DXVK_CONFIG_FILE",""}}}
};
//dxvkCache
std::map<QString,std::map<QString,QString>> dxvkResCache={
   {"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment",{{"DXVK_STATE_CACHE_PATH",""}}}
};
//dxvkLog
std::map<QString,std::map<QString,QString>> dxvkResLog={
   {"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment",{{"DXVK_LOG_PATH",""}}}
};
//默认字体注册表字符串
std::map<QString,std::map<QString,QString>> fontRes={
   {"HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows NT\\CurrentVersion\\FontSubstitutes",
    {
        //{"FixedSys","msyh"},
        //{"System","msyh"},
        //{"Tahoma","msyh"},
        //{"MS Shell Dlg","msyh"}
        {"FixedSys","simsun"},
        {"System","simsun"},
        {"Tahoma","simsun"},
        {"MS Shell Dlg","simsun"}
    }
   }
};
#endif // BASERES_H
