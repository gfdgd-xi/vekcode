#include "objectJson.h"

objectJson::objectJson()
{

}
objectJson::~objectJson()
{
}
//增加游戏
json objectJson::DataSerialize(json jsonData,const BaseLocalData _baseLocalData){
    //序列化容器列表
    //ax.first->容器名
    for(auto ax:_baseLocalData.dockerVec){
        //bx.first->游戏CID
        jsonData["Docker"][ax.first.toStdString()][toStr(WineVersion)]=ax.second.WineVersion.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(WinePath)]=ax.second.WinePath.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockerSystemVersion)]=ax.second.DockerSystemVersion.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockerVer)]=ax.second.DockerVer.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockerPath)]=ax.second.DockerPath.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockerName)]=ax.second.DockerName.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockerWineVersion)]=ax.second.DockerWineVersion.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(MonoState)]=ax.second.MonoState;
        jsonData["Docker"][ax.first.toStdString()][toStr(GeckoState)]=ax.second.GeckoState;
        for(auto [bx,by]:ax.second.dData){
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(AppCID)]=by.AppCID.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(AppName)]=by.AppName.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(AppIco)]=by.AppIco.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(AppExe)]=by.AppExe.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DxvkHUD)]=by.DxvkHUD;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DxvkVerson)]=by.DxvkVerson.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DxvkConfigFile)]=by.DxvkConfigFile.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(AppOtherAgrs)]=by.AppOtherAgrs.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(WorkPath)]=by.WorkPath.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(MainPrcoName)]=by.MainPrcoName.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockSysVersion)]=by.DockSysVersion.toStdString();
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(TaskLog)]=by.TaskLog;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DxvkState)]=by.DxvkState;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(WriteCopy)]=by.WriteCopy;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(SharedMemory)]=by.SharedMemory;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(RtServer)]=by.RtServer;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DisableAss)]=by.DisableAss;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DefaultFonts)]=by.DefaultFonts;
            jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DxvkConfigFileState)]=by.DxvkConfigFileState;
            if(!by.DockerEnv.empty()){
                for(auto&[fa,yz]:by.DockerEnv){
                    jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerEnv)][fa.toStdString()]=yz.toStdString();
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerEnv)]=json({});
            }
            if(!by.DockerLibs.empty()){
                for(auto&ya:by.DockerLibs){
                    jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerLibs)].push_back(ya.toStdString());
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerLibs)]=json({});
            }
            if(!by.DockerRegs.empty()){
                int i=-1;
                for(auto a:by.DockerRegs){
                    i+=1;
                    jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rPath)]=a.rPath.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rKey)]=a.rKey.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rValue)]=a.rValue.toStdString();
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(DockerRegs)]=json::array();
            }
            if(!by.AttachProc.empty()){
                for(auto rs:by.AttachProc){
                    jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(AttachProc)].push_back(rs.toStdString());
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][by.AppCID.toStdString()][toStr(AttachProc)]=json::array();
            }
        }
    }
    //禁止修改
    for(auto &k : _baseLocalData.wineVec){
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineName)]=k.second.IwineName.toStdString();
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwinePath)]=k.second.IwinePath.toStdString();
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineVer)]=k.second.IwineVer.toStdString();
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineUrl)]=k.second.IwineUrl.toStdString();
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineSrc)]=k.second.IwineSrc.toStdString();
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineMono)]=k.second.IwineMono.toStdString();
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineGeckoX86)]=k.second.IwineGeckoX86.toStdString();
        jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineGeckoX86_64)]=k.second.IwineGeckoX86_64.toStdString();
        for(auto dx:k.second.IwineDxvk){
            jsonData["Wine"][k.second.IwineName.toStdString()][toStr(IwineDxvk)].push_back(dx.toStdString());
        }
    }
    //序列化数据源数据
    for(auto &[x,y]: _baseLocalData.appScrSource){
        //x 数据源名字
        //y 数据源json url
        //增加数据源
        jsonData["AppScrSource"][x.toStdString()]=y.toStdString();
        //序列化该数据源下所有数据
        for(auto &[a,b]: _baseLocalData.appJsonList){
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
    for(auto &[x,y]: _baseLocalData.wineSource){
        jsonData["WineScrSource"][x.toStdString()]=y.toStdString();
        for(auto&[a,b]:_baseLocalData.wineJsonList){
            if(a==x){
                for(auto& [d,e]:b){
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(WineName)]=e.WineName.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(WineVersion)]=e.WineVersion.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(WineGit)]=e.WineGit.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(Mono)]=e.Mono.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(GeckoX86)]=e.GeckoX86.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(GeckoX86_64)]=e.GeckoX86_64.toStdString();
                    for(auto dy:e.WineDxvk){
                        jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(WineDxvk)].push_back(dy.toStdString());
                    }
                }
            }
        }
    }
    return jsonData;
}

