#include "objectAppAT.h"

objectAppAT::objectAppAT()
{
}

objectAppAT::~objectAppAT(){
    delete _baseAutoSetJson;
    _baseAutoSetJson=nullptr;
}
/*
 * _dockData 容器参数
 * _appData app参数
 * _appJsonData 自动刷配置参数
 */
void objectAppAT::connectDockAutoData(SdockerData _dockData,SappData _appData,SappDeployInfo _appJsonData){
    baseDockData=_dockData;
    baseAppData=_appData;
    appJsonData=_appJsonData;
}
//分析json类型，一共两种：网络 本地
JSONTYPE objectAppAT::JsonType(){
    if(appJsonData.appJson.startsWith("http",Qt::CaseSensitive)||appJsonData.appJson.startsWith("https",Qt::CaseSensitive)){
        return jNet;
    }
    if(appJsonData.appJson.endsWith("json",Qt::CaseSensitive)){
        return jFile;
    }
    return jDefault;
}
QString objectAppAT::jsonNetToStr(QString jsonNetUrl){
    try {
        QString jNetData=nullptr;
        objectGetCurl* _vekgetcurl=new objectGetCurl();
        jNetData=QString::fromStdString(_vekgetcurl->vekGetData(jsonNetUrl.toStdString()));
        delete _vekgetcurl;
        _vekgetcurl=nullptr;
        return jNetData;
    } catch (nullptr_t) {
        return nullptr;
    }
}
QString objectAppAT::jsonFileToStr(QString jsonFilePath){
    QString jFileStr=nullptr;
    QFile file(jsonFilePath);
    if(!file.exists())
    {
        return nullptr;
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    jFileStr = file.readAll();
    file.close();
    return jFileStr;
}
bool objectAppAT::jsonUnserialize(SappDeployInfo jAppData,JSONTYPE jType){
    QString jsonData=nullptr;
    if(jType==jNet){
        jsonData=jsonNetToStr(jAppData.appJson);
    }else if(jType==jFile){
        jsonData=jsonFileToStr(jAppData.appJson);
    }
    if(jsonData!=nullptr){
        objectJson _objectJson;
        _baseAutoSetJson=new SappDeployData;
        if(_objectJson.unDataSerializeScriptData(_baseAutoSetJson,jsonData)==nullptr){
            return false;
        }
    }
    return true;
}
//三个操作，第一 容器不存在则初始化，第二容器存在则检测容器选项，
bool objectAppAT::objDockerData(){
    //没有容器则按照下面配置设定
    if(!QDir(baseDockData.DockerPath+"/"+baseDockData.DockerName).exists())
    {
        baseDockData.DockerVer=_baseAutoSetJson->Docker.at(toStr(DockerVersion));
        baseDockData.DockerWineVersion=_baseAutoSetJson->Docker.at(toStr(DockerWineVersion));
        baseDockData.DockerSystemVersion=_baseAutoSetJson->Docker.at(toStr(DockerSysVersion));
        qInfo()<<"如果容器不存在"<<baseDockData.WinePath;
    }else{
        //如果容器存在
        qInfo()<<"如果容器存在";
        if(baseDockData.DockerVer!=_baseAutoSetJson->Docker.at(toStr(DockerVersion))){
            pObject::vekError("当前容器版本为:"+baseDockData.DockerVer+"配置文件容器版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerVersion)));
            return false;
        }
        if(baseDockData.DockerWineVersion!=_baseAutoSetJson->Docker.at(toStr(DockerWineVersion))){
            pObject::vekError("当前容器Wine版本为:"+baseDockData.DockerWineVersion+"配置文件容器Wine版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerWineVersion)));
            return false;
        }
        if(baseDockData.WineVersion.contains("deepin",Qt::CaseSensitive)&_baseAutoSetJson->Docker.at(toStr(DockerVersion))=="win64"){
            pObject::vekError("当前容器Wine版本为:"+baseDockData.WineVersion+"配置文件容器版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerVersion))+"\n"+"deepin-wine5不支持64位容器!");
            return false;
        }
    }
    baseDockData.WinePath=g_vekLocalData.wineVec.at(baseDockData.WineVersion).IwinePath;
    QVariant monoState=_baseAutoSetJson->Docker.at(toStr(MonoState));
    baseDockData.MonoState=(monoState).toBool();
    QVariant geckoState=_baseAutoSetJson->Docker.at(toStr(GeckoState));
    baseDockData.GeckoState=(geckoState).toBool();
    return true;
}
void objectAppAT::objAppData(){
    if(!_baseAutoSetJson->Option.empty()){
        for(auto [a,b]:_baseAutoSetJson->Option){
            if(a=="s_name"){
                baseAppData.s_name=b;
            }
            if(a=="DefaultFont"){
                QVariant defaultFontValue=b;
                baseAppData.b_default_fonts=(defaultFontValue).toBool();
            }
            if(a=="b_sharedmemory"){
                QVariant sharedMemoryValue=b;
                baseAppData.b_sharedmemory=(sharedMemoryValue).toBool();
            }
            if(a=="b_writecopy"){
                QVariant writeCopyValue=b;
                baseAppData.b_writecopy=(writeCopyValue).toBool();
            }
            if(a=="b_rtserver"){
                QVariant rtServerValue=b;
                baseAppData.b_rtserver=(rtServerValue).toBool();
            }

            if(a=="s_main_proc_name"){
                baseAppData.s_main_proc_name=b;
            }
            baseAppData.s_dock_system_version=_baseAutoSetJson->Docker.at(toStr(DockerSysVersion));
        }
    }
    if(!_baseAutoSetJson->Dxvk.empty()){
        for(auto a:_baseAutoSetJson->Dxvk){
            if(a.first=="DxvkVersion"){
                baseAppData.s_dxvk_version=a.second;
            }
            if(a.first=="b_dxvk_state"){
                QVariant dxvkStateValue=a.second;
                baseAppData.b_dxvk_state=(dxvkStateValue).toBool();
            }
            if(a.first=="b_dxvk_hud"){
                QVariant dxvkHUDValue=a.second;
                baseAppData.b_dxvk_hud=(dxvkHUDValue).toBool();
            }
        }
    }
    baseAppData.vec_docker_regs=_baseAutoSetJson->Regs;
    baseAppData.vec_docker_libs=_baseAutoSetJson->Libs;
    baseAppData.map_docker_regs=_baseAutoSetJson->Env;
    baseAppData.s_agrs_code=_baseAutoSetJson->Args;
    baseAppData.vec_attach_proc=_baseAutoSetJson->vec_attach_proc;

    QFileInfo fi = QFileInfo(baseAppData.s_exe);
    baseAppData.s_work_path=fi.path();
    objectJson* _objectJson=new objectJson();
    baseAppData.s_uid=_objectJson->GetRandomCID();
    delete _objectJson;
    _objectJson=nullptr;
    //baseAppData.s_ico=jsonIco;
}
void objectAppAT::objectAutoObj(){
    if(objDiyAddApp!=nullptr){
        delete objDiyAddApp;
        objDiyAddApp=nullptr;
    }
    emit Tips("配置容器中请稍候!");
    objDiyAddApp=new objectAppMT(&baseAppData,&baseDockData);
    objDiyAddApp->InitDockObj(false);
    objDiyAddApp->DockLibsInstall();
    delete objDiyAddApp;
    objDiyAddApp=nullptr;
}
void objectAppAT::run(){
    _baseAutoSetJson=new SappDeployData();
    JSONTYPE jtype=JsonType();
    if(jtype==jDefault){
        emit Error("配置文件出错!",true);
        return;
    }
    pObject::oLogs("配置文件:"+appJsonData.appJson);

    if(!jsonUnserialize(appJsonData,jtype)){
        emit Error("配置容器出错!",true);
        return;
    }
    else
    {
        if(!objDockerData()){
            emit Error("配置容器出错!",true);
            return;

        }else
        {
            objAppData();
            objectAutoObj();
        }
    }
    emit Done(&baseDockData,&baseAppData);
}
