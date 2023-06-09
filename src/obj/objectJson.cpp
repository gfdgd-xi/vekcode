﻿#include "objectJson.h"
#include <iomanip>
#include <mutex>
#include <QString>

std::mutex josn_mutex;
objectJson::objectJson()
{

}
objectJson::~objectJson()
{
}
//增加游戏
json objectJson::DataSerialize(json jsonData,const SlocalGloablData _baseLocalData){
    //序列化容器列表
    //ax.first->容器名
    if(_baseLocalData.map_docker_list.size()>0){
        for(auto ax:_baseLocalData.map_docker_list){
            //bx.first->游戏CID
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(WineVersion)]=ax.second.s_dockers_wine_version.toStdString();
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(WinePath)]=ax.second.s_dockers_wine_path.toStdString();
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerSystemVersion)]=ax.second.s_dockers_system_version.toStdString();
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerVer)]=ax.second.s_dockers_bit_version.toStdString();
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerPath)]=ax.second.s_dockers_path.toStdString();
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerName)]=ax.second.s_dockers_name.toStdString();
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerWineVersion)]=ax.second.s_dockers_wine_exe_version.toStdString();
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(MonoState)]=ax.second.s_dockers_mono_state;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(GeckoState)]=ax.second.s_dockers_gecko_state;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerTaskLog)]=ax.second.s_dockers_task_log;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerWriteCopy)]=ax.second.s_dockers_writecopy;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerSharedMemory)]=ax.second.s_dockers_sharedmemory;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerRTServer)]=ax.second.s_dockers_rtserver;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerFonts)]=ax.second.s_dockers_default_fonts;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerAss)]=ax.second.s_dockers_disable_ass;
            jsonData[toStr(Docker)][ax.first.toStdString()][toStr(DockerICMP)]=ax.second.s_dockers_ICMP_state;
            if(ax.second.map_dockers_data.size()>0){
                for(auto [bx,by]:ax.second.map_dockers_data){
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppCID)]=by.s_uid.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppName)]=by.s_name.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppIco)]=by.s_ico.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppExe)]=by.s_exe.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DxvkHUD)]=by.b_dxvk_hud;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DxvkVerson)]=by.s_dxvk_version.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DxvkConfigFile)]=by.s_dxvk_config_file.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppOtherAgrs)]=by.s_agrs_code.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(WorkPath)]=by.s_work_path.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(MainPrcoName)]=by.s_main_proc_name.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockSysVersion)]=by.s_dock_system_version.toStdString();
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(TaskLog)]=by.b_task_log;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DxvkState)]=by.b_dxvk_state;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(WriteCopy)]=by.b_writecopy;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(SharedMemory)]=by.b_sharedmemory;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(RtServer)]=by.b_rtserver;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DisableAss)]=by.b_disable_ass;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DefaultFonts)]=by.b_default_fonts;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppMono)]=by.b_mono_state;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppGecko)]=by.b_gecko_state;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AppICMP)]=by.b_ICMP_state;
                    jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DxvkConfigFileState)]=by.b_dxvk_config_file_state;
                    if(!by.map_docker_envs.empty()){
                        for(auto&[fa,yz]:by.map_docker_envs){
                            jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerEnv)][fa.toStdString()]=yz.toStdString();
                        }
                    }else{
                        jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerEnv)]=json({});
                    }
                    if(!by.vec_docker_libs.empty()){
                        for(auto&ya:by.vec_docker_libs){
                            jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerLibs)].push_back(ya.toStdString());
                        }
                    }else{
                        jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerLibs)]=json({});
                    }
                    if(!by.vec_docker_regs.empty()){
                        int i=-1;
                        for(auto a:by.vec_docker_regs){
                            i+=1;
                            jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerRegs)][i][toStr(rPath)]=a.rPath.toStdString();
                            jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerRegs)][i][toStr(rKey)]=a.rKey.toStdString();
                            jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerRegs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                            jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerRegs)][i][toStr(rValue)]=a.rValue.toStdString();
                        }
                    }else{
                        jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(DockerRegs)]=json::array();
                    }
                    if(!by.vec_proc_attach_list.empty()){
                        for(auto rs:by.vec_proc_attach_list){
                            jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AttachProc)].push_back(rs.toStdString());
                        }
                    }else{
                        jsonData[toStr(Docker)][ax.first.toStdString()][by.s_uid.toStdString()][toStr(AttachProc)]=json::array();
                    }
                }
            }
        }
    }

    //禁止修改
    for(auto &k : _baseLocalData.map_wine_list){
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineName)]=k.second.s_local_wine_name.toStdString();
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwinePath)]=k.second.s_local_wine_path.toStdString();
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineVer)]=k.second.s_local_wine_version.toStdString();
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineUrl)]=k.second.s_local_wine_url.toStdString();
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineSrc)]=k.second.s_local_wine_src.toStdString();
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineMono)]=k.second.s_local_wine_mono.toStdString();
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineGeckoX86)]=k.second.s_local_wine_gecko_86.toStdString();
        jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineGeckoX86_64)]=k.second.s_local_wine_gecko_8664.toStdString();
        for(auto dx:k.second.s_local_wine_dxvk){
            jsonData[toStr(Wine)][k.second.s_local_wine_name.toStdString()][toStr(IwineDxvk)].push_back(dx.toStdString());
        }
    }
    //序列化数据源数据
    for(auto &[x,y]: _baseLocalData.map_app_src_list){
        //x 数据源名字
        //y 数据源json url
        //增加数据源
        jsonData[toStr(AppScrSource)][x.toStdString()]=y.toStdString();
        //序列化该数据源下所有数据
        for(auto &[a,b]: _baseLocalData.map_app_json_list){
            //a 数据源名字
            //b 数据源下数据
            for(auto&[u,i]:b){
                //u app分类名字
                //i app分类下数据
                for(auto [dx,dc]:i){
                    //dx app名字
                    //dc app数据
                    jsonData[toStr(AppJsonList)][a.toStdString()][u.toStdString()][dx.toStdString()][toStr(appName)]=dc.s_deploy_app_name.toStdString();
                    jsonData[toStr(AppJsonList)][a.toStdString()][u.toStdString()][dx.toStdString()][toStr(appIco)]=dc.s_deploy_app_ico.toStdString();
                    jsonData[toStr(AppJsonList)][a.toStdString()][u.toStdString()][dx.toStdString()][toStr(appJson)]=dc.s_deploy_app_json.toStdString();
                }
                //jsonData[toStr(AppJsonList)][x.toStdString()][u.toStdString()]=i.toStdString();
            }
        }
    }
    /* x a 源名字
     *
     */
    for(auto &[x,y]: _baseLocalData.map_wine_src_list){
        jsonData["WineScrSource"][x.toStdString()]=y.toStdString();
        for(auto&[a,b]:_baseLocalData.map_wine_json_list){
            if(a==x){
                for(auto& [d,e]:b){
                    jsonData[toStr(WineJsonList)][x.toStdString()][e.s_remote_wine_name.toStdString()][toStr(WineName)]=e.s_remote_wine_name.toStdString();
                    jsonData[toStr(WineJsonList)][x.toStdString()][e.s_remote_wine_name.toStdString()][toStr(WineVersion)]=e.s_remote_wine_version.toStdString();
                    jsonData[toStr(WineJsonList)][x.toStdString()][e.s_remote_wine_name.toStdString()][toStr(WineGit)]=e.s_remote_wine_git.toStdString();
                    jsonData[toStr(WineJsonList)][x.toStdString()][e.s_remote_wine_name.toStdString()][toStr(Mono)]=e.s_remote_wine_mono.toStdString();
                    jsonData[toStr(WineJsonList)][x.toStdString()][e.s_remote_wine_name.toStdString()][toStr(GeckoX86)]=e.s_remote_wine_gecko_86.toStdString();
                    jsonData[toStr(WineJsonList)][x.toStdString()][e.s_remote_wine_name.toStdString()][toStr(GeckoX86_64)]=e.s_remote_wine_gecko_8664.toStdString();
                    for(auto dy:e.vec_remote_wine_dxvk){
                        jsonData[toStr(WineJsonList)][x.toStdString()][e.s_remote_wine_name.toStdString()][toStr(WineDxvk)].push_back(dy.toStdString());
                    }
                }
            }
        }
    }
    jsonData[toStr(VekOptions)][toStr(vekStyle)]=_baseLocalData.vekOptions.vekStyle.toStdString();
    jsonData[toStr(VekOptions)][toStr(vekLang)]=_baseLocalData.vekOptions.vekLang.toStdString();
    return jsonData;
}

