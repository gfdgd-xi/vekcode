#include "objectAppMT.h"

objectAppMT::objectAppMT(BaseAppData* _data,BaseAppData* _olddata)
{
    _BaseAppData=_data;
    _oldAppData=_olddata;
}
objectAppMT::~objectAppMT(){
}
//写入json
void objectAppMT::SaveDataToJson(QString dName,BaseAppData writeData){
    objectJson _objectJson;
    _objectJson.updateAppNodeData(dName,writeData);
}
//返回dxvk文件列表
QStringList objectAppMT::GetDxvkFileList(QString basedxvkDir){
    QStringList dxvkFileList;
    dxvkFileList.clear();
    QString dxvkTarFile=basedxvkDir+"/"+_BaseAppData->dxvkVerson+".tar.gz";
    QString dxvkTarDir=basedxvkDir+"/"+_BaseAppData->dxvkVerson;
    QDir _dxvkTarDir(dxvkTarDir);
    if(!_dxvkTarDir.exists()){
        char* dxvkFile=("tar -xvf "+dxvkTarFile+" -C "+basedxvkDir).toLocal8Bit().data();
        system(dxvkFile);
    }
    QDir _dxvkUnDir(dxvkTarDir+"/x32");
    if (_dxvkUnDir.exists()) {
        dxvkFileList = _dxvkUnDir.entryList(QDir::Files);
    }
    return dxvkFileList;
}
//安装dxvk
void objectAppMT::DxvkFileInstall(){
    //wine下的dxvk目录
    QString baseDxvkDir=_BaseAppData->winePath+"dxvk";
    qDebug()<<baseDxvkDir;
    //获取dxvk目录下的文件列表
    QStringList dxvkFileList=GetDxvkFileList(baseDxvkDir);
    //dock下的系统区别
    QStringList dockSystemDir;
    dockSystemDir.clear();
    dockSystemDir.append("x32");
    dockSystemDir.append("x64");
    QString dxvkTargetFile=nullptr;
    for(auto c:dockSystemDir){
        QString dxvkSourceFile=baseDxvkDir+"/"+_BaseAppData->dxvkVerson+"/"+c+"/";
        dxvkTargetFile=_BaseAppData->dockPath+"/"+_BaseAppData->dockName+"/drive_c/windows/syswow64/";
        if(c=="x64"){
            dxvkTargetFile=_BaseAppData->dockPath+"/"+_BaseAppData->dockName+"/drive_c/windows/system32/";
        }
        for(auto d:dxvkFileList){
            //卸载
            if(!_BaseAppData->dxvkState){
                if(QFile(dxvkTargetFile+d+".a").exists()){
                    QFile(dxvkTargetFile+d).remove();
                    QFile::rename(dxvkTargetFile+d+".a",dxvkTargetFile+d);
                }
            }else{//安装
                if(QFile(dxvkTargetFile+d+".a").exists()){
                    QFile(dxvkTargetFile+d).remove();
                }else{
                    QFile::rename(dxvkTargetFile+d,dxvkTargetFile+d+".a");
                }
                QFile::copy(dxvkSourceFile+d, dxvkTargetFile+d);
            }
            QFile::setPermissions(dxvkTargetFile+d,QFile::ReadOther|QFile::ReadOwner|QFile::WriteOwner|QFile::ReadGroup);
        }
    }
    DxvkRegedit(dxvkFileList);
}
//dxvk注册表操作
void objectAppMT::DxvkRegedit(QStringList dxvkFileList){
    argsList.clear();
    QString _rPath;
    QString _rValue;
    for(auto d:dxvkRes){
        _rPath=d.first;
        for(auto a:d.second){
            _rValue=a.second;
        }
    }
    QString _rObj;
    if(_BaseAppData->dxvkState)
    {
        _rObj="add";
    }else{
        _rObj="delete";
    }
    for(auto d:dxvkFileList){
        QString _rKey=QFileInfo(d).baseName();
        argsList.push_back(DockRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    }
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}
//dxvkHUD注册表操作
void objectAppMT::DxvkHUDRegs(){
    argsList.clear();
    QString _rPath;
    QString _rKey;
    QString _rValue;
    for(auto a:dxvkResHUD){
        _rPath=a.first;
        for(auto b:a.second){
            _rKey=b.first;
            _rValue=b.second;
        }
    }
    QString _rObj;
    if(_BaseAppData->dxvkHUD){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(DockRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}
//dxvkConfig注册表增加环境变量
void objectAppMT::DxvkConfigFile(){
    QString _rPath;
    QString _rKey;
    argsList.clear();
    for(auto a:dxvkResCof){
        _rPath=a.first;
        for(auto b:a.second){
            _rKey=b.first;
        }
    }
    QString _rValue=_BaseAppData->dxvkConfigFile;
    QString _rObj;
    if(_BaseAppData->dxvkConfigFileState){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(DockRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}

//default fonts
void objectAppMT::DefaultFontsFileInstall(){
    QString fontsDirStr=_BaseAppData->winePath+"fonts";
    QStringList fontsList;
    fontsList.clear();
    QDir _fontsDir(fontsDirStr);
    if (_fontsDir.exists()) {
        fontsList = _fontsDir.entryList(QDir::Files);
    }
    if(_BaseAppData->defaultFonts){
        if(QFile(fontsDirStr).exists()){
            for(auto f:fontsList){
                QFile::copy(fontsDirStr+"/"+f, _BaseAppData->dockPath+"/"+_BaseAppData->dockName+"/drive_c/windows/Fonts/"+f);
            }
        }
    }
    DefaultFontsRegs();
}
//默认字体注册表
void objectAppMT::DefaultFontsRegs(){
    argsList.clear();
    QString _rPath;
    QString _rKey;
    QString _rValue;
    for(auto a:fontRes){
        _rPath=a.first;
        for(auto b:a.second){
            _rKey=b.first;
            _rValue=b.second;
            argsList.push_back(DockRegeditStr("add",_rPath,_rKey,"REG_SZ",_rValue));
        }
    }
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}

void objectAppMT::InitDockDir(bool foceState,QDir _dockPath,QDir _dockDir){
    if(!_dockPath.exists()){
        _dockDir.mkdir(_BaseAppData->dockPath);
    }
    if(_dockDir.exists())
    {
        if(foceState)
        {
            while(_dockDir.removeRecursively()){
                break;
            }
            ExecuteObj(object_wineboot,object_wineboot_i,object_wineserver_default);
        }
    }else{
        ExecuteObj(object_wineboot,object_wineboot_i,object_wineserver_default);
    }
    QFile systemFile=_dockDir.path()+"/system.reg";
    QFile userFile=_dockDir.path()+"/user.reg";
    QFile userdefFile=_dockDir.path()+"/userdef.reg";
    while(true){
        if(systemFile.exists()&userFile.exists()&userdefFile.exists()){
            qDebug()<<"容器初始化完毕！";
            break;
        }
    }
}
void objectAppMT::DockLibsInstall(){
    argsList.clear();
    if(!_BaseAppData->dockLibs.empty()){
        for(auto af:_BaseAppData->dockLibs){
            QStringList libList;
            libList.clear();
            if(af!=NULL){
                libList<<af;
                argsList.push_back(libList);
            }
        }
        ExecuteObj(object_winetricks_libs,object_wineboot_default,object_wineserver_default);
    }  
}
void objectAppMT::installMonoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileMono=_BaseAppData->winePath+"plugs/Mono.msi";
    if(QFile(fileMono).exists()){
        _tempPlugsList.append(fileMono);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(object_plugs,object_wineboot_default,object_wineserver_default);
    }
}
void objectAppMT::installGeckoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileGeckoX86_64=_BaseAppData->winePath+"plugs/GeckoX86_64.msi";
    QString fileGeckoX86=_BaseAppData->winePath+"plugs/GeckoX86.msi";
    if(QFile(fileGeckoX86_64).exists()&QFile(fileGeckoX86).exists()){
        _tempPlugsList.append(fileGeckoX86_64);
        _tempPlugsList.append(fileGeckoX86);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(object_plugs,object_wineboot_default,object_wineserver_default);
    }
}
void objectAppMT::optionRegs(){
    argsList.clear();
    if(!_BaseAppData->dockRegs.empty()){
        for(auto d:_BaseAppData->dockRegs)
        {
            argsList.push_back(DockRegeditStr("add",d.rPath,d.rKey,d.rTValue,d.rValue));
        }
        ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
    }
}
void objectAppMT::newDock(){
    QDir dockPath(_BaseAppData->dockPath);
    QDir dockDir(_BaseAppData->dockPath+"/"+_BaseAppData->dockName);
    qDebug()<<_BaseAppData->dockPath;
    qDebug()<<_BaseAppData->dockName;
    if(_BaseAppData->dockPath==NULL&&_BaseAppData->dockName==NULL){
        return;
    }
    InitDockDir(true,dockPath,dockDir);
    if(_BaseAppData->defaultFonts){
        DefaultFontsFileInstall();
    }
    if(_BaseAppData->monoState){
        installMonoPlugs();
    }
    if(_BaseAppData->geckoState){
        installGeckoPlugs();
    }
}
void objectAppMT::sObjectInstall(){
    DxvkFileInstall();
    DxvkHUDRegs();
    DxvkConfigFile();
}
bool objectAppMT::InitDockObj(bool _forceState){
    QDir dockPath(_BaseAppData->dockPath);
    QDir dockDir(_BaseAppData->dockPath+"/"+_BaseAppData->dockName);
    if(_BaseAppData->dockPath==NULL&&_BaseAppData->dockName==NULL){
        return false;
    }
    try {
        InitDockDir(_forceState,dockPath,dockDir);
        if(_oldAppData==nullptr||_forceState){
            if(_BaseAppData->dxvkState){
                DxvkFileInstall();
                if(_BaseAppData->dxvkHUD){
                    DxvkHUDRegs();
                }
                if(_BaseAppData->dxvkConfigFileState){
                    DxvkConfigFile();
                }
            }
            if(_BaseAppData->defaultFonts){
                DefaultFontsFileInstall();
            }
            if(_BaseAppData->monoState){
                installMonoPlugs();
            }
            if(_BaseAppData->geckoState){
                installGeckoPlugs();
            }
        }else{
           sObjectInstall();
           DefaultFontsFileInstall();
           installMonoPlugs();
           installGeckoPlugs();
        }
        optionRegs();
        ExecuteObj(object_dockSysver,object_wineboot_default,object_wineserver_default);
        return true;
    } catch (nullopt_t) {
        return false;
    }
}
//等待任务结束
void objectAppMT::WaitObjectDone(objectExtend* _waitObject){
    _waitObject->start();
    _waitObject->wait(-1);
    delete _waitObject;
    _waitObject=nullptr;
}
//执行
void objectAppMT::ExecuteObj(objectType _objType,objectWineBoot _objWineBootType,objectWineServer _objWineServer){
    objectExtend* objExtend = new objectExtend();
    if(_BaseAppData->dockPath==NULL||_BaseAppData->dockName==NULL){return;}
    connect(this, SIGNAL(ExecutetoObjectArgs(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)), objExtend, SLOT(setDockOptionObjectData(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)));
    emit(ExecutetoObjectArgs(*_BaseAppData,argsList,_objType,_objWineBootType,_objWineServer));
    WaitObjectDone(objExtend);
}
