﻿#include "vekExtendDebug.h"
#include "ui_common.h"

vekExtendDebug::vekExtendDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekExtendDebug)
{
    ui->setupUi(this);
    vek_Style(this,0);
}

vekExtendDebug::~vekExtendDebug()
{
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
    for(auto a:g_vekLocalData.dockerVec){
        if(a.first==dockName){
            for(auto b:a.second.dData){
                if(b.second.AppCID==appCID){
                    appData=b.second;
                    dockData=a.second;
                    break;
                }
            }
        }
    }
}
void vekExtendDebug::onReadyRead(){
    QByteArray cmdout = m_cmd->readAllStandardOutput();
    if(!cmdout.isEmpty()){
        ui->logTextEdit->append(QString::fromLocal8Bit(cmdout));
    }
    QTextCursor cursor=ui->logTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logTextEdit->setTextCursor(cursor);
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
    qputenv("WINE", (dockData.WinePath+"/wine/bin/"+dockData.WineVersion).toStdString().c_str());
    //设置容器目录
    qputenv("WINEPREFIX", (dockData.DockerPath+"/"+dockData.DockerName).toStdString().c_str());
    qputenv("WINEARCH", dockData.DockerVer.toStdString().c_str());
    //设置工作目录
    qputenv("PWD", appData.WorkPath.toStdString().c_str());
    qputenv("WINETRICKS_DOWNLOADER", "aria2c");
    if(!appData.DockerEnv.empty()){
        for(auto& [a,u]:appData.DockerEnv){
            qputenv(a.toStdString().c_str(),u.toStdString().c_str());
        }
    }
    for(auto _env:m_cmd->systemEnvironment()){
        qDebug()<<_env;
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
    QString gameExe=appData.AppExe;
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
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
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->setWorkingDirectory(appData.WorkPath);
    m_cmd->start("bash");
    connect(m_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(onReadyRead()));
    QString codes=codeDebug+" "+dockData.WinePath+"/wine/bin/"+dockData.DockerWineVersion+" "+codeArgs.join(" ");
    m_cmd->write(codes.toLocal8Bit()+'\n');
    qDebug()<<"|++++++++++++++++++++++++++++|";
    qDebug()<<"writeCode:"+codes;
    qDebug()<<"workPath:"+appData.WorkPath;
    qDebug()<<"WineArgs:"+codeArgs.join(" ");
    qDebug()<<"|++++++++++++++++++++++++++++|";
}
void vekExtendDebug::exitDebug(){
    std::vector<QStringList> _codeAgrs;
    objectExtend* _objectExtend=new objectExtend();
    objectType _objType=object_forcekill;
    connect(this, SIGNAL(toObjectArgs(BaseDockData,QString,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)), _objectExtend, SLOT(setDockOptionObjectData(BaseDockData,QString,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)));
    emit(toObjectArgs(dockData,appData.AppCID,_codeAgrs,_objType,objectWineBoot::object_wineboot_default,objectWineServer::object_wineserver_default));
    _objectExtend->start();
    _objectExtend->wait();
    delete _objectExtend;
    _objectExtend=nullptr;
    if(m_cmd!=nullptr){
        delete m_cmd;
        m_cmd=nullptr;
    }
    delete _objectExtend;
    _objectExtend=nullptr;
}
void vekExtendDebug::upDllStr(){
    ui->lineEdit_DebugDllStr->setText(DebugDllStr.join(""));
}