//反序列化到结构
bool objectJson::unDataSerializeLocalData(){
    //解析srt为json
    try
    {
        QString jsonPath=QApplication::applicationDirPath()+"/data.json";
        QFile file(jsonPath);
        if(!file.exists())
        {
            return false;
        }
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        string temp = file.readAll().toStdString();
        file.close();
        json j3=json::parse(temp);
        if(j3==nullptr){

            return false;
        }
        for (auto& [k, v] : j3.items())
        {
            //反序列化容器表内数据
            if(k==toStr(Docker)){
                //ax->容器名 bx->容器下的游戏列表
                for(auto [ax,bx]:v.items()){
                    SdockerData baseDockData={};
                    auto it = bx.begin();
                    for(it=bx.begin();it!=bx.end();++it)
                    {
                        if(it.value().is_string()){
                            baseDockData.s_dockers_wine_path=QString::fromStdString(bx.at(toStr(WinePath)));
                            baseDockData.s_dockers_wine_version=QString::fromStdString(bx.at(toStr(WineVersion)));
                            baseDockData.s_dockers_path=QString::fromStdString(bx.at(toStr(DockerPath)));
                            baseDockData.s_dockers_name=QString::fromStdString(bx.at(toStr(DockerName)));
                            baseDockData.s_dockers_system_version=QString::fromStdString(bx.at(toStr(DockerSystemVersion)));
                            baseDockData.s_dockers_bit_version=QString::fromStdString(bx.at(toStr(DockerVer)));
                            baseDockData.s_dockers_wine_exe_version=QString::fromStdString(bx.at(toStr(DockerWineVersion)));
                        }
                        if(it.value().is_boolean()){
                            baseDockData.s_dockers_mono_state=bx.at(toStr(MonoState)).get<bool>();
                            baseDockData.s_dockers_gecko_state=bx.at(toStr(GeckoState)).get<bool>();
                            baseDockData.s_dockers_task_log=bx.at(toStr(DockerTaskLog)).get<bool>();
                            baseDockData.s_dockers_writecopy=bx.at(toStr(DockerWriteCopy)).get<bool>();
                            baseDockData.s_dockers_sharedmemory=bx.at(toStr(DockerSharedMemory)).get<bool>();
                            baseDockData.s_dockers_rtserver=bx.at(toStr(DockerRTServer)).get<bool>();
                            baseDockData.s_dockers_default_fonts=bx.at(toStr(DockerFonts)).get<bool>();
                            baseDockData.s_dockers_disable_ass=bx.at(toStr(DockerAss)).get<bool>();
                            baseDockData.s_dockers_ICMP_state=bx.at(toStr(DockerICMP)).get<bool>();

                        }
                        if(it.value().is_object())
                        {
                            for(auto x:it.value())
                            {
                                SappData _base_app_data={};
                                _base_app_data.s_uid=QString::fromStdString(it.value().at("AppCID"));
                                _base_app_data.s_name=QString::fromStdString(it.value().at("AppName"));
                                _base_app_data.s_exe=QString::fromStdString(it.value().at("AppExe"));
                                _base_app_data.s_ico=QString::fromStdString(it.value().at("AppIco"));
                                _base_app_data.s_agrs_code=QString::fromStdString(it.value().at("AppOtherAgrs"));
                                _base_app_data.s_dxvk_version=QString::fromStdString(it.value().at("DxvkVerson"));
                                _base_app_data.s_work_path=QString::fromStdString(it.value().at("WorkPath"));
                                _base_app_data.s_dxvk_config_file=QString::fromStdString(it.value().at("DxvkConfigFile"));
                                _base_app_data.s_main_proc_name=QString::fromStdString(it.value().at("MainPrcoName"));
                                _base_app_data.s_dock_system_version=QString::fromStdString(it.value().at("DockSysVersion"));
                                _base_app_data.b_dxvk_state=it.value().at("DxvkState").get<bool>();
                                _base_app_data.b_dxvk_hud=it.value().at("DxvkHUD").get<bool>();
                                _base_app_data.b_task_log=it.value().at("TaskLog").get<bool>();
                                _base_app_data.b_writecopy=it.value().at("WriteCopy").get<bool>();
                                _base_app_data.b_sharedmemory=it.value().at("SharedMemory").get<bool>();
                                _base_app_data.b_rtserver=it.value().at("RtServer").get<bool>();
                                _base_app_data.b_default_fonts=it.value().at("DefaultFonts").get<bool>();
                                _base_app_data.b_disable_ass=it.value().at("DisableAss").get<bool>();
                                _base_app_data.b_dxvk_config_file_state=it.value().at("DxvkConfigFileState").get<bool>();
                                _base_app_data.b_mono_state=it.value().at("AppMono").get<bool>();
                                _base_app_data.b_gecko_state=it.value().at("AppGecko").get<bool>();
                                _base_app_data.b_ICMP_state=it.value().at("AppICMP").get<bool>();
                                _base_app_data.vec_proc_attach_list.clear();
                                if(it.value().at("AttachProc")!=NULL){
                                    for(auto idx:it.value().at("AttachProc")){
                                        _base_app_data.vec_proc_attach_list.push_back(QString::fromStdString(idx));
                                    }
                                }
                                _base_app_data.map_docker_envs.clear();
                                if(it.value().at("DockerEnv")!=NULL){
                                    for(auto&[vx,vy]:it.value().at("DockerEnv").items()){
                                        _base_app_data.map_docker_envs[QString::fromStdString(vx)]=QString::fromStdString(vy);
                                    }
                                }
                                _base_app_data.vec_docker_regs.clear();
                                if(it.value().at("DockerRegs")!=NULL){
                                    for(auto&wy:it.value().at("DockerRegs")){
                                        SRegs _rbaseRegs;
                                        _rbaseRegs.rPath=QString::fromStdString(wy.at("rPath"));
                                        _rbaseRegs.rKey=QString::fromStdString(wy.at("rKey"));
                                        _rbaseRegs.rTValue=QString::fromStdString(wy.at("rTValue"));
                                        _rbaseRegs.rValue=QString::fromStdString(wy.at("rValue"));
                                        _base_app_data.vec_docker_regs.push_back(_rbaseRegs);
                                    }
                                }
                                baseDockData.map_dockers_data[_base_app_data.s_uid]=_base_app_data;
                            }
                        }
                    }
                    g_vekLocalData.map_docker_list[QString::fromStdString(ax)]=baseDockData;
                }
                //禁止修改
            }
            else if(k==toStr(Wine)){
                SwineData _base_wine_data={};
                for(auto& [x,y]: v.items()){
                    _base_wine_data.s_local_wine_name=QString::fromStdString(y.at("IwineName"));
                    _base_wine_data.s_local_wine_path=QString::fromStdString(y.at("IwinePath"));
                    _base_wine_data.s_local_wine_version=QString::fromStdString(y.at("IwineVer"));
                    _base_wine_data.s_local_wine_url=QString::fromStdString(y.at("IwineUrl"));
                    _base_wine_data.s_local_wine_src=QString::fromStdString(y.at("IwineSrc"));
                    _base_wine_data.s_local_wine_mono=QString::fromStdString(y.at("IwineMono"));
                    _base_wine_data.s_local_wine_gecko_86=QString::fromStdString(y.at("IwineGeckoX86"));
                    _base_wine_data.s_local_wine_gecko_8664=QString::fromStdString(y.at("IwineGeckoX86_64"));
                    _base_wine_data.s_local_wine_dxvk.clear();
                    for(auto yz:y.at("IwineDxvk")){
                        _base_wine_data.s_local_wine_dxvk.push_back(QString::fromStdString(yz));
                    }
                    g_vekLocalData.map_wine_list[_base_wine_data.s_local_wine_name]=_base_wine_data;
                }
            }
            else if(k==toStr(AppScrSource)){
                //软件数据反序列化
                for(auto [b,c] :v.items())
                {
                    //b源名字
                    g_vekLocalData.map_app_src_list[QString::fromStdString(b)]=QString::fromStdString(c);
                    for (auto& [d, j] : j3.items())
                    {
                        if(d==toStr(AppJsonList)){

                            for(auto&[u,i]:j.items()){
                                //u 源名字
                                std::map<QString,std::map<QString,SappDeployInfo>> appTypeList;
                                for(auto [di,du]:i.items()){
                                    //di app分类名字
                                    //du 分类app列表
                                    std::map<QString,SappDeployInfo> appList;
                                    for(auto [dv,dw]:du.items()){
                                        //dv app名字
                                        //dw app数据
                                        SappDeployInfo baseAppJson;
                                        baseAppJson.s_deploy_app_name=QString::fromStdString(dw.at(toStr(appName)));
                                        baseAppJson.s_deploy_app_ico=QString::fromStdString(dw.at(toStr(appIco)));
                                        baseAppJson.s_deploy_app_json=QString::fromStdString(dw.at(toStr(appJson)));
                                        appList.insert(pair<QString,SappDeployInfo>(QString::fromStdString(dv),baseAppJson));
                                    }
                                    appTypeList[QString::fromStdString(di)]=appList;
                                }
                                g_vekLocalData.map_app_json_list[QString::fromStdString(u)]=appTypeList;
                            }
                        }
                    }
                }
            }
            //wine数据序列化
            else if(k=="WineScrSource"){
                /* b u 源名字
                 * i 源下wine版本
                 * kj 版本信息
                 * ix dxvk版本
                */
                for(auto &[b, c] :v.items())
                {
                    g_vekLocalData.map_wine_src_list[QString::fromStdString(b)]=QString::fromStdString(c);
                    for (auto& [d, j] : j3.items())
                    {
                        if(d==toStr(WineJsonList)){
                            for(auto&[u,i]:j.items())
                            {
                                if(u==b)
                                {
                                    for(auto& kj:i){
                                        g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].s_remote_wine_name=QString::fromStdString(kj.at("WineName"));
                                        g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].s_remote_wine_version=QString::fromStdString(kj.at("WineVersion"));
                                        g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].s_remote_wine_git=QString::fromStdString(kj.at("WineGit"));
                                        g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].s_remote_wine_mono=QString::fromStdString(kj.at("Mono"));
                                        g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].s_remote_wine_gecko_86=QString::fromStdString(kj.at("GeckoX86"));
                                        g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].s_remote_wine_gecko_8664=QString::fromStdString(kj.at("GeckoX86_64"));
                                        g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].vec_remote_wine_dxvk.clear();
                                        for(auto ix:kj.at("WineDxvk"))
                                        {
                                            g_vekLocalData.map_wine_json_list[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].vec_remote_wine_dxvk.push_back(QString::fromStdString(ix));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(k==toStr(VekOptions)){
                g_vekLocalData.vekOptions.vekStyle=QString::fromStdString(j3.at(toStr(VekOptions)).at(toStr(vekStyle)));
                g_vekLocalData.vekOptions.vekLang=QString::fromStdString(j3.at(toStr(VekOptions)).at(toStr(vekLang)));
            }
        }
        return true;
    }
    catch (nullptr_t)
    {
        return false;
    }

}
bool objectJson::unSrcData(std::string tData){
    json j3=json::parse(tData);
    if(j3==nullptr){
        return false;
    }
    for (auto& [k, v] : j3.items()){
        if(k=="wineUrl"){
            g_srcUrl.SrcWineUrl=QString::fromStdString(v);
        }
        if(k=="appJsonUrl"){
            g_srcUrl.SrcAppUrl=QString::fromStdString(v);
        }
        if(k=="winetrickUrl"){
            g_srcUrl.SrcWinetrickServerUrl=QString::fromStdString(v);
        }
        if(k=="upLogs"){
            g_srcUrl.SrcUpLogs=QString::fromStdString(v);
        }
        if(k=="logShow"){
            g_srcUrl.SrcLogShow=QString::fromStdString(v);
        }
        if(k=="updateInfo"){
            g_srcUrl.SrcUpInfo=QString::fromStdString(v);
        }
    }
    if(g_srcUrl.SrcAppUrl!=nullptr&&
            g_srcUrl.SrcUpInfo!=nullptr&&
            g_srcUrl.SrcUpLogs!=nullptr&&
            g_srcUrl.SrcLogShow!=nullptr&&
            g_srcUrl.SrcWineUrl!=nullptr&&
            g_srcUrl.SrcWinetrickServerUrl!=nullptr){
        return true;
    }
    return false;
}
//脚本反序列化
SappDeployData* objectJson::unDataSerializeScriptData(SappDeployData* _baseAutoSetJson,const QString autoJsonData){
    try {
        json js3=json::parse(autoJsonData.toStdString());
        for(auto&[k,j]:js3.items()){
            if(QString::fromStdString(k)=="Option"){
                for(auto&[iu,zu]:j.items()){
                    _baseAutoSetJson->map_deploy_option[QString::fromStdString(iu)]=QString::fromStdString(zu);
                }
            }
            if(QString::fromStdString(k)==toStr(Docker)){
                for(auto&[ix,zx]:j.items()){
                    _baseAutoSetJson->map_deploy_docker[QString::fromStdString(ix)]=QString::fromStdString(zx);
                }
            }
            if(QString::fromStdString(k)=="AttachProc"){
                if(!j.empty()){
                    for(auto&zu:j.items()){
                        _baseAutoSetJson->vec_deploy_attach_proc.push_back(QString::fromStdString(zu.value()));
                    }
                }
            }
            if(QString::fromStdString(k)=="Env"){
                if(!j.empty()){
                    for(auto&[iu,zu]:j.items()){
                        _baseAutoSetJson->map_deploy_env[QString::fromStdString(iu)]=QString::fromStdString(zu);
                    }
                }
            }
            if(QString::fromStdString(k)=="Libs"){
                if(!j.empty()){
                    for(auto& d:j.items()){
                        _baseAutoSetJson->vec_deploy_libs.push_back(QString::fromStdString(d.value()));
                    }
                }
            }
            if(QString::fromStdString(k)=="Dxvk"){
                for(auto&[iy,zy]:j.items()){
                    _baseAutoSetJson->map_deploy_dxvk[QString::fromStdString(iy)]=QString::fromStdString(zy);
                }
            }
            if(QString::fromStdString(k)=="Regs"){
                if(!j.empty()){
                    for(auto ad:j.items()){
                        SRegs rbaseRegs;
                        rbaseRegs.rPath=QString::fromStdString(ad.value().at("rPath"));
                        rbaseRegs.rKey=QString::fromStdString(ad.value().at("rKey"));
                        rbaseRegs.rTValue=QString::fromStdString(ad.value().at("rTValue"));
                        rbaseRegs.rValue=QString::fromStdString(ad.value().at("rValue"));
                        _baseAutoSetJson->vec_deploy_regs.push_back(rbaseRegs);
                    }
                }
            }
            if(QString::fromStdString(k)=="Args"){
                if(j!=nullptr){
                    _baseAutoSetJson->map_deploy_args=QString::fromStdString(j);
                }

            }
        }
    } catch (nullptr_t) {
        _baseAutoSetJson=nullptr;
    }
    return _baseAutoSetJson;
}

bool objectJson::unSerializeLocalWineApp(QString key,const QString urlData,UNJSONTYPE jsonType){
    json jdata=json::parse(urlData.toStdString());
    try {
        switch (jsonType) {
        //反序列wine列表
        case unJsonWineList:
            for(auto &[x, y] :jdata.items())
            {
                g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].s_remote_wine_name=QString::fromStdString(y.at("WineName"));
                g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].s_remote_wine_version=QString::fromStdString(y.at("WineVersion"));
                g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].s_remote_wine_git=QString::fromStdString(y.at("WineGit"));
                g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].s_remote_wine_mono=QString::fromStdString(y.at("Mono"));
                g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].s_remote_wine_gecko_86=QString::fromStdString(y.at("GeckoX86"));
                g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].s_remote_wine_gecko_8664=QString::fromStdString(y.at("GeckoX86_64"));
                g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].vec_remote_wine_dxvk.clear();
                for(auto xz:y.at("WineDxvk")){
                    g_vekLocalData.map_wine_json_list[key][QString::fromStdString(y.at("WineName"))].vec_remote_wine_dxvk.push_back(QString::fromStdString(xz));
                }
            }
            break;
            //反序列App数据列表
        case unJsonGameList:
            for(auto [x,y]:jdata.items()){
                for(auto [z,i]:y.items()){
                    //key源名字
                    //x软件分类
                    //z软件名字
                    g_vekLocalData.map_app_json_list[key][QString::fromStdString(x)][QString::fromStdString(z)].s_deploy_app_name=QString::fromStdString(i.at(toStr(AppName)));
                    g_vekLocalData.map_app_json_list[key][QString::fromStdString(x)][QString::fromStdString(z)].s_deploy_app_ico=QString::fromStdString(i.at(toStr(AppIco)));
                    g_vekLocalData.map_app_json_list[key][QString::fromStdString(x)][QString::fromStdString(z)].s_deploy_app_json=QString::fromStdString(i.at(toStr(AppJson)));
                }
            }
            break;
        }

    } catch (nullptr_t) {
        return false;
    }
    return true;
}
json objectJson::exportJson(SdockerData xData,QString s_uid){
    json eJson=nullptr;
    for(auto b:xData.map_dockers_data){
        if(b.second.s_uid==s_uid){
            eJson[toStr(Option)][toStr(DefaultFont)]=toStr(false);
            eJson[toStr(Option)][toStr(SharedMemory)]=toStr(false);
            eJson[toStr(Option)][toStr(WriteCopy)]=toStr(false);
            eJson[toStr(Option)][toStr(RtServer)]=toStr(false);
            eJson[toStr(Dxvk)][toStr(DxvkState)]=toStr(false);
            eJson[toStr(Dxvk)][toStr(DxvkHUD)]=toStr(false);
            eJson[toStr(Docker)][toStr(MonoState)]=toStr(false);
            eJson[toStr(Docker)][toStr(GeckoState)]=toStr(false);

            if(b.second.b_default_fonts){
                eJson[toStr(Option)][toStr(DefaultFont)]=toStr(true);
            }
            if(b.second.b_sharedmemory){
                eJson[toStr(Option)][toStr(SharedMemory)]=toStr(true);
            }
            if(b.second.b_writecopy){
                eJson[toStr(Option)][toStr(WriteCopy)]=toStr(true);
            }
            if(b.second.b_rtserver){
                eJson[toStr(Option)][toStr(RtServer)]=toStr(true);
            }
            if(xData.s_dockers_mono_state){
                eJson[toStr(Docker)][toStr(MonoState)]=toStr(true);
            }
            if(xData.s_dockers_gecko_state){
                eJson[toStr(Docker)][toStr(GeckoState)]=toStr(true);
            }
            if(b.second.b_dxvk_state){
                eJson[toStr(Dxvk)][toStr(DxvkState)]=toStr(true);
            }
            if(b.second.b_dxvk_hud){
                eJson[toStr(Dxvk)][toStr(DxvkHUD)]=toStr(true);
            }
            eJson[toStr(Option)][toStr(AppName)]=b.second.s_name.toStdString();
            eJson[toStr(Option)][toStr(MainPrcoName)]=b.second.s_main_proc_name.toStdString();
            eJson[toStr(Docker)][toStr(DockerSysVersion)]=b.second.s_dock_system_version.toStdString();
            eJson[toStr(Docker)][toStr(DockerVersion)]=xData.s_dockers_bit_version.toStdString();
            eJson[toStr(Docker)][toStr(DockerWineVersion)]=xData.s_dockers_wine_exe_version.toStdString();
            if(!b.second.vec_proc_attach_list.empty()){
                for(auto rs:b.second.vec_proc_attach_list){
                    eJson[toStr(AttachProc)].push_back(rs.toStdString());
                }
            }else{
                eJson[toStr(AttachProc)]=json::array();
            }
            if(!b.second.map_docker_envs.empty()){
                for(auto&[fa,yz]:b.second.map_docker_envs){
                    eJson[toStr(Env)][fa.toStdString()]=yz.toStdString();
                }
            }else{
                eJson[toStr(Env)]=json({});
            }
            if(!b.second.vec_docker_libs.empty()){
                for(auto&ya:b.second.vec_docker_libs){
                    eJson[toStr(Libs)].push_back(ya.toStdString());
                }
            }else{
                eJson[toStr(Libs)]=json::array();
            }
            if(!b.second.vec_docker_regs.empty()){
                int i=0;
                for(auto a:b.second.vec_docker_regs){
                    i+=1;
                    eJson[toStr(Regs)][i][toStr(rPath)]=a.rPath.toStdString();
                    eJson[toStr(Regs)][i][toStr(rKey)]=a.rKey.toStdString();
                    eJson[toStr(Regs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                    eJson[toStr(Regs)][i][toStr(rValue)]=a.rValue.toStdString();
                }
            }else{
                eJson[toStr(Regs)]=json::array();
            }
            eJson[toStr(Args)]=b.second.s_agrs_code.toStdString();
            eJson[toStr(Dxvk)][toStr(dxvkVersion)]=b.second.s_dxvk_version.toStdString();
        }
    }
    return eJson;
}
//×××××××××××数据文件操作××××××××××//
//写入全局文件
void objectJson::WriteLocalData(){
    josn_mutex.lock();
    QString localDataFilePath=QApplication::applicationDirPath()+"/data.json";
    json jsonData=nullptr;
    jsonData=DataSerialize(jsonData,g_vekLocalData);
    WriteJsonToFile(localDataFilePath,jsonData);
    josn_mutex.unlock();
}
//写入文件
void objectJson::WriteJsonToFile(QString filePath,json jsonData){
    ofstream out(filePath.toStdString(),ios::binary);
    out<<std::setw(4)<<jsonData;
    out.close();
}

//*********容器数据操作************//
//删除容器节点
void objectJson::deleteDockerNodeData(QString dockName){
    if(g_vekLocalData.map_docker_list.count(dockName)>0){
        g_vekLocalData.map_docker_list.erase(dockName);
    }
    WriteLocalData();
}
//更新容器节点信息
void objectJson::updateDockerNodeData(SdockerData dockData,QString dockName){
    g_vekLocalData.map_docker_list[dockName]=dockData;
    WriteLocalData();
}
//××××××××××××APP信息操作×××××××××××//
//增加app节点
void objectJson::addAppNodeData(SdockerData dockData,SappData appData){
    g_vekLocalData.map_docker_list[dockData.s_dockers_name]=dockData;
    g_vekLocalData.map_docker_list[dockData.s_dockers_name].map_dockers_data[appData.s_uid]=appData;
    WriteLocalData();
}
//删除APP节点
void objectJson::deleteAppNodeData(SdockerData dockData, QString appCID){
    for(auto& h:g_vekLocalData.map_docker_list)
    {
        if(h.first.count(dockData.s_dockers_name)>0){
            if(h.second.map_dockers_data.count(appCID)>0){
                h.second.map_dockers_data.erase(appCID);
                break;
            }
        }
    }
    WriteLocalData();
}
//更新APP节点信息
void objectJson::updateAppNodeData(SdockerData dockData,SappData appData){
    //g_vekLocalData.map_docker_list[dockData.s_dockers_name].map_dockers_data.erase(appData.s_uid);
    addAppNodeData(dockData,appData);
}
//××××××××××××××××Wine信息操作×××××××××××××××××//
//删除Wine节点
void objectJson::deleteWineNodeData(QString nWineName){
    if(g_vekLocalData.map_wine_list.count(nWineName)>0){
        g_vekLocalData.map_wine_list.erase(nWineName);
    }
    WriteLocalData();
}

//更新Wine节点
void objectJson::updateWineNodeData(SwineData _base_wine_data){
    if(_base_wine_data.s_local_wine_name!=nullptr){
        deleteWineNodeData(_base_wine_data.s_local_wine_name);
    }
    g_vekLocalData.map_wine_list[_base_wine_data.s_local_wine_name]=_base_wine_data;
    WriteLocalData();
}
//生成CID
QString objectJson::GetRandomCID()
{
    int max = 32;
    QString tmp = QString("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ");
    QString str;
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    for(int i=0;i<max;i++) {
        int ir = qrand()%tmp.length();
        str[i] = tmp.at(ir);
    }
    qInfo()<<str;
    return str;
}

