#include "objectAddGameMT.h"

objectAddGameMT::objectAddGameMT(BaseGameData* _data,BaseGameData* _olddata)
{
    _baseGameData=_data;
    _oldGameData=_olddata;
}
objectAddGameMT::~objectAddGameMT(){
}
//写入json
void objectAddGameMT::SaveDataToJson(QString dName,BaseGameData writeData){
    objectJson _objectJson;
    _objectJson.updateGameNodeData(dName,writeData);
}
//返回dxvk文件列表
QStringList objectAddGameMT::GetDxvkFileList(QString basedxvkDir){
    QStringList dxvkFileList;
    dxvkFileList.clear();
    QString dxvkTarFile=basedxvkDir+"/"+_baseGameData->dxvkVerson+".tar.gz";
    QString dxvkTarDir=basedxvkDir+"/"+_baseGameData->dxvkVerson;
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
void objectAddGameMT::DxvkFileInstall(){
    //wine下的dxvk目录
    QString baseDxvkDir=_baseGameData->winePath+"dxvk";
    //获取dxvk目录下的文件列表
    QStringList dxvkFileList=GetDxvkFileList(baseDxvkDir);
    //dock下的系统区别
    QStringList dockSystemDir;
    dockSystemDir.clear();
    dockSystemDir.append("x32");
    dockSystemDir.append("x64");
    QString dxvkTargetFile=nullptr;
    for(auto c:dockSystemDir){
        QString dxvkSourceFile=baseDxvkDir+"/"+_baseGameData->dxvkVerson+"/"+c+"/";
        dxvkTargetFile=_baseGameData->dockPath+"/"+_baseGameData->dockName+"/drive_c/windows/syswow64/";
        if(c=="x64"){
            dxvkTargetFile=_baseGameData->dockPath+"/"+_baseGameData->dockName+"/drive_c/windows/system32/";
        }
        for(auto d:dxvkFileList){
            //卸载
            if(!_baseGameData->dxvkState){
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
void objectAddGameMT::DxvkRegedit(QStringList dxvkFileList){
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
    if(_baseGameData->dxvkState)
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
void objectAddGameMT::DxvkHUDRegs(){
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
    if(_baseGameData->dxvkHUD){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(DockRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}
//dxvkConfig注册表增加环境变量
void objectAddGameMT::DxvkConfigFile(){
    QString _rPath;
    QString _rKey;
    argsList.clear();
    for(auto a:dxvkResCof){
        _rPath=a.first;
        for(auto b:a.second){
            _rKey=b.first;
        }
    }
    QString _rValue=_baseGameData->dxvkConfigFile;
    QString _rObj;
    if(_baseGameData->dxvkConfigFileState){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(DockRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
}

//default fonts
void objectAddGameMT::DefaultFontsFileInstall(){
    QString fontsDirStr=_baseGameData->winePath+"fonts";
    QStringList fontsList;
    fontsList.clear();
    QDir _fontsDir(fontsDirStr);
    if (_fontsDir.exists()) {
        fontsList = _fontsDir.entryList(QDir::Files);
    }
    if(_baseGameData->defaultFonts){
        if(QFile(fontsDirStr).exists()){
            for(auto f:fontsList){
                QFile::copy(fontsDirStr+"/"+f, _baseGameData->dockPath+"/"+_baseGameData->dockName+"/drive_c/windows/Fonts/"+f);
            }
        }
    }
    DefaultFontsRegs();
}
//默认字体注册表
void objectAddGameMT::DefaultFontsRegs(){
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

void objectAddGameMT::InitDockDir(bool foceState,QDir _dockPath,QDir _dockDir){
    if(!_dockPath.exists()){
        _dockDir.mkdir(_baseGameData->dockPath);
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
void objectAddGameMT::DockLibsInstall(){
    argsList.clear();
    if(!_baseGameData->dockLibs.empty()){
        for(auto af:_baseGameData->dockLibs){
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
void objectAddGameMT::installMonoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileMono=_baseGameData->winePath+"plugs/Mono.msi";
    if(QFile(fileMono).exists()){
        _tempPlugsList.append(fileMono);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(object_plugs,object_wineboot_default,object_wineserver_default);
    }
}
void objectAddGameMT::installGeckoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileGeckoX86_64=_baseGameData->winePath+"plugs/GeckoX86_64.msi";
    QString fileGeckoX86=_baseGameData->winePath+"plugs/GeckoX86.msi";
    if(QFile(fileGeckoX86_64).exists()&QFile(fileGeckoX86).exists()){
        _tempPlugsList.append(fileGeckoX86_64);
        _tempPlugsList.append(fileGeckoX86);
        argsList.push_back(_tempPlugsList);
        ExecuteObj(object_plugs,object_wineboot_default,object_wineserver_default);
    }
}
void objectAddGameMT::optionRegs(){
    argsList.clear();
    if(!_baseGameData->dockRegs.empty()){
        for(auto d:_baseGameData->dockRegs)
        {
            argsList.push_back(DockRegeditStr("add",d.rPath,d.rKey,d.rTValue,d.rValue));
        }
        ExecuteObj(object_regobject,object_wineboot_default,object_wineserver_default);
    }
}
void objectAddGameMT::newDock(){
    QDir dockPath(_baseGameData->dockPath);
    QDir dockDir(_baseGameData->dockPath+"/"+_baseGameData->dockName);
    qDebug()<<_baseGameData->dockPath;
    qDebug()<<_baseGameData->dockName;
    if(_baseGameData->dockPath==NULL&&_baseGameData->dockName==NULL){
        return;
    }
    InitDockDir(true,dockPath,dockDir);
    if(_baseGameData->defaultFonts){
        DefaultFontsFileInstall();
    }
    if(_baseGameData->monoState){
        installMonoPlugs();
    }
    if(_baseGameData->geckoState){
        installGeckoPlugs();
    }
}
bool objectAddGameMT::InitDockObj(bool _forceState){
    QDir dockPath(_baseGameData->dockPath);
    QDir dockDir(_baseGameData->dockPath+"/"+_baseGameData->dockName);
    if(_baseGameData->dockPath==NULL&&_baseGameData->dockName==NULL){
        return false;
    }
    try {
        InitDockDir(_forceState,dockPath,dockDir);
        if(_oldGameData==nullptr||_forceState){
            if(_baseGameData->dxvkState){
                DxvkFileInstall();
                if(_baseGameData->dxvkHUD){
                    DxvkHUDRegs();
                }
                if(_baseGameData->dxvkConfigFileState){
                    DxvkConfigFile();
                }
            }
            if(_baseGameData->defaultFonts){
                DefaultFontsFileInstall();
            }
            if(_baseGameData->monoState){
                installMonoPlugs();
            }
            if(_baseGameData->geckoState){
                installGeckoPlugs();
            }
        }else{
            if(_baseGameData->dxvkState!=_oldGameData->dxvkState){
                DxvkFileInstall();
                if(_baseGameData->dxvkHUD!=_oldGameData->dxvkHUD){
                    DxvkHUDRegs();
                }
                if(_baseGameData->dxvkConfigFileState!=_oldGameData->dxvkConfigFileState){
                    DxvkConfigFile();
                }
            }

            if(_baseGameData->defaultFonts!=_oldGameData->defaultFonts){
                DefaultFontsFileInstall();
            }
            if(_baseGameData->monoState!=_oldGameData->monoState){
                installMonoPlugs();
            }
            if(_baseGameData->geckoState!=_oldGameData->geckoState){
                installGeckoPlugs();
            }
        }
        optionRegs();
        ExecuteObj(object_dockSysver,object_wineboot_default,object_wineserver_default);
        return true;
    } catch (nullopt_t) {
        return false;
    }
}
//等待任务结束
void objectAddGameMT::WaitObjectDone(objectExtend* _waitObject){
    _waitObject->start();
    _waitObject->wait(-1);
    delete _waitObject;
    _waitObject=nullptr;
}
//执行
void objectAddGameMT::ExecuteObj(objectType _objType,objectWineBoot _objWineBootType,objectWineServer _objWineServer){
    objectExtend* objExtend = new objectExtend();
    if(_baseGameData->dockPath==NULL||_baseGameData->dockName==NULL){return;}
    connect(this, SIGNAL(ExecutetoObjectArgs(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)), objExtend, SLOT(setDockOptionObjectData(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)));
    emit(ExecutetoObjectArgs(*_baseGameData,argsList,_objType,_objWineBootType,_objWineServer));
    WaitObjectDone(objExtend);
}
