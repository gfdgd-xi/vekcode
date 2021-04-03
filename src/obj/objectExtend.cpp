#include "objectExtend.h"

objectExtend::objectExtend(QObject *parent) : QThread(parent)
{
    parent=nullptr;
}
objectExtend::~objectExtend(){
    if(m_cmd){
        m_cmd->close();
        delete m_cmd;
        m_cmd=nullptr;
    }
}
//传入容器和APP运行参数
void objectExtend::setDockOptionObjectData(SdockerData _dockData,QString _appCID,std::vector<QStringList> _agrsList,ExtendType _objType,ExtendBootType _objWineBootType,ExtendServerType _objWineServer){
    appData=pObject::getAppData(_dockData,_appCID);
    dockData=_dockData;
    argsList=_agrsList;
    objType=_objType;
    objWineBootType=_objWineBootType;
    objWineServer=_objWineServer;
    startArgs=dockData.s_dockers_wine_path+"/wine/bin/"+dockData.s_dockers_wine_exe_version;
}
//设置运行环境变量
void objectExtend::executeArgsEnv(){
    //wine执行版本: "wine"
    //容器系统版本: "win7"
    //Wine版本号: "deepin-wine5"
    //容器系统位数版本: "win32"
    qInfo()<<"wine执行版本:"<<dockData.s_dockers_wine_exe_version;
    qInfo()<<"容器系统版本:"<<dockData.s_dockers_system_version;
    qInfo()<<"Wine版本号:"<<dockData.s_dockers_wine_version;
    qInfo()<<"容器系统位数版本:"<<dockData.s_dockers_bit_version;
    qputenv("WINE", (startArgs).toStdString().c_str());
    qputenv("WINEPREFIX", (dockData.s_dockers_path+"/"+dockData.s_dockers_name).toStdString().c_str());
    qputenv("WINEARCH", dockData.s_dockers_bit_version.toStdString().c_str());
    qputenv("WINETRICKS_DOWNLOADER", "aria2c");

    if(appData.s_work_path!=nullptr){
        //设置工作目录
        qputenv("PWD", appData.s_work_path.toStdString().c_str());
        if(appData.b_task_log){
            qputenv("WINEDEBUG", "-all");
        }
        if(!appData.map_docker_regs.empty()){
            for(auto& [a,u]:appData.map_docker_regs){
                qputenv(a.toStdString().c_str(),u.toStdString().c_str());
            }
        }
    }
    for(auto _env:m_cmd->systemEnvironment()){
        qInfo()<<_env;
    }
}
//针对boot的操作
void objectExtend::executeWineBoot(ExtendBootType objWineBootType){
    QStringList wineboot;
    wineboot.clear();
    wineboot.append(dockData.s_dockers_wine_path+"/wine/bin/");
    switch (objWineBootType) {
    case object_wineboot_e:
        //结束会话
        wineboot.append("wineboot -e");
        break;
    case object_wineboot_f:
        //强制关闭假死进程
        wineboot.append("wineboot -f");
        break;
    case object_wineboot_i:
        //初始化wine实例
        wineboot.append("wineboot -i");
        break;
    case object_wineboot_k:
        //立即关闭进程
        wineboot.append("wineboot -k");
        break;
    case object_wineboot_r:
        //重启dock
        wineboot.append("wineboot -r");
        break;
    case object_wineboot_s:
        //关闭dock
        wineboot.append("wineboot -s");
        break;
    case object_wineboot_u:
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
//针对Server操作
void objectExtend::executeWineServer(ExtendServerType objWineServer){
    QStringList wineserver;
    wineserver.clear();
    wineserver.append(dockData.s_dockers_wine_path+"/wine/bin/");
    switch (objWineServer) {
    case object_wineserver_k:
        //结束会话
        wineserver.append("wineserver -k");
        break;
    case object_wineserver_p:
        //强制关闭假死进程
        wineserver.append("wineserver -p");
        break;
    case object_wineserver_w:
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
//针对winetricks的执行
void objectExtend::executeWinetricks(ExtendType _wType){
    executeWineBoot(object_wineboot_r);
    QStringList codeArgs;
    qputenv("WINE", (dockData.s_dockers_wine_path+"/wine/bin/wine").toStdString().c_str());
    codeArgs.append(dockData.s_dockers_wine_path+"/wine/bin/winetricks");
    switch (_wType) {
      case object_winetricks_gui:
        executeWinetricks_gui(codeArgs);
        break;
    case object_winetricks_cmd_libs:
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
    if(dockData.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
        switchSysVersion(DOCKER,DEEPIN);
    }else{
        switchSysVersion(DOCKER,WINEHQ);
    }
    waitObjectDone(wType);
}
//执行运行APP
void objectExtend::baseExecuteAppCode(QString wcode,QStringList codeArgs){
    executeWineBoot(object_wineboot_r);
    forcekill();
    if(dockData.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
        switchSysVersion(DOCKER,DEEPIN);
    }else{
        switchSysVersion(DOCKER,WINEHQ);
    }
    m_cmd->closeReadChannel(QProcess::StandardOutput);
    m_cmd->closeReadChannel(QProcess::StandardError);
    m_cmd->setWorkingDirectory(appData.s_work_path);
    m_cmd->start(wcode,codeArgs);
    qInfo()<<"|++++++++++++++++++++++++++++|";
    qInfo()<<"writeCode:"+wcode;
    qInfo()<<"workPath:"+appData.s_work_path;
    qInfo()<<"WineArgs:"+codeArgs.join(" ");
    qInfo()<<"|++++++++++++++++++++++++++++|";
    m_cmd->waitForFinished(-1);
    forcekill();
    waitObjectDone(true);
    vector<QString>::iterator it;
    for(it=taskList.begin();it!=taskList.end();)
    {
        if(it->toStdString()==appData.s_main_proc_name.toStdString())
        {
           taskList.erase(it);
           break;
        }
    }
}
//wintricks和常规命令执行
void objectExtend::baseExecuteWineCode(QString code,QStringList codeArgs){
    QString mdCode;
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->start(code,codeArgs,QIODevice::ReadWrite);
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
//执行注册表
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
       codeArgs.append(appData.s_dock_system_version);
   }else{
       codeArgs.append(dockData.s_dockers_system_version);
   }

   baseExecuteWineCode(startArgs,codeArgs);
}
//deepin-wine5容器系统版本切换
void objectExtend::deepinSwitchSysVerion(SWITCH_SYSTEM_VERSION ssv){
    executeWineBoot(object_wineboot_r);
    QStringList codeArgs;
    qputenv("WINE", (dockData.s_dockers_wine_path+"/wine/bin/wine").toStdString().c_str());
    codeArgs.append(dockData.s_dockers_wine_path+"/wine/bin/winetricks");
    if(ssv==APP){
        codeArgs.append(appData.s_dock_system_version);
    }else{
        codeArgs.append(dockData.s_dockers_system_version);
    }
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
//容器基本功能
void objectExtend::optionExtend(){
    QStringList codeArgs;
    if(objType==object_winecfg){
        codeArgs.append("winecfg");
    }
    if(objType==object_regedit){
        codeArgs.append("regedit");
    }
    if(objType==object_control){
        codeArgs.append("control");
    }
    if(objType==object_uninstall){
        codeArgs.append("uninstaller");
    }
    baseExecuteWineCode(startArgs,codeArgs);
}
//APP运行差异化参数
void objectExtend::extendApp(){
    QStringList codeArgs;
    QString gameExe=appData.s_exe;
    /*
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
    */
    codeArgs.append(gameExe);
    if(appData.b_sharedmemory){
        codeArgs.append("STAGING_SHARED_MEMORY=1");
    }
    if(appData.b_rtserver){
        codeArgs.append("STAGING_RT_PRIORITY_SERVER=60");
    }
    if(appData.b_writecopy){
        codeArgs.append("STAGING_WRITECOPY=1");
    }
    if(appData.s_agrs_code!=nullptr){
        codeArgs.append(appData.s_agrs_code);
    }
    dyncDxvkRegs(dxvkResCache);
    dyncDxvkRegs(dxvkResLog);
    baseExecuteAppCode(startArgs,codeArgs);
    emit objexitTray(false);
}
//同步dxvk
void objectExtend::dyncDxvkRegs(std::map<QString,std::map<QString,QString>> dxvkResStr){
    for(auto a:dxvkResStr){
        for(auto b:a.second){
         argsList.clear();
         argsList.push_back(pObject::dockerRegeditStr("add",a.first,b.first,"REG_SZ",appData.s_work_path));
        }
    }
    extendWineRegeditCode(startArgs);
}
//执行gecko和mono组件
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
void objectExtend::forcekill(){
    SappProcData pi;
    objectProcManage* objProcMangs=new objectProcManage();
    pi.s_proc_docker_name=dockData.s_dockers_name;
    pi.s_proc_docker_path=dockData.s_dockers_path;
    pi.s_proc_wine_path=dockData.s_dockers_wine_path;
    pi.vec_proc_attach_list=appData.vec_proc_attach_list;
    pi.vec_proc_attach_list.push_back(appData.s_main_proc_name);
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
    if(objType==object_winecfg||objType==object_regedit||objType==object_control||objType==object_uninstall)
    {
        optionExtend();
    }else if(objType==object_start){
        extendApp();
    }else if(objType==object_winetricks_gui||objType==object_winetricks_cmd_libs){
        executeWinetricks(objType);
    }else if(objType==object_regobject){
        extendWineRegeditCode(startArgs);
    }else if(objType==object_dockSysver){
        if(dockData.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
            switchSysVersion(DOCKER,DEEPIN);
        }else{
            switchSysVersion(DOCKER,WINEHQ);
        }
    }else if(objType==object_wineboot){
        executeWineBoot(objWineBootType);
    }else if(objType==object_wineserver){
        executeWineServer(objWineServer);
    }else if(objType==object_plugs){
        extendPlugs();
    }else if(objType==object_forcekill){
        forcekill();
    }
    executeWineBoot(object_wineboot_r);
}
