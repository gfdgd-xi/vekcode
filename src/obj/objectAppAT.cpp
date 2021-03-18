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
void objectAppAT::connectDockAutoData(BaseDockData _dockData,BaseAppData _appData,BaseAppJson _appJsonData){
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
bool objectAppAT::jsonUnserialize(BaseAppJson jAppData,JSONTYPE jType){
    QString jsonData=nullptr;
    if(jType==jNet){
        jsonData=jsonNetToStr(jAppData.appJson);
    }else if(jType==jFile){
        jsonData=jsonFileToStr(jAppData.appJson);
    }
    if(jsonData!=nullptr){
        objectJson _objectJson;
        _baseAutoSetJson=new BaseAutoSetJson;
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
        qDebug()<<"如果容器不存在"<<baseDockData.WinePath;
    }else{
        //如果容器存在
        qDebug()<<"如果容器存在";
        if(baseDockData.DockerVer!=_baseAutoSetJson->Docker.at(toStr(DockerVersion))){
            vekError("当前容器版本为:"+baseDockData.DockerVer+"配置文件容器版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerVersion)));
            return false;
        }
        if(baseDockData.DockerWineVersion!=_baseAutoSetJson->Docker.at(toStr(DockerWineVersion))){
            vekError("当前容器Wine版本为:"+baseDockData.DockerWineVersion+"配置文件容器Wine版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerWineVersion)));
            return false;
        }
        if(baseDockData.WineVersion.contains("deepin",Qt::CaseSensitive)&_baseAutoSetJson->Docker.at(toStr(DockerVersion))=="win64"){
            vekError("当前容器Wine版本为:"+baseDockData.WineVersion+"配置文件容器版本为:"+_baseAutoSetJson->Docker.at(toStr(DockerVersion))+"\n"+"deepin-wine5不支持64位容器!");
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
            baseAppData.DockSysVersion=_baseAutoSetJson->Docker.at(toStr(DockerSysVersion));
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
    _baseAutoSetJson=new BaseAutoSetJson();
    JSONTYPE jtype=JsonType();
    if(jtype==jDefault){
        emit Error("配置文件出错!",true);
        return;
    }
    qDebug()<<"配置文件"<<appJsonData.appJson;
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
