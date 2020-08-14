﻿#include "objectExtend.h"

objectExtend::objectExtend(QObject *parent) : QThread(parent)
{
    parent=nullptr;
}
objectExtend::~objectExtend(){
    delete m_cmd;
    m_cmd=nullptr;
}
void objectExtend::setDockOptionObjectData(BaseDockData _dockData,QString _appCID,std::vector<QStringList> _agrsList,objectType _objType,objectWineBoot _objWineBootType,objectWineServer _objWineServer){
    if(_appCID!=nullptr){
        for(auto a:_dockData.dData){
            if(a.first==_appCID){
                data=a.second;
                break;
            }
        }
    }
    dockData=_dockData;
    argsList=_agrsList;
    objType=_objType;
    objWineBootType=_objWineBootType;
    objWineServer=_objWineServer;
    startArgs=_dockData.WinePath+"wine/bin/"+_dockData.DockerVer;
}
//运行环境变量设置
void objectExtend::executeArgsEnv(){
    qputenv("WINE", (dockData.WinePath+"wine/bin/"+dockData.WineVersion).toStdString().c_str());
    //设置容器目录
    qputenv("WINEPREFIX", (dockData.DockerPath+"/"+dockData.DockerName).toStdString().c_str());
    qputenv("WINEARCH", dockData.DockerVer.toStdString().c_str());
    //设置工作目录
    qputenv("PWD", data.WorkPath.toStdString().c_str());
    qputenv("WINETRICKS_DOWNLOADER", "aria2c");
    if(data.TaskLog){
        qputenv("WINEDEBUG", "-all");
    }
    if(!data.DockerEnv.empty()){
        for(auto& [a,u]:data.DockerEnv){
            qputenv(a.toStdString().c_str(),u.toStdString().c_str());
        }
    }
    for(auto _env:m_cmd->systemEnvironment()){
        qDebug()<<_env;
    }
}
void objectExtend::executeWineBoot(objectWineBoot objWineBootType){
    QStringList wineboot;
    wineboot.append(dockData.WinePath+"wine/bin/");
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
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
void objectExtend::executeWineServer(objectWineServer objWineServer){
    QStringList wineserver;
    wineserver.append(dockData.WinePath+"wine/bin/");
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
    m_cmd->waitForFinished(-1);
    waitObjectDone(true);
}
//运行Winetricks
void objectExtend::executeWinetricks(){
    //遗留问题->在运行WineTricks之前需要强制结束当前所有运行的wineserver
    //executeWineServer(object_wineserver_k);
    //executeWineBoot(object_wineboot_k);
    QStringList codeArgs;
    codeArgs.append(dockData.WinePath+"wine/bin/winetricks");
    if(objType==object_winetricks_gui){
        codeArgs.append("--gui");
    }else if(objType==object_winetricks_libs){
        for(auto d:argsList){
            for(auto x:d){
                codeArgs.append(x);
            }
        }
    }
    QString mdCode = codeArgs.join(" ");
    m_cmd->start(mdCode,QIODevice::ReadWrite);
    m_cmd->waitForFinished(-1);
    dockEditSystemVersion();
    waitObjectDone(false);   
}
//执行游戏
void objectExtend::baseExecuteAppCode(QString wcode,QStringList codeArgs){
    executeWineBoot(object_wineboot_r);
    monitorProc();
    dockEditSystemVersion();  
    m_cmd->closeReadChannel(QProcess::StandardOutput);
    m_cmd->closeReadChannel(QProcess::StandardError);
    m_cmd->setWorkingDirectory(data.WorkPath);
    m_cmd->execute(wcode,codeArgs);
    qDebug()<<"|++++++++++++++++++++++++++++|";
    qDebug()<<"writeCode:"+wcode;
    qDebug()<<"workPath:"+data.WorkPath;
    qDebug()<<"WineArgs:"+codeArgs.join(" ");
    qDebug()<<"|++++++++++++++++++++++++++++|";
    monitorProc();
    waitObjectDone(true);
    vector<QString>::iterator it;
    for(it=taskList.begin();it!=taskList.end();)
    {
        if(it->toStdString()==data.MainPrcoName.toStdString())
        {
           taskList.erase(it);
           break;
        }
    }
}
void objectExtend::baseExecuteWineCode(QString code,QStringList codeArgs){
    QString mdCode;
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->setWorkingDirectory(data.WorkPath);
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
        qDebug()<<mdCode;
    }
    waitObjectDone(true);
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
    QString gameExe=data.AppExe;
    /*
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
    */
    codeArgs.append(gameExe);
    if(data.TaskMemorySharing){
        codeArgs.append("STAGING_SHARED_MEMORY=1");
    }
    if(data.TaskRealTimePriority){
        codeArgs.append("STAGING_RT_PRIORITY_SERVER=60");
    }
    if(data.TaskMemoryOptimization){
        codeArgs.append("STAGING_WRITECOPY=1");
    }
    if(data.AppOtherAgrs!=nullptr){
        codeArgs.append(data.AppOtherAgrs);
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
         argsList.push_back(DockRegeditStr("add",a.first,b.first,"REG_SZ",data.WorkPath));
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
    if(!data.AttachProc.empty()){
        objectProcManage* objProcMangs=new objectProcManage();
        pi.pDockName=dockData.DockerName;
        pi.pDockPath=dockData.DockerPath;
        pi.pWinePath=dockData.WinePath;
        pi.pAttachProc=data.AttachProc;
        pi.pAttachProc.push_back(data.MainPrcoName);
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
    pi.pAttachProc=data.AttachProc;
    if(objType==object_forcekill){;
        pi.pAttachProc.push_back(data.MainPrcoName);
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
