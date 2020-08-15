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
    for(auto ax:g_vekLocalData.dockerVec){
        //bx.first->游戏CID
        jsonData["Docker"][ax.first.toStdString()][toStr(WineVersion)]=ax.second.WineVersion.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(WinePath)]=ax.second.WinePath.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockSystemVersion)]=ax.second.DockerSystemVersion.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockVer)]=ax.second.DockerVer.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockPath)]=ax.second.DockerPath.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockName)]=ax.second.DockerName.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(DockerWineVersion)]=ax.second.DockerWineVersion.toStdString();
        jsonData["Docker"][ax.first.toStdString()][toStr(MonoState)]=ax.second.MonoState;
        jsonData["Docker"][ax.first.toStdString()][toStr(GeckoState)]=ax.second.GeckoState;
        for(auto bx:ax.second.dData){
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(AppCID)]=bx.second.AppCID.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(AppName)]=bx.second.AppName.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(AppIco)]=bx.second.AppIco.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(AppExe)]=bx.second.AppExe.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DxvkHUD)]=bx.second.DxvkHUD;
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DxvkVerson)]=bx.second.DxvkVerson.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DxvkConfigFile)]=bx.second.DxvkConfigFile.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(AppOtherAgrs)]=bx.second.AppOtherAgrs.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(WorkPath)]=bx.second.WorkPath.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(MainPrcoName)]=bx.second.MainPrcoName.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(TaskLog)]=bx.second.TaskLog;
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DxvkState)]=bx.second.DxvkState;
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(TaskMemoryOptimization)]=bx.second.TaskMemoryOptimization;
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(TaskMemorySharing)]=bx.second.TaskMemorySharing;
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(TaskRealTimePriority)]=bx.second.TaskRealTimePriority;
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DefaultFonts)]=bx.second.DefaultFonts;
            jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DxvkConfigFileState)]=bx.second.DxvkConfigFileState;
            if(!bx.second.DockerEnv.empty()){
                for(auto&[fa,yz]:bx.second.DockerEnv){
                    jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerEnv)][fa.toStdString()]=yz.toStdString();
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerEnv)]=json({});
            }
            if(!bx.second.DockerLibs.empty()){
                for(auto&ya:bx.second.DockerLibs){
                    jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerLibs)].push_back(ya.toStdString());
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerLibs)]=json({});
            }
            if(!bx.second.DockerRegs.empty()){
                int i=-1;
                for(auto a:bx.second.DockerRegs){
                    i+=1;
                    jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rPath)]=a.rPath.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rKey)]=a.rKey.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerRegs)][i][toStr(rValue)]=a.rValue.toStdString();
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(DockerRegs)]=json::array();
            }
            if(!bx.second.AttachProc.empty()){
                for(auto rs:bx.second.AttachProc){
                    jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(AttachProc)].push_back(rs.toStdString());
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.AppCID.toStdString()][toStr(AttachProc)]=json::array();
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
    for(auto &[x,y]: _baseLocalData.appScrSource){
        jsonData["AppScrSource"][x.toStdString()]=y.toStdString();
        for(auto &[a,b]: _baseLocalData.appJsonList){
            for(auto&[u,i]:b){
                jsonData["AppJsonList"][x.toStdString()][u.toStdString()]=i.toStdString();
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
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(rWineName)]=e.WineName.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(rWineVersion)]=e.WineVersion.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(rWineGit)]=e.WineGit.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(rMono)]=e.Mono.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(rGeckoX86)]=e.GeckoX86.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.WineName.toStdString()][toStr(rGeckoX86_64)]=e.GeckoX86_64.toStdString();
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
                    baseDockData.WinePath=QString::fromStdString(bx.at("WinePath"));
                    baseDockData.WineVersion=QString::fromStdString(bx.at("WineVersion"));
                    baseDockData.DockerPath=QString::fromStdString(bx.at("DockerPath"));
                    baseDockData.DockerName=QString::fromStdString(bx.at("DockerName"));
                    baseDockData.DockerSystemVersion=QString::fromStdString(bx.at("DockerSystemVersion"));
                    baseDockData.DockerVer=QString::fromStdString(bx.at("DockerVer"));
                    baseDockData.DockerWineVersion=QString::fromStdString(bx.at("DockerWineVersion"));
                    baseDockData.MonoState=bx.at("MonoState");
                    baseDockData.GeckoState=bx.at("GeckoState");
                    //cx->游戏CID bx->游戏数据
                    for(auto [cx,dx]:bx.at("dData").items()){
                        BaseAppData _base_app_data={};
                        _base_app_data.AppCID=QString::fromStdString(dx.at("AppCID"));
                        _base_app_data.AppName=QString::fromStdString(dx.at("AppName"));
                        _base_app_data.AppExe=QString::fromStdString(dx.at("AppExe"));
                        _base_app_data.AppIco=QString::fromStdString(dx.at("AppIco"));
                        _base_app_data.AppOtherAgrs=QString::fromStdString(dx.at("AppOtherAgrs"));
                        _base_app_data.DxvkVerson=QString::fromStdString(dx.at("DxvkVerson"));
                        _base_app_data.WorkPath=QString::fromStdString(dx.at("WorkPath"));
                        _base_app_data.DxvkConfigFile=QString::fromStdString(dx.at("DxvkConfigFile"));
                        _base_app_data.MainPrcoName=QString::fromStdString(dx.at("MainPrcoName"));
                        _base_app_data.DxvkState=dx.at("DxvkState");
                        _base_app_data.DxvkHUD=dx.at("DxvkHUD");
                        _base_app_data.TaskLog=dx.at("TaskLog");
                        _base_app_data.TaskMemoryOptimization=dx.at("TaskMemoryOptimization");
                        _base_app_data.TaskMemorySharing=dx.at("TaskMemorySharing");
                        _base_app_data.TaskRealTimePriority=dx.at("TaskRealTimePriority");
                        _base_app_data.DefaultFonts=dx.at("DefaultFonts");
                        _base_app_data.DxvkConfigFileState=dx.at("DxvkConfigFileState");
                        _base_app_data.AttachProc.clear();
                        if(dx.at("AttachProc")!=NULL){
                            for(auto idx:dx.at("AttachProc")){
                                _base_app_data.AttachProc.push_back(QString::fromStdString(idx));
                            }
                        }else{
                            _base_app_data.AttachProc={};
                        }
                        _base_app_data.DockerEnv.clear();
                        if(dx.at("DockerEnv")!=NULL){
                            for(auto&[vx,vy]:dx.at("DockerEnv").items()){
                                _base_app_data.DockerEnv.insert(pair<QString,QString>(QString::fromStdString(vx),QString::fromStdString(vy)));
                            }
                        }else{
                            _base_app_data.DockerEnv={};
                        }
                        _base_app_data.DockerRegs.clear();
                        if(dx.at("DockerRegs")!=NULL){
                            for(auto&wy:dx.at("DockerRegs")){
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
                for(auto &[b, c] :v.items())
                {
                    g_vekLocalData.appScrSource.insert(pair<QString,QString>(QString::fromStdString(b),QString::fromStdString(c)));
                    for (auto& [d, j] : j3.items())
                    {
                        if(d=="AppJsonList"){
                            for(auto&[u,i]:j.items()){
                                if(u==b){
                                    for(auto&[w,o]:i.items()){
                                        g_vekLocalData.appJsonList[QString::fromStdString(u)].insert(pair<QString,QString>(QString::fromStdString(w),QString::fromStdString(o)));
                                    }
                                }
                            }
                        }
                        continue;
                    }
                }
            }
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
                                    for(auto& kj:i)
                                    {
                                        qDebug()<<QString::fromStdString(kj);
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
BaseAutoSetJson* objectJson::unDataSerializeScriptData(BaseAutoSetJson* _baseAutoSetJson,QString autoJsonData){
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
                }else{
                    _baseAutoSetJson->AttachProc={};
                }

            }
            if(QString::fromStdString(k)=="Env"){
                if(!j.empty()){
                    for(auto&[iu,zu]:j.items()){
                        _baseAutoSetJson->Env.insert(pair<QString,QString>(QString::fromStdString(iu),QString::fromStdString(zu)));
                    }
                }else{
                    _baseAutoSetJson->Env={};
                }

            }
            if(QString::fromStdString(k)=="Libs"){
                if(!j.empty()){
                    for(auto& d:j.items()){
                        _baseAutoSetJson->Libs.push_back(QString::fromStdString(d.value()));
                    }
                }else{
                    _baseAutoSetJson->Libs={};
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
                }else{
                    _baseAutoSetJson->Regs={};
                }
            }
            if(QString::fromStdString(k)=="Args"){
                _baseAutoSetJson->Args=QString::fromStdString(j);
            }
        }
    } catch (nullptr_t) {
        _baseAutoSetJson=nullptr;
    }
    return _baseAutoSetJson;
}
//反序列化列表
bool objectJson::unSerializeLocalWineApp(QString key,QString urlData,UNJSONTYPE jsonType){
    json jdata=json::parse(urlData.toStdString());
    try {
        switch (jsonType) {
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
        case unJsonGameList:
            for(auto &[x, y] :jdata.items())
            {
                g_vekLocalData.appJsonList[key][QString::fromStdString(x)]=QString::fromStdString(y);
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
                eJson[toStr(Option)][toStr(TrServer)]=toStr(false);
                eJson[toStr(Option)][toStr(MonoState)]=toStr(false);
                eJson[toStr(Option)][toStr(GeckoState)]=toStr(false);
                eJson[toStr(Dxvk)][toStr(DxvkState)]=toStr(false);
                eJson[toStr(Dxvk)][toStr(DxvkHUD)]=toStr(false);
                if(b.second.DefaultFonts){
                    eJson[toStr(Option)][toStr(DefaultFont)]=toStr(true);
                }
                if(b.second.TaskMemorySharing){
                    eJson[toStr(Option)][toStr(TaskMemorySharing)]=toStr(true);
                }
                if(b.second.TaskMemoryOptimization){
                    eJson[toStr(Option)][toStr(TaskMemoryOptimization)]=toStr(true);
                }
                if(b.second.TaskRealTimePriority){
                    eJson[toStr(Option)][toStr(TaskRealTimePriority)]=toStr(true);
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
                eJson[toStr(Option)][toStr(DockSystemVersion)]=xData.DockerSystemVersion.toStdString();
                eJson[toStr(Option)][toStr(DockVer)]=xData.DockerVer.toStdString();
                eJson[toStr(Option)][toStr(WineVersion)]=xData.WineVersion.toStdString();
                eJson[toStr(Option)][toStr(MainPrcoName)]=b.second.MainPrcoName.toStdString();
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
                    int i=-1;
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
//写入文件
void objectJson::WriteJsonToFile(QString filePath,json jsonData){
    ofstream out;
    out.open(filePath.toStdString(),fstream::in | fstream::out | fstream::trunc);
    out<<jsonData;
    cout<<"Json Output:"<<jsonData<<endl;
    out.close();
}

//写入全局文件
void objectJson::WriteLocalData(){
    QString localDataFilePath=QDir::currentPath()+"/data.json";
    json jsonData=nullptr;
    jsonData=DataSerialize(jsonData,g_vekLocalData);
    WriteJsonToFile(localDataFilePath,jsonData);
}
//删除游戏节点
void objectJson::deleteAppNodeData(QString nAppCID){
    for(auto& h:g_vekLocalData.dockerVec){
        for(auto &w:h.second.dData){
            if(w.second.AppCID==nAppCID){
                h.second.dData.erase(nAppCID);
                break;
            }
        }
    }
    WriteLocalData();
}
//删除Wine节点
void objectJson::deleteWineNodeData(QString nWineName){
    for(auto &h : g_vekLocalData.wineVec){
        if(h.first==nWineName){
            g_vekLocalData.wineVec.erase(nWineName);
            break;
        }
    }
    WriteLocalData();
}
//更新或者增加Game节点
void objectJson::updateAppNodeData(QString dockName,BaseAppData _base_app_data){
    if(_base_app_data.AppCID!=nullptr){
        deleteAppNodeData(_base_app_data.AppCID);
    }
    g_vekLocalData.dockerVec[dockName].dData.insert(pair<QString,BaseAppData>(_base_app_data.AppCID,_base_app_data));
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

