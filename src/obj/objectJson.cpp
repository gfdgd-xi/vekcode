#include "objectJson.h"

objectJson::objectJson()
{

}
objectJson::~objectJson()
{
}
//增加游戏
json objectJson::DataSerialize(json jsonData,const LocalData _baseLocalData){
    //序列化容器列表
    //ax.first->容器名
    if(_baseLocalData.local_DockerData.size()>0){
        for(auto ax:_baseLocalData.local_DockerData){
            //bx.first->游戏CID
            jsonData["Docker"][ax.first.toStdString()][toStr(WineVersion)]=ax.second.docker_WineVersion.toStdString();
            jsonData["Docker"][ax.first.toStdString()][toStr(WinePath)]=ax.second.docker_Path.toStdString();
            jsonData["Docker"][ax.first.toStdString()][toStr(DockerSystemVersion)]=ax.second.docker_SystemVersion.toStdString();
            jsonData["Docker"][ax.first.toStdString()][toStr(DockerVer)]=ax.second.docker_SystemBitVersion.toStdString();
            jsonData["Docker"][ax.first.toStdString()][toStr(DockerPath)]=ax.second.docker_Path.toStdString();
            jsonData["Docker"][ax.first.toStdString()][toStr(DockerName)]=ax.second.docker_Name.toStdString();
            jsonData["Docker"][ax.first.toStdString()][toStr(DockerWineVersion)]=ax.second.docker_WineExeVersion.toStdString();
            jsonData["Docker"][ax.first.toStdString()][toStr(MonoState)]=ax.second.docker_MonoState;
            jsonData["Docker"][ax.first.toStdString()][toStr(GeckoState)]=ax.second.docker_GeckoState;
            if(ax.second.docker_Data.size()>0){
                for(auto [bx,by]:ax.second.docker_Data){
                    jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(AppCID)]=by.app_CID.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_Name.toStdString()][toStr(AppName)]=by.app_Name.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_ICO.toStdString()][toStr(AppIco)]=by.app_ICO.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_Exe.toStdString()][toStr(AppExe)]=by.app_Exe.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_DxvkHUD][toStr(DxvkHUD)]=by.app_DxvkHUD;
                    jsonData["Docker"][ax.first.toStdString()][by.app_DxvkVersion.toStdString()][toStr(DxvkVerson)]=by.app_DxvkVersion.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_DxvkConfig.toStdString()][toStr(DxvkConfigFile)]=by.app_DxvkConfig.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_AgrsCode.toStdString()][toStr(AppOtherAgrs)]=by.app_AgrsCode.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_WorkPath.toStdString()][toStr(WorkPath)]=by.app_WorkPath.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_MainProcName.toStdString()][toStr(MainPrcoName)]=by.app_MainProcName.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_SystemVersion.toStdString()][toStr(DockSysVersion)]=by.app_SystemVersion.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.app_TaskLog][toStr(TaskLog)]=by.app_TaskLog;
                    jsonData["Docker"][ax.first.toStdString()][by.app_DxvkState][toStr(DxvkState)]=by.app_DxvkState;
                    jsonData["Docker"][ax.first.toStdString()][by.app_WriteCopy][toStr(WriteCopy)]=by.app_WriteCopy;
                    jsonData["Docker"][ax.first.toStdString()][by.app_SharedMemory][toStr(SharedMemory)]=by.app_SharedMemory;
                    jsonData["Docker"][ax.first.toStdString()][by.app_RtServer][toStr(RtServer)]=by.app_RtServer;
                    jsonData["Docker"][ax.first.toStdString()][by.app_DisableAss][toStr(DisableAss)]=by.app_DisableAss;
                    jsonData["Docker"][ax.first.toStdString()][by.app_DefaultFonts][toStr(DefaultFonts)]=by.app_DefaultFonts;
                    jsonData["Docker"][ax.first.toStdString()][by.app_DxvkConfigFileState][toStr(DxvkConfigFileState)]=by.app_DxvkConfigFileState;
                    if(!by.app_DockerEnv.empty()){
                        for(auto&[fa,yz]:by.app_DockerEnv){
                            jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerEnv)][fa.toStdString()]=yz.toStdString();
                        }
                    }else{
                        jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerEnv)]=json({});
                    }
                    if(!by.app_DockerLibs.empty()){
                        for(auto&ya:by.app_DockerLibs){
                            jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerLibs)].push_back(ya.toStdString());
                        }
                    }else{
                        jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerLibs)]=json({});
                    }
                    if(!by.app_DockerRegs.empty()){
                        int i=-1;
                        for(auto a:by.app_DockerRegs){
                            i+=1;
                            jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerRegs)][i][toStr(rPath)]=a.rPath.toStdString();
                            jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerRegs)][i][toStr(rKey)]=a.rKey.toStdString();
                            jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerRegs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                            jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerRegs)][i][toStr(rValue)]=a.rValue.toStdString();
                        }
                    }else{
                        jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(DockerRegs)]=json::array();
                    }
                    if(!by.app_Attachproc.empty()){
                        for(auto rs:by.app_Attachproc){
                            jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(AttachProc)].push_back(rs.toStdString());
                        }
                    }else{
                        jsonData["Docker"][ax.first.toStdString()][by.app_CID.toStdString()][toStr(AttachProc)]=json::array();
                    }
                }
            }
        }
    }

    //禁止修改
    for(auto &k : _baseLocalData.local_WineData){
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineName)]=k.second.iWineName.toStdString();
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwinePath)]=k.second.iWinePath.toStdString();
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineVer)]=k.second.iWineVer.toStdString();
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineUrl)]=k.second.iWineUrl.toStdString();
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineSrc)]=k.second.iWineSrc.toStdString();
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineMono)]=k.second.iWineMono.toStdString();
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineGeckoX86)]=k.second.iWineGeckoX86.toStdString();
        jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineGeckoX86_64)]=k.second.iWineGeckoX86_64.toStdString();
        for(auto dx:k.second.IwineDxvk){
            jsonData["Wine"][k.second.iWineName.toStdString()][toStr(IwineDxvk)].push_back(dx.toStdString());
        }
    }
    //序列化数据源数据
    for(auto &[x,y]: _baseLocalData.local_AppSrcData){
        //x 数据源名字
        //y 数据源json url
        //增加数据源
        jsonData["AppScrSource"][x.toStdString()]=y.toStdString();
        //序列化该数据源下所有数据
        for(auto &[a,b]: _baseLocalData.local_AppJsonData){
            //a 数据源名字
            //b 数据源下数据
            for(auto&[u,i]:b){
                //u app分类名字
                //i app分类下数据
                for(auto [dx,dc]:i){
                    //dx app名字
                    //dc app数据
                    jsonData["AppJsonList"][a.toStdString()][u.toStdString()][dx.toStdString()][toStr(appName)]=dc.appName.toStdString();
                    jsonData["AppJsonList"][a.toStdString()][u.toStdString()][dx.toStdString()][toStr(appIco)]=dc.appIco.toStdString();
                    jsonData["AppJsonList"][a.toStdString()][u.toStdString()][dx.toStdString()][toStr(appJson)]=dc.appJson.toStdString();
                }
                //jsonData["AppJsonList"][x.toStdString()][u.toStdString()]=i.toStdString();
            }
        }
    }
    /* x a 源名字
     *
     */
    for(auto &[x,y]: _baseLocalData.local_WineSrcData){
        jsonData["WineScrSource"][x.toStdString()]=y.toStdString();
        for(auto&[a,b]:_baseLocalData.local_WineJsonData){
            if(a==x){
                for(auto& [d,e]:b){
                    jsonData["WineJsonList"][x.toStdString()][e.rWineName.toStdString()][toStr(WineName)]=e.rWineName.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.rWineName.toStdString()][toStr(WineVersion)]=e.rWineVersion.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.rWineName.toStdString()][toStr(WineGit)]=e.rWineGit.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.rWineName.toStdString()][toStr(Mono)]=e.rMono.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.rWineName.toStdString()][toStr(GeckoX86)]=e.rGeckoX86.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.rWineName.toStdString()][toStr(GeckoX86_64)]=e.rGeckoX86_64.toStdString();
                    for(auto dy:e.rWineDxvk){
                        jsonData["WineJsonList"][x.toStdString()][e.rWineName.toStdString()][toStr(WineDxvk)].push_back(dy.toStdString());
                    }
                }
            }
        }
    }
    jsonData["Options"]["vekStyle"]=_baseLocalData.local_VekOptions.vekStyle.toStdString();
    jsonData["Options"]["vekLang"]=_baseLocalData.local_VekOptions.vekLang.toStdString();
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
            if(k=="Docker"){
                //ax->容器名 bx->容器下的游戏列表
                for(auto [ax,bx]:v.items()){
                    DockData baseDockData={};
                    auto it = bx.begin();
                    for(it=bx.begin();it!=bx.end();++it)
                    {
                        if(it.value().is_string()){
                            baseDockData.docker_WinePath=QString::fromStdString(bx.at(toStr(WinePath)));
                            baseDockData.docker_WineVersion=QString::fromStdString(bx.at(toStr(WineVersion)));
                            baseDockData.docker_Path=QString::fromStdString(bx.at(toStr(DockerPath)));
                            baseDockData.docker_Name=QString::fromStdString(bx.at(toStr(DockerName)));
                            baseDockData.docker_SystemVersion=QString::fromStdString(bx.at(toStr(DockerSystemVersion)));
                            baseDockData.docker_SystemBitVersion=QString::fromStdString(bx.at(toStr(DockerVer)));
                            baseDockData.docker_WineVersion=QString::fromStdString(bx.at(toStr(DockerWineVersion)));
                        }
                        if(it.value().is_boolean()){
                            baseDockData.docker_MonoState=bx.at(toStr(MonoState)).get<bool>();
                            baseDockData.docker_GeckoState=bx.at(toStr(GeckoState)).get<bool>();
                        }
                        if(it.value().is_object())
                        {
                            for(auto x:it.value())
                            {
                                AppData _base_app_data={};
                                _base_app_data.app_CID=QString::fromStdString(it.value().at("AppCID"));
                                _base_app_data.app_Name=QString::fromStdString(it.value().at("AppName"));
                                _base_app_data.app_Exe=QString::fromStdString(it.value().at("AppExe"));
                                _base_app_data.app_ICO=QString::fromStdString(it.value().at("AppIco"));
                                _base_app_data.app_AgrsCode=QString::fromStdString(it.value().at("AppOtherAgrs"));
                                _base_app_data.app_DxvkVersion=QString::fromStdString(it.value().at("DxvkVerson"));
                                _base_app_data.app_WorkPath=QString::fromStdString(it.value().at("WorkPath"));
                                _base_app_data.app_DxvkConfig=QString::fromStdString(it.value().at("DxvkConfigFile"));
                                _base_app_data.app_MainProcName=QString::fromStdString(it.value().at("MainPrcoName"));
                                _base_app_data.app_SystemVersion=QString::fromStdString(it.value().at("DockSysVersion"));
                                _base_app_data.app_DxvkState=it.value().at("DxvkState").get<bool>();
                                _base_app_data.app_DxvkHUD=it.value().at("DxvkHUD").get<bool>();
                                _base_app_data.app_TaskLog=it.value().at("TaskLog").get<bool>();
                                _base_app_data.app_WriteCopy=it.value().at("WriteCopy").get<bool>();
                                _base_app_data.app_SharedMemory=it.value().at("SharedMemory").get<bool>();
                                _base_app_data.app_RtServer=it.value().at("RtServer").get<bool>();
                                _base_app_data.app_DefaultFonts=it.value().at("DefaultFonts").get<bool>();
                                _base_app_data.app_DisableAss=it.value().at("DisableAss").get<bool>();
                                _base_app_data.app_DxvkConfigFileState=it.value().at("DxvkConfigFileState").get<bool>();
                                _base_app_data.app_Attachproc.clear();
                                if(it.value().at("AttachProc")!=NULL){
                                    for(auto idx:it.value().at("AttachProc")){
                                        _base_app_data.app_Attachproc.push_back(QString::fromStdString(idx));
                                    }
                                }
                                _base_app_data.app_DockerEnv.clear();
                                if(it.value().at("DockerEnv")!=NULL){
                                    for(auto&[vx,vy]:it.value().at("DockerEnv").items()){
                                        _base_app_data.app_DockerEnv[QString::fromStdString(vx)]=QString::fromStdString(vy);
                                    }
                                }
                                _base_app_data.app_DockerRegs.clear();
                                if(it.value().at("DockerRegs")!=NULL){
                                    for(auto&wy:it.value().at("DockerRegs")){
                                        regs _rbaseRegs;
                                        _rbaseRegs.rPath=QString::fromStdString(wy.at("rPath"));
                                        _rbaseRegs.rKey=QString::fromStdString(wy.at("rKey"));
                                        _rbaseRegs.rTValue=QString::fromStdString(wy.at("rTValue"));
                                        _rbaseRegs.rValue=QString::fromStdString(wy.at("rValue"));
                                        _base_app_data.app_DockerRegs.push_back(_rbaseRegs);
                                    }
                                }
                                baseDockData.docker_Data[_base_app_data.app_CID]=_base_app_data;
                            }
                        }
                    }
                    g_vekLocalData.local_DockerData[QString::fromStdString(ax)]=baseDockData;
                }
                //禁止修改
            }
            else if(k=="Wine"){
                WineData _base_wine_data={};
                for(auto& [x,y]: v.items()){
                    _base_wine_data.iWineName=QString::fromStdString(y.at("IwineName"));
                    _base_wine_data.iWinePath=QString::fromStdString(y.at("IwinePath"));
                    _base_wine_data.iWineVer=QString::fromStdString(y.at("IwineVer"));
                    _base_wine_data.iWineUrl=QString::fromStdString(y.at("IwineUrl"));
                    _base_wine_data.iWineSrc=QString::fromStdString(y.at("IwineSrc"));
                    _base_wine_data.iWineMono=QString::fromStdString(y.at("IwineMono"));
                    _base_wine_data.iWineGeckoX86=QString::fromStdString(y.at("IwineGeckoX86"));
                    _base_wine_data.iWineGeckoX86_64=QString::fromStdString(y.at("IwineGeckoX86_64"));
                    _base_wine_data.IwineDxvk.clear();
                    for(auto yz:y.at("IwineDxvk")){
                        _base_wine_data.IwineDxvk.push_back(QString::fromStdString(yz));
                    }
                    g_vekLocalData.local_WineData[_base_wine_data.iWineName]=_base_wine_data;
                }
            }
            else if(k=="AppScrSource"){
                //软件数据反序列化
                for(auto [b,c] :v.items())
                {
                    //b源名字
                    g_vekLocalData.local_AppSrcData[QString::fromStdString(b)]=QString::fromStdString(c);
                    for (auto& [d, j] : j3.items())
                    {
                        if(d=="AppJsonList"){

                            for(auto&[u,i]:j.items()){
                                //u 源名字
                                std::map<QString,std::map<QString,AppJson>> appTypeList;
                                for(auto [di,du]:i.items()){
                                    //di app分类名字
                                    //du 分类app列表
                                    std::map<QString,AppJson> appList;
                                    for(auto [dv,dw]:du.items()){
                                        //dv app名字
                                        //dw app数据
                                        AppJson baseAppJson;
                                        baseAppJson.appName=QString::fromStdString(dw.at(toStr(appName)));
                                        baseAppJson.appIco=QString::fromStdString(dw.at(toStr(appIco)));
                                        baseAppJson.appJson=QString::fromStdString(dw.at(toStr(appJson)));
                                        appList.insert(pair<QString,AppJson>(QString::fromStdString(dv),baseAppJson));
                                    }
                                    appTypeList[QString::fromStdString(di)]=appList;
                                }
                                g_vekLocalData.local_AppJsonData[QString::fromStdString(u)]=appTypeList;
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
                    g_vekLocalData.local_WineSrcData[QString::fromStdString(b)]=QString::fromStdString(c);
                    for (auto& [d, j] : j3.items())
                    {
                        if(d=="WineJsonList"){
                            for(auto&[u,i]:j.items())
                            {
                                if(u==b)
                                {
                                    for(auto& kj:i){
                                        g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rWineName=QString::fromStdString(kj.at("WineName"));
                                        g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rWineVersion=QString::fromStdString(kj.at("WineVersion"));
                                        g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rWineGit=QString::fromStdString(kj.at("WineGit"));
                                        g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rMono=QString::fromStdString(kj.at("Mono"));
                                        g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rGeckoX86=QString::fromStdString(kj.at("GeckoX86"));
                                        g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rGeckoX86_64=QString::fromStdString(kj.at("GeckoX86_64"));
                                        g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rWineDxvk.clear();
                                        for(auto ix:kj.at("WineDxvk"))
                                        {
                                            g_vekLocalData.local_WineJsonData[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].rWineDxvk.push_back(QString::fromStdString(ix));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(k=="Options"){
                g_vekLocalData.local_VekOptions.vekStyle=QString::fromStdString(j3.at("Options").at("vekStyle"));
                g_vekLocalData.local_VekOptions.vekLang=QString::fromStdString(j3.at("Options").at("vekLang"));
            }
        }
        return true;
    }
    catch (nullptr_t)
    {
        return false;
    }

}

//脚本反序列化
AutoJson* objectJson::unDataSerializeScriptData(AutoJson* _baseAutoSetJson,const QString autoJsonData){
    try {
        json js3=json::parse(autoJsonData.toStdString());
        for(auto&[k,j]:js3.items()){
            if(QString::fromStdString(k)=="Option"){
                for(auto&[iu,zu]:j.items()){
                    _baseAutoSetJson->auto_Option[QString::fromStdString(iu)]=QString::fromStdString(zu);
                }
            }
            if(QString::fromStdString(k)=="Docker"){
                for(auto&[ix,zx]:j.items()){
                    _baseAutoSetJson->auto_Docker[QString::fromStdString(ix)]=QString::fromStdString(zx);
                }
            }
            if(QString::fromStdString(k)=="AttachProc"){
                if(!j.empty()){
                    for(auto&zu:j.items()){
                        _baseAutoSetJson->app_Attachproc.push_back(QString::fromStdString(zu.value()));
                    }
                }
            }
            if(QString::fromStdString(k)=="Env"){
                if(!j.empty()){
                    for(auto&[iu,zu]:j.items()){
                        _baseAutoSetJson->auto_Env[QString::fromStdString(iu)]=QString::fromStdString(zu);
                    }
                }
            }
            if(QString::fromStdString(k)=="Libs"){
                if(!j.empty()){
                    for(auto& d:j.items()){
                        _baseAutoSetJson->auto_Libs.push_back(QString::fromStdString(d.value()));
                    }
                }
            }
            if(QString::fromStdString(k)=="Dxvk"){
                for(auto&[iy,zy]:j.items()){
                    _baseAutoSetJson->auto_Dxvk[QString::fromStdString(iy)]=QString::fromStdString(zy);
                }
            }
            if(QString::fromStdString(k)=="Regs"){
                if(!j.empty()){
                    for(auto ad:j.items()){
                        regs rbaseRegs;
                        rbaseRegs.rPath=QString::fromStdString(ad.value().at("rPath"));
                        rbaseRegs.rKey=QString::fromStdString(ad.value().at("rKey"));
                        rbaseRegs.rTValue=QString::fromStdString(ad.value().at("rTValue"));
                        rbaseRegs.rValue=QString::fromStdString(ad.value().at("rValue"));
                        _baseAutoSetJson->auto_Regs.push_back(rbaseRegs);
                    }
                }
            }
            if(QString::fromStdString(k)=="Args"){
                if(j!=nullptr){
                    _baseAutoSetJson->auto_Args=QString::fromStdString(j);
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
                g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rWineName=QString::fromStdString(y.at("WineName"));
                g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rWineVersion=QString::fromStdString(y.at("WineVersion"));
                g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rWineGit=QString::fromStdString(y.at("WineGit"));
                g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rMono=QString::fromStdString(y.at("Mono"));
                g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rGeckoX86=QString::fromStdString(y.at("GeckoX86"));
                g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rGeckoX86_64=QString::fromStdString(y.at("GeckoX86_64"));
                g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rWineDxvk.clear();
                for(auto xz:y.at("WineDxvk")){
                    g_vekLocalData.local_WineJsonData[key][QString::fromStdString(y.at("WineName"))].rWineDxvk.push_back(QString::fromStdString(xz));
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
                    g_vekLocalData.local_AppJsonData[key][QString::fromStdString(x)][QString::fromStdString(z)].appName=QString::fromStdString(i.at(toStr(AppName)));
                    g_vekLocalData.local_AppJsonData[key][QString::fromStdString(x)][QString::fromStdString(z)].appIco=QString::fromStdString(i.at(toStr(AppIco)));
                    g_vekLocalData.local_AppJsonData[key][QString::fromStdString(x)][QString::fromStdString(z)].appJson=QString::fromStdString(i.at(toStr(AppJson)));
                }
            }
            break;
        }

    } catch (nullptr_t) {
        return false;
    }
    return true;
}
json objectJson::exportJson(DockData xData,QString AppCID){
    json eJson=nullptr;
    for(auto b:xData.docker_Data){
        if(b.second.app_CID==AppCID){
            eJson[toStr(Option)][toStr(DefaultFont)]=toStr(false);
            eJson[toStr(Option)][toStr(SharedMemory)]=toStr(false);
            eJson[toStr(Option)][toStr(WriteCopy)]=toStr(false);
            eJson[toStr(Option)][toStr(RtServer)]=toStr(false);
            eJson[toStr(Dxvk)][toStr(DxvkState)]=toStr(false);
            eJson[toStr(Dxvk)][toStr(DxvkHUD)]=toStr(false);
            eJson[toStr(Docker)][toStr(MonoState)]=toStr(false);
            eJson[toStr(Docker)][toStr(GeckoState)]=toStr(false);

            if(b.second.app_DefaultFonts){
                eJson[toStr(Option)][toStr(DefaultFont)]=toStr(true);
            }
            if(b.second.app_SharedMemory){
                eJson[toStr(Option)][toStr(SharedMemory)]=toStr(true);
            }
            if(b.second.app_WriteCopy){
                eJson[toStr(Option)][toStr(WriteCopy)]=toStr(true);
            }
            if(b.second.app_RtServer){
                eJson[toStr(Option)][toStr(RtServer)]=toStr(true);
            }
            if(xData.docker_MonoState){
                eJson[toStr(Docker)][toStr(MonoState)]=toStr(true);
            }
            if(xData.docker_GeckoState){
                eJson[toStr(Docker)][toStr(GeckoState)]=toStr(true);
            }
            if(b.second.app_DxvkState){
                eJson[toStr(Dxvk)][toStr(DxvkState)]=toStr(true);
            }
            if(b.second.app_DxvkHUD){
                eJson[toStr(Dxvk)][toStr(DxvkHUD)]=toStr(true);
            }
            eJson[toStr(Option)][toStr(AppName)]=b.second.app_Name.toStdString();
            eJson[toStr(Option)][toStr(MainPrcoName)]=b.second.app_MainProcName.toStdString();
            eJson[toStr(Docker)][toStr(DockerSysVersion)]=b.second.app_SystemVersion.toStdString();
            eJson[toStr(Docker)][toStr(DockerVersion)]=xData.docker_SystemVersion.toStdString();
            eJson[toStr(Docker)][toStr(DockerWineVersion)]=xData.docker_WineVersion.toStdString();
            if(!b.second.app_Attachproc.empty()){
                for(auto rs:b.second.app_Attachproc){
                    eJson[toStr(AttachProc)].push_back(rs.toStdString());
                }
            }else{
                eJson[toStr(AttachProc)]=json::array();
            }
            if(!b.second.app_DockerEnv.empty()){
                for(auto&[fa,yz]:b.second.app_DockerEnv){
                    eJson[toStr(Env)][fa.toStdString()]=yz.toStdString();
                }
            }else{
                eJson[toStr(Env)]=json({});
            }
            if(!b.second.app_DockerLibs.empty()){
                for(auto&ya:b.second.app_DockerLibs){
                    eJson[toStr(Libs)].push_back(ya.toStdString());
                }
            }else{
                eJson[toStr(Libs)]=json::array();
            }
            if(!b.second.app_DockerRegs.empty()){
                int i=0;
                for(auto a:b.second.app_DockerRegs){
                    i+=1;
                    eJson[toStr(Regs)][i][toStr(rPath)]=a.rPath.toStdString();
                    eJson[toStr(Regs)][i][toStr(rKey)]=a.rKey.toStdString();
                    eJson[toStr(Regs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                    eJson[toStr(Regs)][i][toStr(rValue)]=a.rValue.toStdString();
                }
            }else{
                eJson[toStr(Regs)]=json::array();
            }
            eJson[toStr(Args)]=b.second.app_AgrsCode.toStdString();
            eJson[toStr(Dxvk)][toStr(dxvkVersion)]=b.second.app_DxvkVersion.toStdString();
        }
    }
    return eJson;
}
//×××××××××××数据文件操作××××××××××//
//写入全局文件
void objectJson::WriteLocalData(){
    QString localDataFilePath=QApplication::applicationDirPath()+"/data.json";
    json jsonData=nullptr;
    jsonData=DataSerialize(jsonData,g_vekLocalData);
    WriteJsonToFile(localDataFilePath,jsonData);
}
//写入文件
void objectJson::WriteJsonToFile(QString filePath,json jsonData){
    ofstream out;
    out.open(filePath.toStdString(),fstream::in | fstream::out | fstream::trunc);
    out<<jsonData;
    cout<<"Json Output:"<<jsonData<<endl;
    out.close();
}

//*********容器数据操作************//
//删除容器节点
void objectJson::deleteDockerNodeData(QString dockName){
    if(g_vekLocalData.local_DockerData.count(dockName)>0){
        g_vekLocalData.local_DockerData.erase(dockName);
    }
    WriteLocalData();
}
//更新容器节点信息
void objectJson::updateDockerNodeData(DockData dockData,QString dockName){
    g_vekLocalData.local_DockerData[dockName]=dockData;
    WriteLocalData();
}
//××××××××××××APP信息操作×××××××××××//
//增加app节点
void objectJson::addAppNodeData(DockData dockData,AppData appData){
    g_vekLocalData.local_DockerData[dockData.docker_Name]=dockData;
    g_vekLocalData.local_DockerData[dockData.docker_Name].docker_Data[appData.app_CID]=appData;
    WriteLocalData();
}
//删除APP节点
void objectJson::deleteAppNodeData(DockData dockData, QString appCID){
    for(auto& h:g_vekLocalData.local_DockerData)
    {
        if(h.first.count(dockData.docker_Name)>0){
            if(h.second.docker_Data.count(appCID)>0){
                h.second.docker_Data.erase(appCID);
                break;
            }
        }
    }
    WriteLocalData();
}
//更新APP节点信息
void objectJson::updateAppNodeData(DockData dockData,AppData appData){
    addAppNodeData(dockData,appData);
}
//××××××××××××××××Wine信息操作×××××××××××××××××//
//删除Wine节点
void objectJson::deleteWineNodeData(QString nWineName){
    if(g_vekLocalData.local_WineData.count(nWineName)>0){
        g_vekLocalData.local_WineData.erase(nWineName);
    }
    WriteLocalData();
}

//更新Wine节点
void objectJson::updateWineNodeData(WineData _base_wine_data){
    if(_base_wine_data.iWineName!=nullptr){
        deleteWineNodeData(_base_wine_data.iWineName);
    }
    g_vekLocalData.local_WineData[_base_wine_data.iWineName]=_base_wine_data;
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

