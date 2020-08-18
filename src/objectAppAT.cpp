#include "objectAppAT.h"

objectAppAT::objectAppAT()
{
}

objectAppAT::~objectAppAT(){
    delete _baseAutoSetJson;
    _baseAutoSetJson=nullptr;
}
void objectAppAT::connectDockAutoData(BaseDockData _dockData,BaseAppData _appData,QString _jsonCfg){
      baseAppData=_appData;
      baseDockData=_dockData;
      jsonCfg=_jsonCfg;
}
bool objectAppAT::JsonType(QString str){
    //查看jsonPaht头是否为http或者https
    if(jsonCfg.startsWith("http",Qt::CaseSensitive)){
        return true;;
    }
    if(str.startsWith("https",Qt::CaseSensitive)){
        return true;
    }
    //本地json
    if(str.endsWith("json",Qt::CaseSensitive)){
        return true;
    }
    //源名字json
    for(auto & v:g_vekLocalData.appJsonList){
        if(v.first==str){
            for(auto & y:v.second){
                if(y.first==str){
                    jsonCfg=y.second;
                    return true;
                    break;
                }
            }
        }
    }
    return false;
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
        if(baseDockData.DockerWineVersion!=_baseAutoSetJson->Docker.at(toStr(DockerWineVersion))){
            vekError("当前容器Wine版本为:"+baseDockData.DockerWineVersion+"配置文件容器Wine版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerWineVersion)));
            return false;
        }
    }else{
        //设置wine版本和路径
        baseDockData.WineVersion=g_vekLocalData.wineVec.at(baseDockData.WineVersion).IwineVer;
        baseDockData.WinePath=g_vekLocalData.wineVec.at(baseDockData.WineVersion).IwinePath;
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
    }
    return true;
}
void objectAppAT::objAppData(){
    if(!_baseAutoSetJson->Option.empty()){
        for(auto [a,b]:_baseAutoSetJson->Option){
            if(a=="AppName"){
                baseAppData.AppName=b;
            }
            if(a=="DefaultFont"){
                QVariant defaultFontValue=b;
                baseAppData.DefaultFonts=(defaultFontValue).toBool();
            }
            if(a=="SharedMemory"){
                QVariant sharedMemoryValue=b;
                baseAppData.SharedMemory=(sharedMemoryValue).toBool();
            }
            if(a=="WriteCopy"){
                QVariant writeCopyValue=b;
                baseAppData.WriteCopy=(writeCopyValue).toBool();
            }
            if(a=="RtServer"){
                QVariant rtServerValue=b;
                baseAppData.RtServer=(rtServerValue).toBool();
            }

            if(a=="MainPrcoName"){
                baseAppData.MainPrcoName=b;
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
    baseAppData.DockerRegs=_baseAutoSetJson->Regs;
    baseAppData.DockerLibs=_baseAutoSetJson->Libs;
    baseAppData.DockerEnv=_baseAutoSetJson->Env;
    baseAppData.AppOtherAgrs=_baseAutoSetJson->Args;
    baseAppData.AttachProc=_baseAutoSetJson->AttachProc;

    QFileInfo fi = QFileInfo(baseAppData.AppExe);
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
    objDiyAddApp=new objectAppMT(&baseAppData,&baseDockData);
    objDiyAddApp->InitDockObj(false);
    objDiyAddApp->optionRegs();
    objDiyAddApp->DockLibsInstall();
    SaveAppDataToJson(baseDockData,baseAppData);
    delete objDiyAddApp;
    objDiyAddApp=nullptr;
}
void objectAppAT::run(){
    _baseAutoSetJson=new BaseAutoSetJson();
    if(JsonType(jsonCfg)){
        emit Error("配置文件出错!",true);
        return;
    }
    if(!jsonUnserialize(jsonCfg)){
        emit Error("配置容器出错!",true);
        return;
    }
    else
    {
        if(objDockerData(baseDockData.DockerName)){
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
