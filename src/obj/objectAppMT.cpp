#include "objectAppMT.h"

objectAppMT::objectAppMT(SdockerData* _dockData,SappData* _appData)
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
    QString dxvkTarFile=basedxvkDir+"/"+appData->s_dxvk_version+".tar.gz";
    QString dxvkTarDir=basedxvkDir+"/"+appData->s_dxvk_version;
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
    QString baseDxvkDir=dockData->s_dockers_wine_path+"/dxvk";
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
        QString dxvkSourceFile=baseDxvkDir+"/"+appData->s_dxvk_version+"/"+c+"/";
        dxvkTargetFile=dockData->s_dockers_path+"/"+dockData->s_dockers_name+"/drive_c/windows/syswow64/";
        if(dockData->s_dockers_bit_version=="win32"){
            dxvkTargetFile=dockData->s_dockers_path+"/"+dockData->s_dockers_name+"/drive_c/windows/system32/";
        }
        if(QDir(dxvkTargetFile).exists()){
            for(auto d:dxvkFileList){
                //卸载
                if(!appData->b_dxvk_state){
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
    if(appData->b_dxvk_state)
    {
        _rObj="add";
    }else{
        _rObj="delete";
    }
    for(auto d:dxvkFileList){
        QString _rKey=QFileInfo(d).baseName();
        argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    }
    ExtendArgs exArgs;
    exArgs.ex_docker=object_docker_reggedit_extend;
    ExecuteObject(exArgs,EX_DOCKER);
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
    if(appData->b_dxvk_hud){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExtendArgs exArgs;
    exArgs.ex_docker=object_docker_reggedit_extend;
    ExecuteObject(exArgs,EX_DOCKER);
}
//dxvkConfig注册表增加环境变量
void objectAppMT::s_dxvk_config_file(){
    QString _rPath;
    QString _rKey;
    argsList.clear();
    for(auto a:dxvkResCof){
        _rPath=a.first;
        for(auto b:a.second){
            _rKey=b.first;
        }
    }
    QString _rValue=appData->s_dxvk_config_file;
    QString _rObj;
    if(appData->b_dxvk_config_file_state){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExtendArgs exArgs;
    exArgs.ex_docker=object_docker_reggedit_extend;
    ExecuteObject(exArgs,EX_DOCKER);
}

//default fonts
void objectAppMT::DefaultFontsFileInstall(CHANGETYPE _type){
    QString fontsDirStr=dockData->s_dockers_wine_path+"/fonts";
    bool fonts_state;

    if(_type==CHANGETYPEDOCKER){
        fonts_state=appData->b_default_fonts;
    }else{
        fonts_state=dockData->s_dockers_default_fonts;
    }
    QStringList fontsList;
    fontsList.clear();
    QDir _fontsDir(fontsDirStr);
    if (_fontsDir.exists()) {
        fontsList = _fontsDir.entryList(QDir::Files);
    }
    if(fonts_state){
        if(QFile(fontsDirStr).exists()){
            for(auto f:fontsList){
                pObject::oLogs(fontsDirStr+"/"+f);
                pObject::oLogs(dockData->s_dockers_path+"/"+dockData->s_dockers_name+"/drive_c/windows/Fonts/"+f);
                QFile::copy(fontsDirStr+"/"+f, dockData->s_dockers_path+"/"+dockData->s_dockers_name+"/drive_c/windows/Fonts/"+f);
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
    ExtendArgs exArgs;
    exArgs.ex_docker=object_docker_reggedit_extend;
    ExecuteObject(exArgs,EX_DOCKER);
}

void objectAppMT::DockLibsInstall(){
    argsList.clear();
    if(!appData->vec_docker_libs.empty()){
        for(auto af:appData->vec_docker_libs){
            QStringList libList;
            libList.clear();
            if(af!=nullptr){
                libList<<af;
                argsList.push_back(libList);
            }
        }
        ExtendArgs exArgs;
        exArgs.ex_docker=object_docker_winetricks_cmd_libs;
        ExecuteObject(exArgs,EX_DOCKER);
    }
}
void objectAppMT::installMonoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileMono=dockData->s_dockers_wine_path+"/plugs/Mono.msi";
    if(QFile(fileMono).exists()){
        _tempPlugsList.append(fileMono);
        argsList.push_back(_tempPlugsList);
        ExtendArgs exArgs;
        exArgs.ex_docker=object_docker_plugs_extend;
        ExecuteObject(exArgs,EX_DOCKER);
    }
}
void objectAppMT::installGeckoPlugs(){
    argsList.clear();
    QStringList _tempPlugsList;
    QString fileGeckoX86_64=dockData->s_dockers_wine_path+"/plugs/GeckoX86_64.msi";
    QString fileGeckoX86=dockData->s_dockers_wine_path+"/plugs/GeckoX86.msi";
    if(QFile(fileGeckoX86_64).exists()&QFile(fileGeckoX86).exists()){
        _tempPlugsList.append(fileGeckoX86_64);
        _tempPlugsList.append(fileGeckoX86);
        argsList.push_back(_tempPlugsList);
        ExtendArgs exArgs;
        exArgs.ex_docker=object_docker_plugs_extend;
        ExecuteObject(exArgs,EX_DOCKER);
    }
}
void objectAppMT::optionRegs(){
    argsList.clear();
    for(auto d:appData->vec_docker_regs)
    {
        argsList.push_back(pObject::dockerRegeditStr("add",d.rPath,d.rKey,d.rTValue,d.rValue));
    }
    ExtendArgs exArgs;
    exArgs.ex_docker=object_docker_reggedit_extend;
    ExecuteObject(exArgs,EX_DOCKER);
}

void objectAppMT::InstallDXVK(){
    DxvkFileInstall();
    DxvkHUDRegs();
    s_dxvk_config_file();
}
void objectAppMT::b_disable_ass(std::map<QString,std::map<QString,QString>> regStr){
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
    if(dockData->s_dockers_disable_ass){
        _rObj="add";
    }else{
        _rObj="delete";
    }
    argsList.push_back(pObject::dockerRegeditStr(_rObj,_rPath,_rKey,"REG_SZ",_rValue));
    ExtendArgs exArgs;
    exArgs.ex_docker=object_docker_reggedit_extend;
    ExecuteObject(exArgs,EX_DOCKER);
}
void objectAppMT::outAppIco(){
    QString icoCacheDir=QApplication::applicationDirPath()+"/vekCache/";
    if(!QDir(icoCacheDir).exists()){
        QDir(QApplication::applicationDirPath()).mkdir("vekCache");
    }
    QString exeName=QFileInfo(appData->s_exe).baseName();
    QString exePath=pObject::pathNullToStr(appData->s_exe);
    char* outCode=("wrestool -x -t 14 "+exePath+ ">"+ icoCacheDir+exeName).toLocal8Bit().data();
    system(outCode);
    if(QFileInfo(icoCacheDir+exeName).size()>0){
        appData->s_ico=icoCacheDir+exeName;
    }
}
void objectAppMT::changeSettings(CHANGETYPE _type){
    bool bfonts,bmono,bgecko;

    if(_type==CHANGETYPEDOCKER){
        bfonts=dockData->s_dockers_default_fonts;
        bmono=dockData->s_dockers_mono_state;
        bgecko=dockData->s_dockers_gecko_state;
    }else{
        bfonts=appData->b_default_fonts;
        bmono=appData->b_mono_state;
        bgecko=appData->b_gecko_state;
        if(!appData->vec_docker_regs.empty()){
            optionRegs();
        }
        b_disable_ass(winebuilder);
        b_disable_ass(winemine);
        InstallDXVK();
        outAppIco();
        ExtendArgs exArgs;
        exArgs.ex_docker=object_docker_switch_version;
        ExecuteObject(exArgs,EX_DOCKER);
    }
    argsList.clear();
    if(bfonts){
        DefaultFontsFileInstall(_type);
    }
    if(bmono){
        installMonoPlugs();
    }
    if(bgecko){
        installGeckoPlugs();
    }
    pObject::saveDockerDataToJson(*dockData,dockData->s_dockers_name);
}
void objectAppMT::InitDockDir(bool foceState,QDir _dockPath,QDir _dockDir){
    ExtendArgs exArgs;
    exArgs.ex_boot=object_wineboot_i;
    if(!_dockPath.exists()){
        _dockDir.mkdir(dockData->s_dockers_path);
    }
    if(_dockDir.exists())
    {
        if(foceState)
        {
            while(_dockDir.removeRecursively()){
                break;
            }

            ExecuteObject(exArgs,EX_DOCKER);
        }
    }else{
        ExecuteObject(exArgs,EX_DOCKER);
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
bool objectAppMT::InitDocker(bool _forceState){
    QDir dockPath(dockData->s_dockers_path);
    QDir dockDir(dockData->s_dockers_path+"/"+dockData->s_dockers_name);
    argsList.clear();
    if(dockData->s_dockers_path==nullptr&&dockData->s_dockers_name==nullptr){
        return false;
    }
    InitDockDir(_forceState,dockPath,dockDir);
    if(dockData->s_dockers_default_fonts){
        DefaultFontsFileInstall(CHANGETYPEDOCKER);
    }
    if(dockData->s_dockers_mono_state){
        installMonoPlugs();
    }
    if(dockData->s_dockers_gecko_state){
        installGeckoPlugs();
    }
    b_disable_ass(winebuilder);
    b_disable_ass(winemine);
    pObject::saveDockerDataToJson(*dockData,dockData->s_dockers_name);
    return true;
}

//等待任务结束
void objectAppMT::WaitObjectDone(objectExtend* _waitObject){
    _waitObject->start();
    _waitObject->wait(-1);
    delete _waitObject;
    _waitObject=nullptr;
}
//执行
void objectAppMT::ExecuteObject(ExtendArgs ex_Args,ExtendType ex_Type){
    objectExtend* objExtend = new objectExtend();
    if(dockData->s_dockers_path==nullptr||dockData->s_dockers_name==nullptr){return;}
    if(ex_Type==EX_APP){
        objExtend->setDockOptionObjectData(*dockData,appData->s_uid,argsList,ex_Args,ex_Type);
    }else{
        objExtend->setDockOptionObjectData(*dockData,nullptr,argsList,ex_Args,ex_Type);
    }
    WaitObjectDone(objExtend);
}
