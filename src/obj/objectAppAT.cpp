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
    if(appJsonData.s_deploy_app_json.startsWith("http",Qt::CaseSensitive)||appJsonData.s_deploy_app_json.startsWith("https",Qt::CaseSensitive)){
        return jNet;
    }
    if(appJsonData.s_deploy_app_json.endsWith("json",Qt::CaseSensitive)){
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
        jsonData=jsonNetToStr(jAppData.s_deploy_app_json);
    }else if(jType==jFile){
        jsonData=jsonFileToStr(jAppData.s_deploy_app_json);
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
    if(!QDir(baseDockData.s_dockers_path+"/"+baseDockData.s_dockers_name).exists())
    {
        baseDockData.s_dockers_bit_version=_baseAutoSetJson->map_deploy_docker.at(toStr(DockerVersion));
        baseDockData.s_dockers_wine_version=_baseAutoSetJson->map_deploy_docker.at(toStr(s_dockers_wine_version));
        baseDockData.s_dockers_system_version=_baseAutoSetJson->map_deploy_docker.at(toStr(DockerSysVersion));
    }else{
        //如果容器存在
        //bit_version为小系统版本分win32 win64
        //wine_exe_version为本地执行wine执行程序版本分wine和wine64
        //wine_version为wine的版本分别为deepin-wine5和win6.5之类为wine的名字
        //-----------------------------
        //于自动脚本区别在于
        //toStr(DockerVersion)为容器版本win32和win64
        //toStr(DockerWineVersion)为wine执行程序版本wine和wine64
        if(baseDockData.s_dockers_bit_version!=_baseAutoSetJson->map_deploy_docker.at(toStr(DockerVersion))){
            pObject::vekError("当前容器版本为:"+baseDockData.s_dockers_bit_version+"配置文件容器版本为:"+_baseAutoSetJson->map_deploy_docker.at(toStr(DockerVersion)));
            return false;
        }
        if(baseDockData.s_dockers_wine_exe_version!=_baseAutoSetJson->map_deploy_docker.at(toStr(DockerWineVersion))){
            pObject::vekError("当前容器Wine版本为:"+baseDockData.s_dockers_wine_exe_version+"配置文件容器Wine版本为:"+_baseAutoSetJson->map_deploy_docker.at(toStr(DockerWineVersion)));
            return false;
        }
        if(baseDockData.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
            if(_baseAutoSetJson->map_deploy_docker.at(toStr(DockerVersion))=="win64"){
                pObject::vekError("当前容器Wine版本为:"+baseDockData.s_dockers_wine_version+"配置文件容器版本为:"+_baseAutoSetJson->map_deploy_docker.at(toStr(DockerVersion))+"\n"+"deepin-wine5不支持64位容器!");
                return false;
            }
        }
    }
    baseDockData.s_dockers_wine_path=g_vekLocalData.map_wine_list.at(baseDockData.s_dockers_wine_version).s_local_wine_path;
    QVariant monoState=_baseAutoSetJson->map_deploy_docker.at(toStr(MonoState));
    baseDockData.s_dockers_mono_state=(monoState).toBool();
    QVariant geckoState=_baseAutoSetJson->map_deploy_docker.at(toStr(GeckoState));
    baseDockData.s_dockers_gecko_state=(geckoState).toBool();
    return true;
}
void objectAppAT::objAppData(){
    if(!_baseAutoSetJson->map_deploy_option.empty()){
        for(auto [a,b]:_baseAutoSetJson->map_deploy_option){
            if(a=="AppName"){
                baseAppData.s_name=b;
            }
            if(a=="DefaultFont"){
                QVariant defaultFontValue=b;
                baseAppData.b_default_fonts=(defaultFontValue).toBool();
            }
            if(a=="SharedMemory"){
                QVariant sharedMemoryValue=b;
                baseAppData.b_sharedmemory=(sharedMemoryValue).toBool();
            }
            if(a=="WriteCopy"){
                QVariant writeCopyValue=b;
                baseAppData.b_writecopy=(writeCopyValue).toBool();
            }
            if(a=="RtServer"){
                QVariant rtServerValue=b;
                baseAppData.b_rtserver=(rtServerValue).toBool();
            }

            if(a=="MainPrcoName"){
                baseAppData.s_main_proc_name=b;
            }
            baseAppData.s_dock_system_version=_baseAutoSetJson->map_deploy_docker.at(toStr(DockerSysVersion));
        }
    }
    if(!_baseAutoSetJson->map_deploy_dxvk.empty()){
        for(auto a:_baseAutoSetJson->map_deploy_dxvk){
            if(a.first=="DxvkVersion"){
                baseAppData.s_dxvk_version=a.second;
            }
            if(a.first=="DxvkState"){
                QVariant dxvkStateValue=a.second;
                baseAppData.b_dxvk_state=(dxvkStateValue).toBool();
            }
            if(a.first=="DxvkHUD"){
                QVariant dxvkHUDValue=a.second;
                baseAppData.b_dxvk_hud=(dxvkHUDValue).toBool();
            }
        }
    }
    baseAppData.vec_docker_regs=_baseAutoSetJson->vec_deploy_regs;
    baseAppData.vec_docker_libs=_baseAutoSetJson->vec_deploy_libs;
    baseAppData.map_docker_regs=_baseAutoSetJson->map_deploy_env;
    baseAppData.s_agrs_code=_baseAutoSetJson->map_deploy_args;
    baseAppData.vec_proc_attach_list=_baseAutoSetJson->vec_deploy_attach_proc;

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
    pObject::oLogs("配置文件:"+appJsonData.s_deploy_app_json);

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
