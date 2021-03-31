#include "vekExtendDebug.h"
#include "ui_common.h"

vekExtendDebug::vekExtendDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekExtendDebug)
{
    ui->setupUi(this);
}

vekExtendDebug::~vekExtendDebug()
{
    exitDebug();
    emit _unVekDebug();
    delete ui;
}
void vekExtendDebug::ConnectDebugObject(QString dockName,QString appCID){
    connect(ui->pushButton_DebugStart,&QPushButton::clicked,this,&vekExtendDebug::startDebug);
    connect(ui->pushButton_DebugDllAdd,&QPushButton::clicked,this,&vekExtendDebug::addDll);
    connect(ui->pushButton_DebugDllDel,&QPushButton::clicked,this,&vekExtendDebug::delDll);
    connect(ui->pushButton_DebugForceExit,&QPushButton::clicked,this,&vekExtendDebug::exitDebug);
    for(auto xz:dllList){
        ui->comboBox_DebugDllList->addItem(xz);
    }
    for(auto a:g_vekLocalData.local_DockerData){
        if(a.first==dockName){
            for(auto b:a.second.docker_Data){
                if(b.second.app_CID==appCID){
                    appData=b.second;
                    dockData=a.second;
                    break;
                }
            }
        }
    }
    QStringList logn;
    logn<<"500"<<"1000"<<"20000"<<"50000";
    ui->comboBox_logint->addItems(logn);
}
void vekExtendDebug::onReadyRead(){
    QByteArray cmdout = m_cmd->readAllStandardOutput();
    ui->logTextEdit->document()->setMaximumBlockCount(ui->comboBox_logint->currentText().toInt());
    if(!cmdout.isEmpty()){
        ui->logTextEdit->append(QString::fromLocal8Bit(cmdout));
    }
    if(ui->radioButton_radiologs->isChecked()){
        QTextCursor cursor=ui->logTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->logTextEdit->setTextCursor(cursor);
    }
}
void vekExtendDebug::addDll(){
    QString xData="+"+ui->comboBox_DebugDllList->currentText();
    if(!DebugDllStr.empty()){
        for(auto x:DebugDllStr){
            if(x==xData){
                return;
            }
        }
        if(DebugDllStr.size()>=1){
            DebugDllStr.append(",");
        }
    }
    DebugDllStr.append(xData);
    upDllStr();
}
void vekExtendDebug::delDll(){
    QString tData;
    if(DebugDllStr.empty()){
        return;
    }
    for(auto x:DebugDllStr){
        tData="+"+ui->comboBox_DebugDllList->currentText();
        if(x==tData){
            DebugDllStr.removeOne(tData);
            if(DebugDllStr.size()>1){
                DebugDllStr.removeLast();
            }
            upDllStr();
        }
    }
}
void vekExtendDebug::startDebug(){
    ExtendApp();
}
//运行环境变量设置
void vekExtendDebug::executeArgsEnv(){
    qInfo()<<dockData.docker_SystemVersion;
    qInfo()<<dockData.docker_WineVersion;
    qInfo()<<dockData.docker_WinePath;
    qInfo()<<dockData.docker_SystemBitVersion;
    qInfo()<<dockData.docker_WineVersion;
    qputenv("WINE", (dockData.docker_WinePath+"/wine/bin/"+dockData.docker_WineVersion).toStdString().c_str());
    //设置容器目录
    qputenv("WINEPREFIX", (dockData.docker_Path+"/"+dockData.docker_Name).toStdString().c_str());
    qputenv("WINEARCH", dockData.docker_SystemBitVersion.toStdString().c_str());
    //设置工作目录
    qputenv("PWD", appData.app_WorkPath.toStdString().c_str());
    qputenv("WINETRICKS_DOWNLOADER", "aria2c");
    if(!appData.app_DockerEnv.empty()){
        for(auto& [a,u]:appData.app_DockerEnv){
            qputenv(a.toStdString().c_str(),u.toStdString().c_str());
        }
    }
    for(auto _env:m_cmd->systemEnvironment()){
        qInfo()<<_env;
    }
}
//执行游戏
void vekExtendDebug::ExtendApp(){
    if(m_cmd!=nullptr){
        delete m_cmd;
        m_cmd=nullptr;
    }
    m_cmd=new QProcess();
    executeArgsEnv();
    QStringList codeArgs;
    QString codeDebug;
    if(!DebugDllStr.empty()){
        codeDebug="WINEDEBUG="+ui->lineEdit_DebugDllStr->text();
    }
    QString gameExe=appData.app_Exe;
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
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
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->setWorkingDirectory(appData.app_WorkPath);
    m_cmd->start("bash");
    connect(m_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(onReadyRead()));
    QString codez;
    //deepin-wine5不支持winecfg /v winxp方式切换容器系统版本。顾采用wine winetricks winxp切换容器系统版本
    if(dockData.docker_WineVersion.contains("deepin",Qt::CaseSensitive)){
        codez=dockData.docker_WinePath+"/wine/bin/"+dockData.docker_WineVersion+" "+dockData.docker_WinePath+"/wine/bin/winetricks "+appData.app_SystemVersion;
    }else{
        codez=dockData.docker_WinePath+"/wine/bin/"+dockData.docker_WineVersion+" "+"winecfg /v "+appData.app_SystemVersion;
    }

    m_cmd->write(codez.toLocal8Bit()+'\n');
    QString codes=codeDebug+" "+dockData.docker_WinePath+"/wine/bin/"+dockData.docker_WineVersion+" "+codeArgs.join(" ");
    m_cmd->write(codes.toLocal8Bit()+'\n');
    qInfo()<<"|++++++++++++++++++++++++++++|";
    qInfo()<<"writeCode:"+codes;
    qInfo()<<"workPath:"+appData.app_WorkPath;
    qInfo()<<"WineArgs:"+codeArgs.join(" ");
    qInfo()<<"|++++++++++++++++++++++++++++|";
}
void vekExtendDebug::exitDebug(){
    std::vector<QStringList> _codeAgrs;
    objectExtend* _objectExtend=new objectExtend();
    OBJTYPE _objType=FORCEKILL;
    _objectExtend->setDockOptionObjectData(dockData,appData.app_CID,_codeAgrs,_objType,BOOTTYPE::BOOTDEFAULT,SERVERTYPE::SERVERDEFAULT);
    _objectExtend->start();
    _objectExtend->wait();
    delete _objectExtend;
    _objectExtend=nullptr;
    if(m_cmd!=nullptr){
        delete m_cmd;
        m_cmd=nullptr;
    }
}
void vekExtendDebug::upDllStr(){
    ui->lineEdit_DebugDllStr->setText(DebugDllStr.join(""));
}
