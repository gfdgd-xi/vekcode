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
    if(m_cmd){
        m_cmd->close();
        delete m_cmd;
        m_cmd=nullptr;
    }
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
    for(auto a:g_vekLocalData.map_docker_list){
        if(a.first==dockName){
            for(auto b:a.second.map_dockers_data){
                if(b.second.s_uid==appCID){
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
    qInfo()<<dockData.s_dockers_system_version;
    qInfo()<<dockData.s_dockers_wine_version;
    qInfo()<<dockData.s_dockers_wine_path;
    qInfo()<<dockData.s_dockers_bit_version;
    qInfo()<<dockData.s_dockers_wine_exe_version;
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
    for(auto _env:m_cmd->systemEnvironment()){
        qInfo()<<_env;
    }
}
//执行游戏
void vekExtendDebug::ExtendApp(){
    if(m_cmd){
        m_cmd->close();
        delete m_cmd;
        m_cmd=nullptr;
    }
    m_cmd=new QProcess();
    executeArgsEnv();
    exitDebug();
    QStringList codeArgs;
    QString codeDebug;
    if(!DebugDllStr.empty()){
        codeDebug="WINEDEBUG="+ui->lineEdit_DebugDllStr->text();
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
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->setWorkingDirectory(appData.s_work_path);
    m_cmd->start("bash");
    connect(m_cmd,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(m_cmd,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(onReadyRead()));
    connect(m_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(onReadyRead()));    
    QString codez;
    //deepin-wine5不支持winecfg /v winxp方式切换容器系统版本。顾采用wine winetricks winxp切换容器系统版本
    if(dockData.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
        codez=dockData.s_dockers_wine_path+"/wine/bin/winetricks "+appData.s_dock_system_version;
    }else{
        codez=dockData.s_dockers_wine_path+"/wine/bin/"+dockData.s_dockers_wine_exe_version+" "+"winecfg /v "+appData.s_dock_system_version;
    }

    m_cmd->write(codez.toLocal8Bit()+'\n');
    QString codes=codeDebug+" "+dockData.s_dockers_wine_path+"/wine/bin/"+dockData.s_dockers_wine_exe_version+" "+codeArgs.join(" ");
    m_cmd->write(codes.toLocal8Bit()+'\n');
    qInfo()<<"|++++++++++++++++++++++++++++|";
    qInfo()<<"writeCode:"+codes;
    qInfo()<<"workPath:"+appData.s_work_path;
    qInfo()<<"WineArgs:"+codeArgs.join(" ");
    qInfo()<<"|++++++++++++++++++++++++++++|";
}
void vekExtendDebug::exitDebug(){
    std::vector<QStringList> _codeAgrs;
    objectExtend* _objectExtend=new objectExtend();
    ExtendType exType=EX_APP;
    ExtendArgs exArgs;
    exArgs.ex_app=object_app_forcekill;
    _objectExtend->setDockOptionObjectData(dockData,appData.s_uid,_codeAgrs,exArgs,exType);
    _objectExtend->start();
    _objectExtend->wait();
    delete _objectExtend;
    _objectExtend=nullptr;
}
void vekExtendDebug::upDllStr(){
    ui->lineEdit_DebugDllStr->setText(DebugDllStr.join(""));
}
