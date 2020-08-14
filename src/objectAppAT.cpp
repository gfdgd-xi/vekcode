#include "objectAppAT.h"

objectAppAT::objectAppAT()
{
}

objectAppAT::~objectAppAT(){
    delete _baseAutoSetJson;
    _baseAutoSetJson=nullptr;
}
QString objectAppAT::jsonPathTypeToStr(QString jsonPathFile){
    try {
        QString jsonDataStr=nullptr;
        if(jsonPathFile.contains("http",Qt::CaseSensitive)||jsonPathFile.contains("https",Qt::CaseSensitive)){
            vekGetCurl* _vekgetcurl=new vekGetCurl();
            jsonDataStr=QString::fromStdString(_vekgetcurl->vekGetData(jsonPathFile.toStdString()));
            delete _vekgetcurl;
            _vekgetcurl=nullptr;
        }else{
            QFile file(jsonPathFile);
            if(!file.exists())
            {
                return nullptr;
            }
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            jsonDataStr = file.readAll();
            file.close();
        }
        if(jsonDataStr=="error"||jsonDataStr==nullptr){
            return nullptr;
        }
        return jsonDataStr;
    } catch (nullopt_t) {
        return nullptr;
    }
}
bool objectAppAT::jsonUnserialize(QString jsonPathFile){
    QString jsonData=jsonPathTypeToStr(jsonPathFile);
    if(jsonData==nullptr){
        return false;
    }
    objectJson _objectJson;
    if(_objectJson.unDataSerializeScriptData(_baseAutoSetJson,jsonData)==nullptr){
        return false;
    }
    return true;
}
bool objectAppAT::objDockerData(QString dockName){
    bool dockState=false;
    for(auto a:g_vekLocalData.dockerVec){
        if(a.first==dockName){
            dockState=true;
            baseDockData=a.second;
            break;
        }
    }
    //if docker exits
    if(dockState){
        if(baseDockData.DockerVer!=_baseAutoSetJson->Docker.at(toStr(DockerVersion))){
            vekError("当前容器版本为:"+baseDockData.DockerVer+"配置文件容器版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerVersion)));
            return false;
        }
        if(baseDockData.DockerSystemVersion!=_baseAutoSetJson->Docker.at(toStr(DockerSystemVersion))){
            vekError("当前容器系统版本为:"+baseDockData.DockerSystemVersion+"配置文件容器系统版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerSystemVersion)));
            return false;
        }
        if(baseDockData.WineVersion!=_baseAutoSetJson->Docker.at(toStr(WineVersion))){
            vekError("当前容器Wine版本为:"+baseDockData.WineVersion+"配置文件容器Wine版本为:"+_baseAutoSetJson->Docker.at(toStr(WineVersion)));
            return false;
        }
    }else{
        //设置wine版本和路径
        for(auto &x : g_vekLocalData.wineVec){
            if(x.first==_objAddDataAT.pWineVersion){
                baseDockData.WineVersion=x.second.IwineVer;
                baseDockData.WinePath=x.second.IwinePath;
                break;
            }
        }
        if(_baseAutoSetJson->Docker.at(toStr(DockerVersion))!=NULL){
            baseDockData.DockerVer=_baseAutoSetJson->Docker.at(toStr(DockerVersion));
        }
        if(_baseAutoSetJson->Docker.at(toStr(DockerWineVersion))!=NULL){
            baseDockData.WineVersion=_baseAutoSetJson->Docker.at(toStr(DockerWineVersion));
        }
        if(_baseAutoSetJson->Docker.at(toStr(DockerSysVersion))!=NULL){
            baseDockData.DockerSystemVersion=_baseAutoSetJson->Docker.at(toStr(DockerSysVersion));
        }
        if(_baseAutoSetJson->Docker.at(toStr(MonoState))!=NULL){
            QVariant monoState=_baseAutoSetJson->Docker.at(toStr(MonoState));
            baseDockData.MonoState=(monoState).toBool();;
        }
        if(_baseAutoSetJson->Docker.at(toStr(GeckoState))!=NULL){
            QVariant geckoState=_baseAutoSetJson->Docker.at(toStr(GeckoState));
            baseDockData.GeckoState=(geckoState).toBool();;
        }
        baseDockData.DockerPath=_objAddDataAT.pDockPath;
        baseDockData.DockerName=_objAddDataAT.pDockName;
    }
    return true;
}
void objectAppAT::objAppData(){
    if(!_baseAutoSetJson->Option.empty()){
        for(auto a:_baseAutoSetJson->Option){
            if(a.first=="AppName"){
                baseAppData.AppName=a.second;
            }

            if(a.first=="DefaultFont"){
                QVariant defaultFontValue=a.second;
                baseAppData.DefaultFonts=(defaultFontValue).toBool();
            }
            if(a.first=="SharedMemory"){
                QVariant sharedMemoryValue=a.second;
                baseAppData.TaskMemorySharing=(sharedMemoryValue).toBool();
            }
            if(a.first=="WriteCopy"){
                QVariant writeCopyValue=a.second;
                baseAppData.TaskMemoryOptimization=(writeCopyValue).toBool();
            }
            if(a.first=="RtServer"){
                QVariant rtServerValue=a.second;
                baseAppData.TaskRealTimePriority=(rtServerValue).toBool();
            }

            if(a.first=="MainPrcoName"){
                baseAppData.MainPrcoName=a.second;
            }
        }
    }
    if(!_baseAutoSetJson->Dxvk.empty()){
        for(auto a:_baseAutoSetJson->Dxvk){
            if(a.first=="DxvkVersion"){
                baseAppData.DxvkVerson=a.second;
            }
            if(a.first=="DxvkState"){
                QVariant dxvkStateValue=a.second;
                baseAppData.DxvkState=(dxvkStateValue).toBool();
            }
            if(a.first=="DxvkHUD"){
                QVariant dxvkHUDValue=a.second;
                baseAppData.DxvkHUD=(dxvkHUDValue).toBool();
            }
        }
    }
    if(!_baseAutoSetJson->Regs.empty()){
        baseAppData.DockerRegs=_baseAutoSetJson->Regs;
    }
    if(!_baseAutoSetJson->Libs.empty()){
        baseAppData.DockerLibs=_baseAutoSetJson->Libs;
    }
    if(!_baseAutoSetJson->Env.empty()){
        baseAppData.DockerEnv=_baseAutoSetJson->Env;
    }
    if(_baseAutoSetJson->Args!=nullptr){
        baseAppData.AppOtherAgrs=_baseAutoSetJson->Args;
    }
    if(!_baseAutoSetJson->AttachProc.empty()){
        baseAppData.AttachProc=_baseAutoSetJson->AttachProc;
    }

    baseAppData.AppExe=_objAddDataAT.pAppExePath;
    QFileInfo fi = QFileInfo(_objAddDataAT.pAppExePath);
    baseAppData.WorkPath=fi.path();
    objectJson* _objectJson=new objectJson();
    baseAppData.AppCID=_objectJson->GetRandomCID();
    delete _objectJson;
    _objectJson=nullptr;
    baseAppData.AppIco=":/res/img/vek.ico";
}
void objectAppAT::objectAutoObj(){
    if(objDiyAddApp!=nullptr){
        delete objDiyAddApp;
        objDiyAddApp=nullptr;
    }
    emit Tips("配置容器中请稍候!");
    objDiyAddApp=new objectAppMT(&baseAppData,nullptr);
    objDiyAddApp->InitDockObj(false);
    objDiyAddApp->optionRegs();
    objDiyAddApp->DockLibsInstall();
    objDiyAddApp->SaveDataToJson(baseDockData.DockerName,baseAppData);
    delete objDiyAddApp;
    objDiyAddApp=nullptr;
}
void objectAppAT::run(){
    _baseAutoSetJson=new BaseAutoSetJson();
    if(!jsonUnserialize(_objAddDataAT.pJsonPath)){
        emit Error("配置容器出错!",true);
        return;
    }
    else
    {
        if(objDockerData(_objAddDataAT.pDockName)){
            objAppData();
        }else
        {
            emit Error("配置容器出错!",true);
            return;
        }
    }
    objectAutoObj();
    emit Done();
}
