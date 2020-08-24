#include "objectExtend.h"

objectExtend::objectExtend(QObject *parent) : QThread(parent)
{
    parent=nullptr;
}
objectExtend::~objectExtend(){
    delete m_cmd;
    m_cmd=nullptr;
}
void objectExtend::setDockOptionObjectData(BaseDockData _dockData,QString _appCID,std::vector<QStringList> _agrsList,objectType _objType,objectWineBoot _objWineBootType,objectWineServer _objWineServer){
    appData=GetAppData(_dockData,_appCID);
    dockData=_dockData;
    argsList=_agrsList;
    objType=_objType;
    objWineBootType=_objWineBootType;
    objWineServer=_objWineServer;
    startArgs=dockData.WinePath+"/wine/bin/"+dockData.DockerWineVersion;
}
//运行环境变量设置
void objectExtend::executeArgsEnv(){
    qDebug()<<"wine执行版本:"<<dockData.DockerWineVersion;
    qDebug()<<"容器版本系统版本:"<<dockData.DockerSystemVersion;
    qDebug()<<"Wine版本号:"<<dockData.WineVersion;
    qDebug()<<"容器系统位数版本:"<<dockData.DockerVer;
    qputenv("WINE", (dockData.WinePath+"/wine/bin/"+dockData.DockerWineVersion).toStdString().c_str());
    qputenv("WINEPREFIX", (dockData.DockerPath+"/"+dockData.DockerName).toStdString().c_str());
    qputenv("WINEARCH", dockData.DockerVer.toStdString().c_str());
    qputenv("WINETRICKS_DOWNLOADER", "aria2c");

    if(appData.WorkPath!=nullptr){
        //设置工作目录
        qputenv("PWD", appData.WorkPath.toStdString().c_str());
        if(appData.TaskLog){
            qputenv("WINEDEBUG", "-all");
        }
        if(!appData.DockerEnv.empty()){
            for(auto& [a,u]:appData.DockerEnv){
                qputenv(a.toStdString().c_str(),u.toStdString().c_str());
            }
        }
    }
    for(auto _env:m_cmd->systemEnvironment()){
        qDebug()<<_env;
    }
}
void objectExtend::executeWineBoot(objectWineBoot objWineBootType){
    QStringList wineboot;
    wineboot.clear();
    wineboot.append(dockData.WinePath+"/wine/bin/");
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
        break;
    }
    m_cmd->start(wineboot.join(""),QIODevice::ReadWrite);
    qDebug()<<"wineboot:"<<wineboot.join("");
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
void objectExtend::executeWineServer(objectWineServer objWineServer){
    QStringList wineserver;
    wineserver.clear();
    wineserver.append(dockData.WinePath+"/wine/bin/");
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
        break;
    }
    m_cmd->start(wineserver.join(""),QIODevice::ReadWrite);
    qDebug()<<"wineServer:"<<wineserver.join("");
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
//运行Winetricks
void objectExtend::executeWinetricks(){
    //遗留问题->在运行WineTricks之前需要强制结束当前所有运行的wineserver
    //executeWineServer(object_wineserver_k);
    executeWineBoot(object_wineboot_r);
    QStringList codeArgs;
    bool wType=false;
    qputenv("WINE", (dockData.WinePath+"/wine/bin/wine").toStdString().c_str());
    codeArgs.append(dockData.WinePath+"/wine/bin/winetricks");
    if(objType==object_winetricks_gui){
        codeArgs.append("--gui");
        wType=true;
    }else if(objType==object_winetricks_libs){
        for(auto d:argsList){
            for(auto x:d){

                codeArgs.append(x);
            }
        }
    }
    QString mdCode = codeArgs.join(" ");
    m_cmd->start(mdCode,QIODevice::ReadWrite);
    qDebug()<<"WineTricks:"<<codeArgs.join(" ");
    m_cmd->waitForFinished(-1);
    dockEditSystemVersion();
    waitObjectDone(wType);
}
//执行游戏
void objectExtend::baseExecuteAppCode(QString wcode,QStringList codeArgs){
    executeWineBoot(object_wineboot_r);
    monitorProc();
    appEditSystemVersion();
    m_cmd->closeReadChannel(QProcess::StandardOutput);
    m_cmd->closeReadChannel(QProcess::StandardError);
    m_cmd->setWorkingDirectory(appData.WorkPath);
    m_cmd->start(wcode,codeArgs);
    qDebug()<<"|++++++++++++++++++++++++++++|";
    qDebug()<<"writeCode:"+wcode;
    qDebug()<<"workPath:"+appData.WorkPath;
    qDebug()<<"WineArgs:"+codeArgs.join(" ");
    qDebug()<<"|++++++++++++++++++++++++++++|";
    m_cmd->waitForFinished(-1);
    monitorProc();
    waitObjectDone(true);
    vector<QString>::iterator it;
    for(it=taskList.begin();it!=taskList.end();)
    {
        if(it->toStdString()==appData.MainPrcoName.toStdString())
        {
           taskList.erase(it);
           break;
        }
    }
}
void objectExtend::baseExecuteWineCode(QString code,QStringList codeArgs){
    QString mdCode;
    m_cmd->setReadChannel(QProcess::StandardOutput);
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
void objectExtend::appEditSystemVersion(){
   QStringList codeArgs;
   codeArgs.append("winecfg");
   codeArgs.append("/v");
   codeArgs.append(appData.DockSysVersion);
   baseExecuteWineCode(startArgs,codeArgs);
}
void objectExtend::dockEditSystemVersion(){
   QStringList codeArgs;
   codeArgs.append("winecfg");
   codeArgs.append("/v");
   codeArgs.append(dockData.DockerSystemVersion);
   baseExecuteWineCode(startArgs,codeArgs);
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
void objectExtend::extendApp(){
    QStringList codeArgs;
    QString gameExe=appData.AppExe;
    /*
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
    */
    codeArgs.append(gameExe);
    if(appData.SharedMemory){
        codeArgs.append("STAGING_SHARED_MEMORY=1");
    }
    if(appData.RtServer){
        codeArgs.append("STAGING_RT_PRIORITY_SERVER=60");
    }
    if(appData.WriteCopy){
        codeArgs.append("STAGING_WRITECOPY=1");
    }
    if(appData.AppOtherAgrs!=nullptr){
        codeArgs.append(appData.AppOtherAgrs);
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
         argsList.push_back(DockRegeditStr("add",a.first,b.first,"REG_SZ",appData.WorkPath));
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
    procInfo pi;
    if(!appData.AttachProc.empty()){
        objectProcManage* objProcMangs=new objectProcManage();
        pi.pDockName=dockData.DockerName;
        pi.pDockPath=dockData.DockerPath;
        pi.pWinePath=dockData.WinePath;
        pi.pAttachProc=appData.AttachProc;
        pi.pAttachProc.push_back(appData.MainPrcoName);
        objProcMangs->iprocInfo=pi;
        objProcMangs->start();
        objProcMangs->wait();
        objProcMangs->exit();
        delete objProcMangs;
        objProcMangs=nullptr;
    }
}
void objectExtend::forcekill(){
    procInfo pi;
    objectProcManage* objProcMangs=new objectProcManage();
    pi.pDockName=dockData.DockerName;
    pi.pDockPath=dockData.DockerPath;
    pi.pWinePath=dockData.WinePath;
    pi.pAttachProc=appData.AttachProc;
    if(objType==object_forcekill){;
        pi.pAttachProc.push_back(appData.MainPrcoName);
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
    if(objType==object_winecfg||objType==object_regedit||objType==object_control||objType==object_uninstall)
    {
        optionExtend();
    }else if(objType==object_start){
        extendApp();
    }else if(objType==object_winetricks_gui||objType==object_winetricks_libs){
        executeWinetricks();
    }else if(objType==object_regobject){
        extendWineRegeditCode(startArgs);
    }else if(objType==object_dockSysver){
        dockEditSystemVersion();
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
