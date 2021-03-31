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
void objectAppAT::connectDockAutoData(DockData _dockData,AppData _appData,AppJson _appJsonData){
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
bool objectAppAT::jsonUnserialize(AppJson jAppData,JSONTYPE jType){
    QString jsonData=nullptr;
    if(jType==jNet){
        jsonData=jsonNetToStr(jAppData.appJson);
    }else if(jType==jFile){
        jsonData=jsonFileToStr(jAppData.appJson);
    }
    if(jsonData!=nullptr){
        objectJson _objectJson;
        _baseAutoSetJson=new AutoJson;
        if(_objectJson.unDataSerializeScriptData(_baseAutoSetJson,jsonData)==nullptr){
            return false;
        }
    }
    return true;
}
//三个操作，第一 容器不存在则初始化，第二容器存在则检测容器选项，
bool objectAppAT::objDockerData(){
    //没有容器则按照下面配置设定
    if(!QDir(baseDockData.docker_Path+"/"+baseDockData.docker_Name).exists())
    {
        baseDockData.docker_SystemBitVersion=_baseAutoSetJson->auto_Docker.at(toStr(DockerVersion));
        baseDockData.docker_WineVersion=_baseAutoSetJson->auto_Docker.at(toStr(DockerWineVersion));
        baseDockData.docker_SystemVersion=_baseAutoSetJson->auto_Docker.at(toStr(DockerSysVersion));
        qInfo()<<"如果容器不存在"<<baseDockData.docker_WinePath;
    }else{
        //如果容器存在
        qInfo()<<"如果容器存在";
        if(baseDockData.docker_SystemBitVersion!=_baseAutoSetJson->auto_Docker.at(toStr(DockerVersion))){
            pObject::vekError("当前容器版本为:"+baseDockData.docker_SystemBitVersion+"配置文件容器版本为:"+_baseAutoSetJson->auto_Docker.at(toStr(DockerVersion)));
            return false;
        }
        if(baseDockData.docker_WineVersion!=_baseAutoSetJson->auto_Docker.at(toStr(DockerWineVersion))){
            pObject::vekError("当前容器Wine版本为:"+baseDockData.docker_WineVersion+"配置文件容器Wine版本为:"+_baseAutoSetJson->auto_Docker.at(toStr(DockerWineVersion)));
            return false;
        }
        if(baseDockData.docker_WineVersion.contains("deepin",Qt::CaseSensitive)&_baseAutoSetJson->auto_Docker.at(toStr(DockerVersion))=="win64"){
            pObject::vekError("当前容器Wine版本为:"+baseDockData.docker_WineVersion+"配置文件容器版本为:"+_baseAutoSetJson->auto_Docker.at(toStr(DockerVersion))+"\n"+"deepin-wine5不支持64位容器!");
            return false;
        }
    }
    baseDockData.docker_WinePath=g_vekLocalData.local_WineData.at(baseDockData.docker_WineVersion).iWinePath;
    QVariant monoState=_baseAutoSetJson->auto_Docker.at(toStr(MonoState));
    baseDockData.docker_MonoState=(monoState).toBool();
    QVariant geckoState=_baseAutoSetJson->auto_Docker.at(toStr(GeckoState));
    baseDockData.docker_GeckoState=(geckoState).toBool();
    return true;
}
void objectAppAT::objAppData(){
    if(!_baseAutoSetJson->auto_Option.empty()){
        for(auto [a,b]:_baseAutoSetJson->auto_Option){
            if(a=="AppName"){
                baseAppData.app_Name=b;
            }
            if(a=="DefaultFont"){
                QVariant defaultFontValue=b;
                baseAppData.app_DefaultFonts=(defaultFontValue).toBool();
            }
            if(a=="SharedMemory"){
                QVariant sharedMemoryValue=b;
                baseAppData.app_SharedMemory=(sharedMemoryValue).toBool();
            }
            if(a=="WriteCopy"){
                QVariant writeCopyValue=b;
                baseAppData.app_WriteCopy=(writeCopyValue).toBool();
            }
            if(a=="RtServer"){
                QVariant rtServerValue=b;
                baseAppData.app_RtServer=(rtServerValue).toBool();
            }

            if(a=="MainPrcoName"){
                baseAppData.app_MainProcName=b;
            }
            baseAppData.app_SystemVersion=_baseAutoSetJson->auto_Docker.at(toStr(DockerSysVersion));
        }
    }
    if(!_baseAutoSetJson->auto_Dxvk.empty()){
        for(auto a:_baseAutoSetJson->auto_Dxvk){
            if(a.first=="DxvkVersion"){
                baseAppData.app_DxvkVersion=a.second;
            }
            if(a.first=="DxvkState"){
                QVariant dxvkStateValue=a.second;
                baseAppData.app_DxvkState=(dxvkStateValue).toBool();
            }
            if(a.first=="DxvkHUD"){
                QVariant dxvkHUDValue=a.second;
                baseAppData.app_DxvkHUD=(dxvkHUDValue).toBool();
            }
        }
    }
    baseAppData.app_DockerRegs=_baseAutoSetJson->auto_Regs;
    baseAppData.app_DockerLibs=_baseAutoSetJson->auto_Libs;
    baseAppData.app_DockerEnv=_baseAutoSetJson->auto_Env;
    baseAppData.app_AgrsCode=_baseAutoSetJson->auto_Args;
    baseAppData.app_Attachproc=_baseAutoSetJson->app_Attachproc;

    QFileInfo fi = QFileInfo(baseAppData.app_Exe);
    baseAppData.app_WorkPath=fi.path();
    objectJson* _objectJson=new objectJson();
    baseAppData.app_CID=_objectJson->GetRandomCID();
    delete _objectJson;
    _objectJson=nullptr;
    //baseAppData.AppIco=jsonIco;
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
    _baseAutoSetJson=new AutoJson();
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
