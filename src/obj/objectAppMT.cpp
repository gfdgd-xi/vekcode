#include "objectAppMT.h"

objectAppMT::objectAppMT(BaseAppData* _appData,BaseDockData* _dockData)
{
    appData=_appData;
    dockData=_dockData;
}
objectAppMT::~objectAppMT(){
}

//返回dxvk文件列表
QStringList objectAppMT::GetDxvkFileList(QString basedxvkDir){
    QStringList dxvkFileList;
    dxvkFileList.clear();
    QString dxvkTarFile=basedxvkDir+"/"+appData->DxvkVerson+".tar.gz";
    QString dxvkTarDir=basedxvkDir+"/"+appData->DxvkVerson;
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
    QString baseDxvkDir=dockData->WinePath+"/dxvk";
    qDebug()<<baseDxvkDir;
    //获取dxvk目录下的文件列表
    QStringList dxvkFileList=GetDxvkFileList(baseDxvkDir);
    //dock下的系统区别
    QStringList dockSystemDir;
    dockSystemDir.clear();
    dockSystemDir.append("x32");
    //dockSystemDir.append("x64");
    QString dxvkTargetFile=nullptr;
    for(auto c:dockSystemDir){
        QString dxvkSourceFile=baseDxvkDir+"/"+appData->DxvkVerson+"/"+c+"/";
        dxvkTargetFile=dockData->DockerPath+"/"+dockData->DockerName+"/drive_c/windows/syswow64/";
        if(dockData->DockerVer=="win32"){
           dxvkTargetFile=dockData->DockerPath+"/"+dockData->DockerName+"/drive_c/windows/system32/";
        }
        if(QDir(dxvkTargetFile).exists()){
            for(auto d:dxvkFileList){
                //卸载
                if(!appData->DxvkState){
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
                QFile::setPermissions(dxvkTargetFile+d,
                                      QFile::ReadOther|
                                      QFile::ExeOther|
                                      QFile::ReadGroup|
                                      QFile::ExeGroup|
                                      QFile::ReadOwner|
                                      QFile::WriteOwner|
                                      QFile::ExeOwner);
            }
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
    if(appData->DxvkState)
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
    if(appData->DxvkHUD){
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
    QString _rValue=appData->DxvkConfigFile;
    QString _rObj;
    if(appData->DxvkConfigFileState){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(DockRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}

//default fonts
void objectAppMT::DefaultFontsFileInstall(){
    QString fontsDirStr=dockData->WinePath+"/fonts";
    QStringList fontsList;
    fontsList.clear();
    QDir _fontsDir(fontsDirStr);
    if (_fontsDir.exists()) {
        fontsList = _fontsDir.entryList(QDir::Files);
    }
    if(appData->DefaultFonts){
        if(QFile(fontsDirStr).exists()){
            for(auto f:fontsList){
                qDebug()<<fontsDirStr+"/"+f;
                qDebug()<<dockData->DockerPath+"/"+dockData->DockerName+"/drive_c/windows/Fonts/"+f;
                QFile::copy(fontsDirStr+"/"+f, dockData->DockerPath+"/"+dockData->DockerName+"/drive_c/windows/Fonts/"+f);
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
        _dockDir.mkdir(dockData->DockerPath);
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
    if(!appData->DockerLibs.empty()){
        for(auto af:appData->DockerLibs){
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
    QString fileMono=dockData->WinePath+"/plugs/Mono.msi";
    if(QFile(fileMono).exists()){
        _tempPlugsList.append(fileMono);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(object_plugs,object_wineboot_default,object_wineserver_default);
    }
}
void objectAppMT::installGeckoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileGeckoX86_64=dockData->WinePath+"/plugs/GeckoX86_64.msi";
    QString fileGeckoX86=dockData->WinePath+"/plugs/GeckoX86.msi";
    if(QFile(fileGeckoX86_64).exists()&QFile(fileGeckoX86).exists()){
        _tempPlugsList.append(fileGeckoX86_64);
        _tempPlugsList.append(fileGeckoX86);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(object_plugs,object_wineboot_default,object_wineserver_default);
    }
}
void objectAppMT::optionRegs(){
    argsList.clear();
    for(auto d:appData->DockerRegs)
    {
        argsList.push_back(DockRegeditStr("add",d.rPath,d.rKey,d.rTValue,d.rValue));
    }
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}
void objectAppMT::newDock(){
    QDir dockPath(dockData->DockerPath);
    QDir dockDir(dockData->DockerPath+"/"+dockData->DockerName);
    qDebug()<<dockData->DockerPath;
    qDebug()<<dockData->DockerName;
    argsList.clear();
    if(dockData->DockerPath==NULL&&dockData->DockerName==NULL){
        return;
    }
    InitDockDir(true,dockPath,dockDir);
    if(appData->DefaultFonts){
        DefaultFontsFileInstall();
    }
    if(dockData->MonoState){
        installMonoPlugs();
    }
    if(dockData->GeckoState){
        installGeckoPlugs();
    }
    DisableAss(winebuilder);
    DisableAss(winemine);
}
void objectAppMT::sObjectInstall(){
    DxvkFileInstall();
    DxvkHUDRegs();
    DxvkConfigFile();
}
void objectAppMT::DisableAss(std::map<QString,std::map<QString,QString>> regStr){
    argsList.clear();
    QString _rPath;
    QString _rKey;
    QString _rValue;
    for(auto a:regStr){
        _rPath=a.first;
        for(auto b:a.second){
            _rKey=b.first;
            _rValue=b.second;
        }
    }
    QString _rObj;
    if(appData->DisableAss){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(DockRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}
void objectAppMT::outAppIco(){
    QString icoCacheDir=QDir::currentPath()+"/vekCache/";
    if(!QDir(icoCacheDir).exists()){
        QDir(QDir::currentPath()).mkdir("vekCache");
    }
    QString exeName=QFileInfo(appData->AppExe).baseName();
    QString exePath=StrPathNullToStr(appData->AppExe);
    char* outCode=("wrestool -x -t 14 "+exePath+ ">"+ icoCacheDir+exeName).toLocal8Bit().data();
    system(outCode);
    if(QFileInfo(icoCacheDir+exeName).size()>0){
        appData->AppIco=icoCacheDir+exeName;
    }
}
bool objectAppMT::InitDockObj(bool _forceState){
    QDir dockPath(dockData->DockerPath);
    QDir dockDir(dockData->DockerPath+"/"+dockData->DockerName);
    if(dockData->DockerPath==NULL&&dockData->DockerName==NULL){
        return false;
    }
    try {
        InitDockDir(_forceState,dockPath,dockDir);
        sObjectInstall();
        DisableAss(winebuilder);
        DisableAss(winemine);
        if(appData->DefaultFonts){
            DefaultFontsFileInstall();
        }
        if(dockData->MonoState){
            installMonoPlugs();
        }
        if(dockData->GeckoState){
            installGeckoPlugs();
        }
        if(!appData->DockerRegs.empty()){
            optionRegs();
        }
        outAppIco();
        ExecuteObj(object_dockSysver,object_wineboot_default,object_wineserver_default);
        return true;
    } catch (nullptr_t) {
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
    if(dockData->DockerPath==NULL||dockData->DockerName==NULL){return;}
    objExtend->setDockOptionObjectData(*dockData,appData->AppCID,argsList,_objType,_objWineBootType,_objWineServer);
    WaitObjectDone(objExtend);
}
