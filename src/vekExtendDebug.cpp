#include "vekExtendDebug.h"
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
void vekExtendDebug::ConnectDebugObject(){
    connect(ui->pushButton_DebugStart,&QPushButton::clicked,this,&vekExtendDebug::startDebug);
    connect(ui->pushButton_DebugDllAdd,&QPushButton::clicked,this,&vekExtendDebug::addDll);
    connect(ui->pushButton_DebugDllDel,&QPushButton::clicked,this,&vekExtendDebug::delDll);
    connect(ui->pushButton_DebugForceExit,&QPushButton::clicked,this,&vekExtendDebug::exitDebug);
    for(auto xz:dllList){
        ui->comboBox_DebugDllList->addItem(xz);
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
    ExtendApp(_data);
}
//运行环境变量设置
void vekExtendDebug::executeArgsEnv(BaseAppData data){
    QString dockPath =data.dockPath+"/"+data.dockName;
    QDir dockDir(dockPath);
    QString winePath=data.winePath+"wine/bin/wine";
    qputenv("WINE", winePath.toStdString().c_str());
    //设置容器目录
    qputenv("WINEPREFIX", dockPath.toStdString().c_str());
    //设置工作目录
    qputenv("PWD", data.workPath.toStdString().c_str());
    if(!data.dockEnv.empty()){
        for(auto& [a,u]:data.dockEnv){
            qputenv(a.toStdString().c_str(),u.toStdString().c_str());
        }
    }
    //输出环境变量

    for(auto _env:m_cmd->systemEnvironment()){
        qDebug()<<_env;
    }
}
//执行游戏
void vekExtendDebug::ExtendApp(BaseAppData _dataApp){
    if(m_cmd!=nullptr){
        delete m_cmd;
        m_cmd=nullptr;
    }
    m_cmd=new QProcess();
    _data=_dataApp;
    executeArgsEnv(_dataApp);
    QStringList codeArgs;
    QString codeDebug;
    if(!DebugDllStr.empty()){
        codeDebug="WINEDEBUG="+ui->lineEdit_DebugDllStr->text();
    }
    QString gameExe=_dataApp.appExe;
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
    codeArgs.append(gameExe);
    if(_dataApp.taskMemorySharing){
        codeArgs.append("STAGING_SHARED_MEMORY=1");
    }
    if(_dataApp.taskRealTimePriority){
        codeArgs.append("STAGING_RT_PRIORITY_SERVER=60");
    }
    if(_dataApp.taskMemoryOptimization){
        codeArgs.append("STAGING_WRITECOPY=1");
    }
    if(_dataApp.appOtherAgrs!=nullptr){
        codeArgs.append(_dataApp.appOtherAgrs);
    }
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->setWorkingDirectory(_dataApp.workPath);
    m_cmd->start("bash");
    connect(m_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(onReadyRead()));
    QString codes=codeDebug+" "+_data.winePath+"wine/bin/wine"+" "+codeArgs.join(" ");
    m_cmd->write(codes.toLocal8Bit()+'\n');
    qDebug()<<"|++++++++++++++++++++++++++++|";
    qDebug()<<"writeCode:"+codes;
    qDebug()<<"workPath:"+_dataApp.workPath;
    qDebug()<<"WineArgs:"+codeArgs.join(" ");
    qDebug()<<"|++++++++++++++++++++++++++++|";
}
void vekExtendDebug::exitDebug(){
    std::vector<QStringList> _codeAgrs;
    objectExtend* _objectExtend=new objectExtend();
    objectType _objType=object_forcekill;
    connect(this, SIGNAL(toObjectArgs(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)), _objectExtend, SLOT(setDockOptionObjectData(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)));
    emit(toObjectArgs(_data,_codeAgrs,_objType,objectWineBoot::object_wineboot_default,objectWineServer::object_wineserver_default));
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
