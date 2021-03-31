#include "objectExtend.h"

objectExtend::objectExtend(QObject *parent) : QThread(parent)
{
    parent=nullptr;
}
objectExtend::~objectExtend(){
    delete m_cmd;
    m_cmd=nullptr;
}
void objectExtend::setDockOptionObjectData(DockData _dockData,QString _appCID,std::vector<QStringList> _agrsList,OBJTYPE _objType,BOOTTYPE _objWineBootType,SERVERTYPE _objWineServer){
    appData=pObject::getAppData(_dockData,_appCID);
    dockData=_dockData;
    argsList=_agrsList;
    objType=_objType;
    objWineBootType=_objWineBootType;
    objWineServer=_objWineServer;
    startArgs=dockData.docker_WinePath+"/wine/bin/"+dockData.docker_WineVersion;
}
//运行环境变量设置
void objectExtend::executeArgsEnv(){
    qInfo()<<"wine执行版本:"<<dockData.docker_WineVersion;
    qInfo()<<"容器版本系统版本:"<<dockData.docker_SystemVersion;
    qInfo()<<"Wine版本号:"<<dockData.docker_WineExeVersion;
    qInfo()<<"容器系统位数版本:"<<dockData.docker_SystemBitVersion;
    qputenv("WINE", (dockData.docker_WinePath+"/wine/bin/"+dockData.docker_WineVersion).toStdString().c_str());
    qputenv("WINEPREFIX", (dockData.docker_Path+"/"+dockData.docker_Name).toStdString().c_str());
    qputenv("WINEARCH", dockData.docker_SystemBitVersion.toStdString().c_str());
    qputenv("WINETRICKS_DOWNLOADER", "aria2c");

    if(appData.app_WorkPath!=nullptr){
        //设置工作目录
        qputenv("PWD", appData.app_WorkPath.toStdString().c_str());
        if(appData.app_TaskLog){
            qputenv("WINEDEBUG", "-all");
        }
        if(!appData.app_DockerEnv.empty()){
            for(auto& [a,u]:appData.app_DockerEnv){
                qputenv(a.toStdString().c_str(),u.toStdString().c_str());
            }
        }
    }
    for(auto _env:m_cmd->systemEnvironment()){
        qInfo()<<_env;
    }
}
void objectExtend::executeWineBoot(BOOTTYPE objWineBootType){
    QStringList wineboot;
    wineboot.clear();
    wineboot.append(dockData.docker_WinePath+"/wine/bin/");
    switch (objWineBootType) {
    case BOOTE:
        //结束会话
        wineboot.append("wineboot -e");
        break;
    case BOOTF:
        //强制关闭假死进程
        wineboot.append("wineboot -f");
        break;
    case BOOTI:
        //初始化wine实例
        wineboot.append("wineboot -i");
        break;
    case BOOTK:
        //立即关闭进程
        wineboot.append("wineboot -k");
        break;
    case BOOTR:
        //重启dock
        wineboot.append("wineboot -r");
        break;
    case BOOTS:
        //关闭dock
        wineboot.append("wineboot -s");
        break;
    case BOOTU:
        //更新dock
        wineboot.append("wineboot -u");
        break;
    default:
        return;
        //break;
    }
    m_cmd->start(wineboot.join(""),QIODevice::ReadWrite);
    qInfo()<<"wineboot:"<<wineboot.join("");
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
void objectExtend::executeWineServer(SERVERTYPE objWineServer){
    QStringList wineserver;
    wineserver.clear();
    wineserver.append(dockData.docker_WinePath+"/wine/bin/");
    switch (objWineServer) {
    case SERVERK:
        //结束会话
        wineserver.append("wineserver -k");
        break;
    case SERVERP:
        //强制关闭假死进程
        wineserver.append("wineserver -p");
        break;
    case SERVERW:
        //初始化wine实例
        wineserver.append("wineserver -w");
        break;
    default:
        return;
        //break;
    }
    m_cmd->start(wineserver.join(""),QIODevice::ReadWrite);
    qInfo()<<"wineServer:"<<wineserver.join("");
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
void objectExtend::executeWinetricks(OBJTYPE _wType){
    executeWineBoot(BOOTR);
    QStringList codeArgs;
    qputenv("WINE", (dockData.docker_WinePath+"/wine/bin/wine").toStdString().c_str());
    codeArgs.append(dockData.docker_WinePath+"/wine/bin/winetricks");
    switch (_wType) {
      case WINETRICKSGUI:
        executeWinetricks_gui(codeArgs);
        break;
    case WINETRICKSLIBS:
        executeWinetricks_cmd_libs(codeArgs);
        break;
    }
}
//winetricks gui模式
void objectExtend::executeWinetricks_gui(QStringList cArgs){
   cArgs.append("--gui");
   ExtendWinetricksCode(cArgs,true);
}
//winetricks 命令和静默libs安装模式
void objectExtend::executeWinetricks_cmd_libs(QStringList cArgs){
    for(auto d:argsList){
        for(auto x:d){
            cArgs.append(x);
        }
    }
   ExtendWinetricksCode(cArgs,false);
}
//winetricks执行命令
void objectExtend::ExtendWinetricksCode(QStringList cArgs,bool wType){
    QString mdCode = cArgs.join(" ");
    m_cmd->start(mdCode,QIODevice::ReadWrite);
    qInfo()<<"WineTricks:"<<cArgs.join(" ");
    m_cmd->waitForFinished(-1);
    if(dockData.docker_WineVersion.contains("deepin",Qt::CaseSensitive)){
        switchSysVersion(DOCKER,DEEPIN);
    }else{
        switchSysVersion(DOCKER,WINEHQ);
    }
    waitObjectDone(wType);
}
//执行游戏
void objectExtend::baseExecuteAppCode(QString wcode,QStringList codeArgs){
    executeWineBoot(BOOTR);
    monitorProc();
    if(dockData.docker_WineVersion.contains("deepin",Qt::CaseSensitive)){
        switchSysVersion(DOCKER,DEEPIN);
    }else{
        switchSysVersion(DOCKER,WINEHQ);
    }
    m_cmd->closeReadChannel(QProcess::StandardOutput);
    m_cmd->closeReadChannel(QProcess::StandardError);
    m_cmd->setWorkingDirectory(appData.app_WorkPath);
    m_cmd->start(wcode,codeArgs);
    qInfo()<<"|++++++++++++++++++++++++++++|";
    qInfo()<<"writeCode:"+wcode;
    qInfo()<<"workPath:"+appData.app_WorkPath;
    qInfo()<<"WineArgs:"+codeArgs.join(" ");
    qInfo()<<"|++++++++++++++++++++++++++++|";
    m_cmd->waitForFinished(-1);
    monitorProc();
    waitObjectDone(true);
    vector<QString>::iterator it;
    for(it=taskList.begin();it!=taskList.end();)
    {
        if(it->toStdString()==appData.app_MainProcName.toStdString())
        {
           taskList.erase(it);
           break;
        }
    }
}
void objectExtend::baseExecuteWineCode(QString code,QStringList codeArgs){
    QString mdCode;
    m_cmd->setReadChannel(QProcess::StandardOutput);
    qInfo()<<"this:"<<code;
    qInfo()<<"this:"<<codeArgs;
    m_cmd->start(code,codeArgs,QIODevice::ReadWrite);
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
//wineRegedit
void objectExtend::extendWineRegeditCode(QString code){
    for(auto regStr:argsList){
        QString mdCode=code+" "+regStr.join(" ");
        m_cmd->start(mdCode,QIODevice::ReadWrite);
        m_cmd->waitForFinished(-1);
    }
    waitObjectDone(true);
}
//容器系统版本切换
void objectExtend::switchSysVersion(SWITCH_SYSTEM_VERSION ssv,SWITCH_WINE_SYSTEM_VERSION swsv){
    switch(swsv){
    case::WINEHQ:
        hqSwitchSysVersion(ssv);
        break;
    default:
        deepinSwitchSysVerion(ssv);
    }
}
//WineHQ容器系统版本切换
void objectExtend::hqSwitchSysVersion(SWITCH_SYSTEM_VERSION ssv){
   QStringList codeArgs;
   codeArgs.append("winecfg");
   codeArgs.append("/v");
   if(ssv==APP){
       codeArgs.append(appData.app_SystemVersion);
   }
   codeArgs.append(dockData.docker_SystemVersion);
   baseExecuteWineCode(startArgs,codeArgs);
}
//deepin-wine5容器系统版本切换
void objectExtend::deepinSwitchSysVerion(SWITCH_SYSTEM_VERSION ssv){
    executeWineBoot(BOOTR);
    QStringList codeArgs;
    qputenv("WINE", (dockData.docker_WinePath+"/wine/bin/wine").toStdString().c_str());
    codeArgs.append(dockData.docker_WinePath+"/wine/bin/winetricks");
    if(ssv==APP){
        codeArgs.append(appData.app_SystemVersion);
    }
    codeArgs.append(dockData.docker_SystemVersion);
    QString mdCode = codeArgs.join(" ");
    m_cmd->start(mdCode,QIODevice::ReadWrite);
    qInfo()<<"WineTricks:"<<codeArgs.join(" ");
    m_cmd->waitForFinished(-1);
}

//等待任务结束
void objectExtend::waitObjectDone(bool objState){
    if(!objState){
        m_cmd->close();
    }else{
        m_cmd->close();
        m_cmd->kill();
    }
}
void objectExtend::optionExtend(){
    QStringList codeArgs;
    if(objType==WINECFG){
        codeArgs.append("winecfg");
    }
    if(objType==REGEDIT){
        codeArgs.append("regedit");
    }
    if(objType==CONTROL){
        codeArgs.append("control");
    }
    if(objType==REMOVE){
        codeArgs.append("uninstaller");
    }
    baseExecuteWineCode(startArgs,codeArgs);
}
void objectExtend::extendApp(){
    QStringList codeArgs;
    QString gameExe=appData.app_Exe;
    /*
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
    */
    codeArgs.append(gameExe);
    if(appData.app_SharedMemory){
        codeArgs.append("STAGING_SHARED_MEMORY=1");
    }
    if(appData.app_RtServer){
        codeArgs.append("STAGING_RT_PRIORITY_SERVER=60");
    }
    if(appData.app_WriteCopy){
        codeArgs.append("STAGING_WRITECOPY=1");
    }
    if(appData.app_AgrsCode!=nullptr){
        codeArgs.append(appData.app_AgrsCode);
    }
    dyncDxvkRegs(dxvkResCache);
    dyncDxvkRegs(dxvkResLog);
    baseExecuteAppCode(startArgs,codeArgs);
    emit objexitTray(false);
}

void objectExtend::dyncDxvkRegs(std::map<QString,std::map<QString,QString>> dxvkResStr){
    for(auto a:dxvkResStr){
        for(auto b:a.second){
         argsList.clear();
         argsList.push_back(pObject::dockerRegeditStr("add",a.first,b.first,"REG_SZ",appData.app_WorkPath));
        }
    }
    extendWineRegeditCode(startArgs);
}
void objectExtend::extendPlugs(){
    QStringList codeArgs;
    for(auto a:argsList){
        for(auto b:a){
            codeArgs.clear();
            codeArgs.append("msiexec");
            codeArgs.append("/i");
            codeArgs.append(b);
            baseExecuteWineCode(startArgs,codeArgs);
        }
    }
}
void objectExtend::monitorProc(){
    ProcInfo pi;
    if(!appData.app_Attachproc.empty()){
        objectProcManage* objProcMangs=new objectProcManage();
        pi.pDockName=dockData.docker_Name;
        pi.pDockPath=dockData.docker_Path;
        pi.pWinePath=dockData.docker_WinePath;
        pi.pAttachProc=appData.app_Attachproc;
        pi.pAttachProc.push_back(appData.app_MainProcName);
        objProcMangs->iprocInfo=pi;
        objProcMangs->start();
        objProcMangs->wait();
        objProcMangs->exit();
        delete objProcMangs;
        objProcMangs=nullptr;
    }
}
void objectExtend::forcekill(){
    ProcInfo pi;
    objectProcManage* objProcMangs=new objectProcManage();
    pi.pDockName=dockData.docker_Name;
    pi.pDockPath=dockData.docker_Path;
    pi.pWinePath=dockData.docker_WinePath;
    pi.pAttachProc=appData.app_Attachproc;
    if(objType==FORCEKILL){
        pi.pAttachProc.push_back(appData.app_MainProcName);
    }
    objProcMangs->iprocInfo=pi;
    objProcMangs->start();
    objProcMangs->wait();
    objProcMangs->exit();
    delete objProcMangs;
    objProcMangs=nullptr;
}
void objectExtend::run(){
    m_cmd=new QProcess();
    executeArgsEnv();
    if(objType==WINECFG||objType==REGEDIT||objType==CONTROL||objType==REMOVE)
    {
        optionExtend();
    }else if(objType==START){
        extendApp();
    }else if(objType==WINETRICKSGUI||objType==WINETRICKSLIBS){
        executeWinetricks(objType);
    }else if(objType==REGOBJ){
        extendWineRegeditCode(startArgs);
    }else if(objType==DOCKSYSVER){
        if(dockData.docker_WineVersion.contains("deepin",Qt::CaseSensitive)){
            switchSysVersion(DOCKER,DEEPIN);
        }else{
            switchSysVersion(DOCKER,WINEHQ);
        }
    }else if(objType==BOOT){
        executeWineBoot(objWineBootType);
    }else if(objType==SERVER){
        executeWineServer(objWineServer);
    }else if(objType==PLUGS){
        extendPlugs();
    }else if(objType==FORCEKILL){
        forcekill();
    }
    executeWineBoot(BOOTR);
}
