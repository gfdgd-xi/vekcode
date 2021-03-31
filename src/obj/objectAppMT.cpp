#include "objectAppMT.h"

objectAppMT::objectAppMT(AppData* _appData,DockData* _dockData)
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
    QString dxvkTarFile=basedxvkDir+"/"+appData->app_DxvkVersion+".tar.gz";
    QString dxvkTarDir=basedxvkDir+"/"+appData->app_DxvkVersion;
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
    QString baseDxvkDir=dockData->docker_WinePath+"/dxvk";
    pObject::oLogs(baseDxvkDir);
    //获取dxvk目录下的文件列表
    QStringList dxvkFileList=GetDxvkFileList(baseDxvkDir);
    //dock下的系统区别
    QStringList dockSystemDir;
    dockSystemDir.clear();
    dockSystemDir.append("x32");
    //dockSystemDir.append("x64");
    QString dxvkTargetFile=nullptr;
    for(auto c:dockSystemDir){
        QString dxvkSourceFile=baseDxvkDir+"/"+appData->app_DxvkVersion+"/"+c+"/";
        dxvkTargetFile=dockData->docker_Path+"/"+dockData->docker_Name+"/drive_c/windows/syswow64/";
        if(dockData->docker_SystemBitVersion=="win32"){
           dxvkTargetFile=dockData->docker_Path+"/"+dockData->docker_Name+"/drive_c/windows/system32/";
        }
        if(QDir(dxvkTargetFile).exists()){
            for(auto d:dxvkFileList){
                //卸载
                if(!appData->app_DxvkState){
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
    if(appData->app_DxvkState)
    {
        _rObj="add";
    }else{
        _rObj="delete";
    }
    for(auto d:dxvkFileList){
        QString _rKey=QFileInfo(d).baseName();
        argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    }
    ExecuteObj(REGOBJ,BOOTDEFAULT,SERVERDEFAULT);
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
    if(appData->app_DxvkHUD){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(REGOBJ,BOOTDEFAULT,SERVERDEFAULT);
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
    QString _rValue=appData->app_DxvkConfig;
    QString _rObj;
    if(appData->app_DxvkConfigFileState){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(REGOBJ,BOOTDEFAULT,SERVERDEFAULT);
}

//default fonts
void objectAppMT::DefaultFontsFileInstall(){
    QString fontsDirStr=dockData->docker_WinePath+"/fonts";
    QStringList fontsList;
    fontsList.clear();
    QDir _fontsDir(fontsDirStr);
    if (_fontsDir.exists()) {
        fontsList = _fontsDir.entryList(QDir::Files);
    }
    if(appData->app_DefaultFonts){
        if(QFile(fontsDirStr).exists()){
            for(auto f:fontsList){
                pObject::oLogs(fontsDirStr+"/"+f);
                pObject::oLogs(dockData->docker_Path+"/"+dockData->docker_Name+"/drive_c/windows/Fonts/"+f);
                QFile::copy(fontsDirStr+"/"+f, dockData->docker_Path+"/"+dockData->docker_Name+"/drive_c/windows/Fonts/"+f);
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
            argsList.push_back(pObject::dockerRegeditStr("add",_rPath,_rKey,"REG_SZ",_rValue));
        }
    }
    ExecuteObj(REGOBJ,BOOTDEFAULT,SERVERDEFAULT);
}

void objectAppMT::InitDockDir(bool foceState,QDir _dockPath,QDir _dockDir){
    if(!_dockPath.exists()){
        _dockDir.mkdir(dockData->docker_Path);
    }
    if(_dockDir.exists())
    {
        if(foceState)
        {
            while(_dockDir.removeRecursively()){
                break;
            }
            ExecuteObj(BOOT,BOOTI,SERVERDEFAULT);
        }
    }else{
        ExecuteObj(BOOT,BOOTI,SERVERDEFAULT);
    }
    QFile systemFile=_dockDir.path()+"/system.reg";
    QFile userFile=_dockDir.path()+"/user.reg";
    QFile userdefFile=_dockDir.path()+"/userdef.reg";
    while(true){
        if(systemFile.exists()&userFile.exists()&userdefFile.exists()){
            pObject::oLogs("容器初始化完毕！");
            break;
        }
    }
}
void objectAppMT::DockLibsInstall(){
    argsList.clear();
    if(!appData->app_DockerLibs.empty()){
        for(auto af:appData->app_DockerLibs){
            QStringList libList;
            libList.clear();
            if(af!=nullptr){
                libList<<af;
                argsList.push_back(libList);
            }
        }
        ExecuteObj(WINETRICKSLIBS,BOOTDEFAULT,SERVERDEFAULT);
    }  
}
void objectAppMT::installMonoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileMono=dockData->docker_WinePath+"/plugs/Mono.msi";
    if(QFile(fileMono).exists()){
        _tempPlugsList.append(fileMono);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(PLUGS,BOOTDEFAULT,SERVERDEFAULT);
    }
}
void objectAppMT::installGeckoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileGeckoX86_64=dockData->docker_WinePath+"/plugs/GeckoX86_64.msi";
    QString fileGeckoX86=dockData->docker_WinePath+"/plugs/GeckoX86.msi";
    if(QFile(fileGeckoX86_64).exists()&QFile(fileGeckoX86).exists()){
        _tempPlugsList.append(fileGeckoX86_64);
        _tempPlugsList.append(fileGeckoX86);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(PLUGS,BOOTDEFAULT,SERVERDEFAULT);
    }
}
void objectAppMT::optionRegs(){
    argsList.clear();
    for(auto d:appData->app_DockerRegs)
    {
        argsList.push_back(pObject::dockerRegeditStr("add",d.rPath,d.rKey,d.rTValue,d.rValue));
    }
    ExecuteObj(REGOBJ,BOOTDEFAULT,SERVERDEFAULT);
}
void objectAppMT::newDock(){
    QDir dockPath(dockData->docker_Path);
    QDir dockDir(dockData->docker_Path+"/"+dockData->docker_Name);
    pObject::oLogs(dockData->docker_Path);
    pObject::oLogs(dockData->docker_Name);
    argsList.clear();
    if(dockData->docker_Path==nullptr&&dockData->docker_Name==nullptr){
        return;
    }
    InitDockDir(true,dockPath,dockDir);
    if(appData->app_DefaultFonts){
        DefaultFontsFileInstall();
    }
    if(dockData->docker_MonoState){
        installMonoPlugs();
    }
    if(dockData->docker_GeckoState){
        installGeckoPlugs();
    }
    DisableAss(winebuilder);
    DisableAss(winemine);
    pObject::saveDockerDataToJson(*dockData,dockData->docker_Name);
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
    if(appData->app_DisableAss){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(REGOBJ,BOOTDEFAULT,SERVERDEFAULT);
}
void objectAppMT::outAppIco(){
    QString icoCacheDir=QApplication::applicationDirPath()+"/vekCache/";
    if(!QDir(icoCacheDir).exists()){
        QDir(QApplication::applicationDirPath()).mkdir("vekCache");
    }
    QString exeName=QFileInfo(appData->app_Exe).baseName();
    QString exePath=pObject::pathNullToStr(appData->app_Exe);
    char* outCode=("wrestool -x -t 14 "+exePath+ ">"+ icoCacheDir+exeName).toLocal8Bit().data();
    system(outCode);
    if(QFileInfo(icoCacheDir+exeName).size()>0){
        appData->app_ICO=icoCacheDir+exeName;
    }
}
bool objectAppMT::InitDockObj(bool _forceState){
    QDir dockPath(dockData->docker_Path);
    QDir dockDir(dockData->docker_Path+"/"+dockData->docker_Name);
    if(dockData->docker_Path==nullptr&&dockData->docker_Name==nullptr){
        return false;
    }
    try {
        InitDockDir(_forceState,dockPath,dockDir);
        sObjectInstall();
        DisableAss(winebuilder);
        DisableAss(winemine);
        if(appData->app_DefaultFonts){
            DefaultFontsFileInstall();
        }
        if(dockData->docker_MonoState){
            installMonoPlugs();
        }
        if(dockData->docker_GeckoState){
            installGeckoPlugs();
        }
        if(!appData->app_DockerRegs.empty()){
            optionRegs();
        }
        outAppIco();
        ExecuteObj(DOCKSYSVER,BOOTDEFAULT,SERVERDEFAULT);
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
void objectAppMT::ExecuteObj(OBJTYPE _objType,BOOTTYPE _objWineBootType,SERVERTYPE _objWineServer){
    objectExtend* objExtend = new objectExtend();
    if(dockData->docker_Path==nullptr||dockData->docker_Name==nullptr){return;}
    objExtend->setDockOptionObjectData(*dockData,appData->app_CID,argsList,_objType,_objWineBootType,_objWineServer);
    WaitObjectDone(objExtend);
}
