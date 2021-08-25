#include "objectDebug.h"

objectDebug::objectDebug(QObject *parent) : QThread(parent)
{

}
void objectDebug::setArgs(SdockerData _dockdata,SappData _appdata,QStringList debugStr){
    dockData=_dockdata;
    appData=_appdata;
    dArgs=debugStr;
}
//运行环境变量设置
void objectDebug::executeArgsEnv(){
    qputenv("WINE", (dockData.s_dockers_wine_path+"/wine/bin/"+dockData.s_dockers_wine_exe_version).toStdString().c_str());
    //设置容器目录
    qputenv("WINEPREFIX", (dockData.s_dockers_path+"/"+dockData.s_dockers_name).toStdString().c_str());
    qputenv("WINEARCH", dockData.s_dockers_bit_version.toStdString().c_str());
    //设置工作目录
    qputenv("PWD", appData.s_work_path.toStdString().c_str());
    qputenv("WINETRICKS_DOWNLOADER", "aria2c");
    if(!appData.map_docker_envs.empty()){
        for(auto& [a,u]:appData.map_docker_envs){
            qputenv(a.toStdString().c_str(),u.toStdString().c_str());
        }
    }
}
void objectDebug::exitDebug(){
    std::vector<QStringList> _codeAgrs;
    objectExtend* _objectExtend=new objectExtend();
    ExtendType exType=EX_DOCKER;
    ExtendArgs exArgs;
    exArgs.ex_docker=object_docker_allforcekill;
    _objectExtend->setDockOptionObjectData(dockData,nullptr,_codeAgrs,exArgs,exType);
    _objectExtend->start();
    _objectExtend->wait();
    delete _objectExtend;
    _objectExtend=nullptr;
}
void objectDebug::outEmit(){
    QByteArray localMsg = xProcess->readAllStandardOutput();
    emit outLogEmit(localMsg);
}
void objectDebug::run(){
    executeArgsEnv();
    exitDebug();
    if(xProcess){
        xProcess->close();
        delete xProcess;
        xProcess=nullptr;
    }
    xProcess=new QProcess();
    QStringList codeArgs;
    QString codeDebug;
    if(!dArgs.empty()){
        codeDebug="WINEDEBUG="+dArgs.join("");
    }
    QString gameExe=appData.s_exe;
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
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
    xProcess->setWorkingDirectory(appData.s_work_path);
    xProcess->setProcessChannelMode(QProcess::ForwardedChannels);
    xProcess->setReadChannel(QProcess::StandardOutput);
    connect(xProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(outEmit()));
    QString codes=codeDebug+" "+dockData.s_dockers_wine_path+"/wine/bin/"+dockData.s_dockers_wine_exe_version+" "+codeArgs.join(" ");
    //QString wcode="WINEPREFIX="+dockData.s_dockers_path+"/"+dockData.s_dockers_name;
    //QString pcode=QApplication::applicationDirPath()+"/vekScript/vekrun";
    //QString scode=wcode+" "+dockData.s_dockers_wine_path+"/wine/bin/"+dockData.s_dockers_wine_exe_version+" "+codeArgs.join(" ");
    xProcess->start(codes);
    xProcess->waitForFinished(-1);
    qInfo()<<"|++++++++++++++++++++++++++++|";
    qInfo()<<"writeCode:"+codes;
    qInfo()<<"workPath:"+appData.s_work_path;
    qInfo()<<"WineArgs:"+codeArgs.join(" ");
    qInfo()<<"|++++++++++++++++++++++++++++|";
}