//反序列化到结构
bool objectJson::unDataSerializeLocalData(){
    //解析srt为json
    try
    {
        QString jsonPath=QDir::currentPath()+"/data.json";
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
                    BaseDockData baseDockData={};
                    auto it = bx.begin();
                    for(it=bx.begin();it!=bx.end();++it)
                    {
                        if(it.value().is_string()){
                            baseDockData.WinePath=QString::fromStdString(bx.at(toStr(WinePath)));
                            baseDockData.WineVersion=QString::fromStdString(bx.at(toStr(WineVersion)));
                            baseDockData.DockerPath=QString::fromStdString(bx.at(toStr(DockerPath)));
                            baseDockData.DockerName=QString::fromStdString(bx.at(toStr(DockerName)));
                            baseDockData.DockerSystemVersion=QString::fromStdString(bx.at(toStr(DockerSystemVersion)));
                            baseDockData.DockerVer=QString::fromStdString(bx.at(toStr(DockerVer)));
                            baseDockData.DockerWineVersion=QString::fromStdString(bx.at(toStr(DockerWineVersion)));
                        }
                        if(it.value().is_boolean()){
                            baseDockData.MonoState=bx.at(toStr(MonoState)).get<bool>();
                            baseDockData.GeckoState=bx.at(toStr(GeckoState)).get<bool>();
                        }
                        if(it.value().is_object())
                        {
                            for(auto x:it.value())
                            {
                                BaseAppData _base_app_data={};
                                _base_app_data.AppCID=QString::fromStdString(it.value().at("AppCID"));
                                _base_app_data.AppName=QString::fromStdString(it.value().at("AppName"));
                                _base_app_data.AppExe=QString::fromStdString(it.value().at("AppExe"));
                                _base_app_data.AppIco=QString::fromStdString(it.value().at("AppIco"));
                                _base_app_data.AppOtherAgrs=QString::fromStdString(it.value().at("AppOtherAgrs"));
                                _base_app_data.DxvkVerson=QString::fromStdString(it.value().at("DxvkVerson"));
                                _base_app_data.WorkPath=QString::fromStdString(it.value().at("WorkPath"));
                                _base_app_data.DxvkConfigFile=QString::fromStdString(it.value().at("DxvkConfigFile"));
                                _base_app_data.MainPrcoName=QString::fromStdString(it.value().at("MainPrcoName"));
                                _base_app_data.DockSysVersion=QString::fromStdString(it.value().at("DockSysVersion"));
                                _base_app_data.DxvkState=it.value().at("DxvkState").get<bool>();
                                _base_app_data.DxvkHUD=it.value().at("DxvkHUD").get<bool>();
                                _base_app_data.TaskLog=it.value().at("TaskLog").get<bool>();
                                _base_app_data.WriteCopy=it.value().at("WriteCopy").get<bool>();
                                _base_app_data.SharedMemory=it.value().at("SharedMemory").get<bool>();
                                _base_app_data.RtServer=it.value().at("RtServer").get<bool>();
                                _base_app_data.DefaultFonts=it.value().at("DefaultFonts").get<bool>();
                                _base_app_data.DisableAss=it.value().at("DisableAss").get<bool>();
                                _base_app_data.DxvkConfigFileState=it.value().at("DxvkConfigFileState").get<bool>();
                                _base_app_data.AttachProc.clear();
                                if(it.value().at("AttachProc")!=NULL){
                                    for(auto idx:it.value().at("AttachProc")){
                                        _base_app_data.AttachProc.push_back(QString::fromStdString(idx));
                                    }
                                }
                                _base_app_data.DockerEnv.clear();
                                if(it.value().at("DockerEnv")!=NULL){
                                    for(auto&[vx,vy]:it.value().at("DockerEnv").items()){
                                        _base_app_data.DockerEnv.insert(pair<QString,QString>(QString::fromStdString(vx),QString::fromStdString(vy)));
                                    }
                                }
                                _base_app_data.DockerRegs.clear();
                                if(it.value().at("DockerRegs")!=NULL){
                                    for(auto&wy:it.value().at("DockerRegs")){
                                        BaseDockRegs _rbaseRegs;
                                        _rbaseRegs.rPath=QString::fromStdString(wy.at("rPath"));
                                        _rbaseRegs.rKey=QString::fromStdString(wy.at("rKey"));
                                        _rbaseRegs.rTValue=QString::fromStdString(wy.at("rTValue"));
                                        _rbaseRegs.rValue=QString::fromStdString(wy.at("rValue"));
                                        _base_app_data.DockerRegs.push_back(_rbaseRegs);
                                    }
                                }
                                baseDockData.dData.insert(pair<QString,BaseAppData>(_base_app_data.AppCID,_base_app_data));
                            }
                        }
                    }
                    g_vekLocalData.dockerVec.insert(pair<QString,BaseDockData>(QString::fromStdString(ax),baseDockData));
                }
                //禁止修改
            }else if(k=="Wine"){
                BaseWineData _base_wine_data={};
                for(auto& [x,y]: v.items()){
                    _base_wine_data.IwineName=QString::fromStdString(y.at("IwineName"));
                    _base_wine_data.IwinePath=QString::fromStdString(y.at("IwinePath"));
                    _base_wine_data.IwineVer=QString::fromStdString(y.at("IwineVer"));
                    _base_wine_data.IwineUrl=QString::fromStdString(y.at("IwineUrl"));
                    _base_wine_data.IwineSrc=QString::fromStdString(y.at("IwineSrc"));
                    _base_wine_data.IwineMono=QString::fromStdString(y.at("IwineMono"));
                    _base_wine_data.IwineGeckoX86=QString::fromStdString(y.at("IwineGeckoX86"));
                    _base_wine_data.IwineGeckoX86_64=QString::fromStdString(y.at("IwineGeckoX86_64"));
                    _base_wine_data.IwineDxvk.clear();
                    for(auto yz:y.at("IwineDxvk")){
                        _base_wine_data.IwineDxvk.push_back(QString::fromStdString(yz));
                    }
                    g_vekLocalData.wineVec.insert(pair<QString,BaseWineData>(_base_wine_data.IwineName,_base_wine_data));
                }
            }else if(k=="AppScrSource"){
                //软件数据反序列化
                for(auto [b,c] :v.items())
                {
                    //b源名字
                    g_vekLocalData.appScrSource.insert(pair<QString,QString>(QString::fromStdString(b),QString::fromStdString(c)));
                    for (auto& [d, j] : j3.items())
                    {
                        if(d=="AppJsonList"){

                            for(auto&[u,i]:j.items()){
                                //u 源名字
                                std::map<QString,std::map<QString,BaseAppJson>> appTypeList;
                                for(auto [di,du]:i.items()){
                                    //di app分类名字
                                    //du 分类app列表
                                    std::map<QString,BaseAppJson> appList;
                                    for(auto [dv,dw]:du.items()){
                                        //dv app名字
                                        //dw app数据
                                        BaseAppJson baseAppJson;
                                        baseAppJson.appName=QString::fromStdString(dw.at(toStr(appName)));
                                        baseAppJson.appIco=QString::fromStdString(dw.at(toStr(appIco)));
                                        baseAppJson.appJson=QString::fromStdString(dw.at(toStr(appJson)));
                                        appList.insert(pair<QString,BaseAppJson>(QString::fromStdString(dv),baseAppJson));
                                    }
                                  appTypeList.insert(pair<QString,std::map<QString,BaseAppJson>>(QString::fromStdString(di),appList));
                                }
                                g_vekLocalData.appJsonList.insert(pair<QString,std::map<QString,std::map<QString,BaseAppJson>>>(QString::fromStdString(u),appTypeList));
                                /*
                                if(u==b){
                                    for(auto&[w,o]:i.items()){
                                        g_vekLocalData.appJsonList[QString::fromStdString(u)].insert(pair<QString,QString>(QString::fromStdString(w),QString::fromStdString(o)));
                                    }
                                }
                                */
                            }
                        }
                        //continue;
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
                    g_vekLocalData.wineSource.insert(pair<QString,QString>(QString::fromStdString(b),QString::fromStdString(c)));
                    for (auto& [d, j] : j3.items())
                    {
                        if(d=="WineJsonList"){
                            for(auto&[u,i]:j.items())
                            {
                                if(u==b)
                                {
                                    for(auto& kj:i){
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].WineName=QString::fromStdString(kj.at("WineName"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].WineVersion=QString::fromStdString(kj.at("WineVersion"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].WineGit=QString::fromStdString(kj.at("WineGit"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].Mono=QString::fromStdString(kj.at("Mono"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].GeckoX86=QString::fromStdString(kj.at("GeckoX86"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].GeckoX86_64=QString::fromStdString(kj.at("GeckoX86_64"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].WineDxvk.clear();
                                        for(auto ix:kj.at("WineDxvk"))
                                        {
                                            g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("WineName"))].WineDxvk.push_back(QString::fromStdString(ix));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
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
BaseAutoSetJson* objectJson::unDataSerializeScriptData(BaseAutoSetJson* _baseAutoSetJson,const QString autoJsonData){
    try {
        json js3=json::parse(autoJsonData.toStdString());
        for(auto&[k,j]:js3.items()){
            if(QString::fromStdString(k)=="Option"){
                for(auto&[iu,zu]:j.items()){
                    _baseAutoSetJson->Option.insert(pair<QString,QString>(QString::fromStdString(iu),QString::fromStdString(zu)));
                }
            }
            if(QString::fromStdString(k)=="Docker"){
                for(auto&[ix,zx]:j.items()){
                    _baseAutoSetJson->Docker.insert(pair<QString,QString>(QString::fromStdString(ix),QString::fromStdString(zx)));
                }
            }
            if(QString::fromStdString(k)=="AttachProc"){
                if(!j.empty()){
                    for(auto&zu:j.items()){
                        _baseAutoSetJson->AttachProc.push_back(QString::fromStdString(zu.value()));
                    }
                }
            }
            if(QString::fromStdString(k)=="Env"){
                if(!j.empty()){
                    for(auto&[iu,zu]:j.items()){
                        _baseAutoSetJson->Env.insert(pair<QString,QString>(QString::fromStdString(iu),QString::fromStdString(zu)));
                    }
                }
            }
            if(QString::fromStdString(k)=="Libs"){
                if(!j.empty()){
                    for(auto& d:j.items()){
                        _baseAutoSetJson->Libs.push_back(QString::fromStdString(d.value()));
                    }
                }
            }
            if(QString::fromStdString(k)=="Dxvk"){
                for(auto&[iy,zy]:j.items()){
                    _baseAutoSetJson->Dxvk.insert(pair<QString,QString>(QString::fromStdString(iy),QString::fromStdString(zy)));
                }
            }
            if(QString::fromStdString(k)=="Regs"){
                if(!j.empty()){
                    for(auto ad:j.items()){
                        BaseDockRegs rbaseRegs;
                        rbaseRegs.rPath=QString::fromStdString(ad.value().at("rPath"));
                        rbaseRegs.rKey=QString::fromStdString(ad.value().at("rKey"));
                        rbaseRegs.rTValue=QString::fromStdString(ad.value().at("rTValue"));
                        rbaseRegs.rValue=QString::fromStdString(ad.value().at("rValue"));
                        _baseAutoSetJson->Regs.push_back(rbaseRegs);
                    }
                }
            }
            if(QString::fromStdString(k)=="Args"){
                if(j!=nullptr){
                    _baseAutoSetJson->Args=QString::fromStdString(j);
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
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].WineName=QString::fromStdString(y.at("WineName"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].WineVersion=QString::fromStdString(y.at("WineVersion"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].WineGit=QString::fromStdString(y.at("WineGit"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].Mono=QString::fromStdString(y.at("Mono"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].GeckoX86=QString::fromStdString(y.at("GeckoX86"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].GeckoX86_64=QString::fromStdString(y.at("GeckoX86_64"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].WineDxvk.clear();
                for(auto xz:y.at("WineDxvk")){
                    g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("WineName"))].WineDxvk.push_back(QString::fromStdString(xz));
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
                    g_vekLocalData.appJsonList[key][QString::fromStdString(x)][QString::fromStdString(z)].appName=QString::fromStdString(i.at(toStr(AppName)));
                    g_vekLocalData.appJsonList[key][QString::fromStdString(x)][QString::fromStdString(z)].appIco=QString::fromStdString(i.at(toStr(AppIco)));
                    g_vekLocalData.appJsonList[key][QString::fromStdString(x)][QString::fromStdString(z)].appJson=QString::fromStdString(i.at(toStr(AppJson)));
                }
            }
            break;
        }

    } catch (nullptr_t) {
        return false;
    }
    return true;
}
json objectJson::exportJson(BaseDockData xData,QString AppCID){
    json eJson=nullptr;
    for(auto b:xData.dData){
        if(b.second.AppCID==AppCID){
            eJson[toStr(Option)][toStr(DefaultFont)]=toStr(false);
            eJson[toStr(Option)][toStr(SharedMemory)]=toStr(false);
            eJson[toStr(Option)][toStr(WriteCopy)]=toStr(false);
            eJson[toStr(Option)][toStr(RtServer)]=toStr(false);
            eJson[toStr(Dxvk)][toStr(DxvkState)]=toStr(false);
            eJson[toStr(Dxvk)][toStr(DxvkHUD)]=toStr(false);
            eJson[toStr(Docker)][toStr(MonoState)]=toStr(false);
            eJson[toStr(Docker)][toStr(GeckoState)]=toStr(false);

            if(b.second.DefaultFonts){
                eJson[toStr(Option)][toStr(DefaultFont)]=toStr(true);
            }
            if(b.second.SharedMemory){
                eJson[toStr(Option)][toStr(SharedMemory)]=toStr(true);
            }
            if(b.second.WriteCopy){
                eJson[toStr(Option)][toStr(WriteCopy)]=toStr(true);
            }
            if(b.second.RtServer){
                eJson[toStr(Option)][toStr(RtServer)]=toStr(true);
            }
            if(xData.MonoState){
                eJson[toStr(Docker)][toStr(MonoState)]=toStr(true);
            }
            if(xData.GeckoState){
                eJson[toStr(Docker)][toStr(GeckoState)]=toStr(true);
            }
            if(b.second.DxvkState){
                eJson[toStr(Dxvk)][toStr(DxvkState)]=toStr(true);
            }
            if(b.second.DxvkHUD){
                eJson[toStr(Dxvk)][toStr(DxvkHUD)]=toStr(true);
            }
            eJson[toStr(Option)][toStr(AppName)]=b.second.AppName.toStdString();
            eJson[toStr(Option)][toStr(MainPrcoName)]=b.second.MainPrcoName.toStdString();
            eJson[toStr(Docker)][toStr(DockerSysVersion)]=b.second.DockSysVersion.toStdString();
            eJson[toStr(Docker)][toStr(DockerVersion)]=xData.DockerVer.toStdString();
            eJson[toStr(Docker)][toStr(DockerWineVersion)]=xData.DockerWineVersion.toStdString();
            if(!b.second.AttachProc.empty()){
                for(auto rs:b.second.AttachProc){
                    eJson[toStr(AttachProc)].push_back(rs.toStdString());
                }
            }else{
                eJson[toStr(AttachProc)]=json::array();
            }
            if(!b.second.DockerEnv.empty()){
                for(auto&[fa,yz]:b.second.DockerEnv){
                    eJson[toStr(Env)][fa.toStdString()]=yz.toStdString();
                }
            }else{
                eJson[toStr(Env)]=json({});
            }
            if(!b.second.DockerLibs.empty()){
                for(auto&ya:b.second.DockerLibs){
                    eJson[toStr(Libs)].push_back(ya.toStdString());
                }
            }else{
                eJson[toStr(Libs)]=json::array();
            }
            if(!b.second.DockerRegs.empty()){
                int i=0;
                for(auto a:b.second.DockerRegs){
                    i+=1;
                    eJson[toStr(Regs)][i][toStr(rPath)]=a.rPath.toStdString();
                    eJson[toStr(Regs)][i][toStr(rKey)]=a.rKey.toStdString();
                    eJson[toStr(Regs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                    eJson[toStr(Regs)][i][toStr(rValue)]=a.rValue.toStdString();
                }
            }else{
                eJson[toStr(Regs)]=json::array();
            }
            eJson[toStr(Args)]=b.second.AppOtherAgrs.toStdString();
            eJson[toStr(Dxvk)][toStr(dxvkVersion)]=b.second.DxvkVerson.toStdString();
        }
    }
    return eJson;
}
//×××××××××××数据文件操作××××××××××//
//写入全局文件
void objectJson::WriteLocalData(){
    QString localDataFilePath=QDir::currentPath()+"/data.json";
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
    if(!g_vekLocalData.dockerVec.empty()){
        for(auto a:g_vekLocalData.dockerVec){
            if(a.first==dockName){
                g_vekLocalData.dockerVec.erase(dockName);
                break;
            }
        }
    }
    WriteLocalData();
}
//更新容器节点信息
void objectJson::updateDockerNodeData(BaseDockData dockData,QString dockName){
    if(dockName!=nullptr){
        deleteDockerNodeData(dockName);
    }
    g_vekLocalData.dockerVec.insert(pair<QString,BaseDockData>(dockName,dockData));
    WriteLocalData();
}
//××××××××××××APP信息操作×××××××××××//
//增加app节点
void objectJson::addAppNodeData(BaseDockData dockData,BaseAppData appData){
    g_vekLocalData.dockerVec.insert(pair<QString,BaseDockData>(dockData.DockerName,dockData));
    g_vekLocalData.dockerVec[dockData.DockerName].dData.insert(pair<QString,BaseAppData>(appData.AppCID,appData));
    WriteLocalData();
}
//删除APP节点
void objectJson::deleteAppNodeData(BaseDockData dockData, QString appCID){
    for(auto& h:g_vekLocalData.dockerVec)
    {
        if(dockData.DockerName==h.first){
            for(auto &w:h.second.dData){
                if(w.first==appCID){
                    h.second.dData.erase(appCID);
                    break;
                }
            }
        }
    }
    WriteLocalData();
}
//更新APP节点信息
void objectJson::updateAppNodeData(BaseDockData dockData,BaseAppData appData){
    deleteDockerNodeData(dockData.DockerName);
    addAppNodeData(dockData,appData);
}
//××××××××××××××××Wine信息操作×××××××××××××××××//
//删除Wine节点
void objectJson::deleteWineNodeData(QString nWineName){
    g_vekLocalData.wineVec.erase(nWineName);
    WriteLocalData();
}

//更新Wine节点
void objectJson::updateWineNodeData(BaseWineData _base_wine_data){
    if(_base_wine_data.IwineName!=nullptr){
        deleteWineNodeData(_base_wine_data.IwineName);
    }
    g_vekLocalData.wineVec.insert(pair<QString,BaseWineData>(_base_wine_data.IwineName,_base_wine_data));
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
    qDebug()<<str;
    return str;
}

