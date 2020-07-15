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
    delete ui;
    m_cmd->close();
    m_cmd->kill();
    delete m_cmd;
    m_cmd=nullptr;
}
void vekExtendDebug::exitProc(QString info){
    if(d_cmd){
        delete d_cmd;
        d_cmd=nullptr;
    }
    d_cmd=new QProcess();
    d_cmd->start("bash");
    QStringList list1 = info.split("\n");
    QString procName="onmyoji";
    QString procPid;
    for(auto a:list1){
        if(a.contains(procName,Qt::CaseSensitive)){
            bool ok;
            procPid=QString::number(a.left(10).toLongLong(&ok,16));
            qDebug()<<procPid;
            break;
        }
    }
    if(procPid!=NULL){
        QString pCodes="WINEPREFIX="+_data.dockPath+"/"+_data.dockName+" "+_data.winePath+"wine/bin/winedbg";
        QString dCodes="attach "+procPid;
        QString kCodes="kill";
        QString qCodes="quit";
        d_cmd->write(pCodes.toLocal8Bit()+'\n');
        d_cmd->write(dCodes.toLocal8Bit()+'\n');
        d_cmd->write(kCodes.toLocal8Bit()+'\n');
        d_cmd->write(qCodes.toLocal8Bit()+'\n');
    }
}
void vekExtendDebug::onReadyRead(){
    QByteArray cmdout = m_cmd->readAll();
    if(!cmdout.isEmpty()){
        ui->logTextEdit->append(QString::fromLocal8Bit(cmdout));
        /*
        mutex.lock();
        exitProc(QString::fromLocal8Bit(cmdout));
        mutex.unlock();
        */
    }
    QTextCursor cursor=ui->logTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logTextEdit->setTextCursor(cursor);
}
//运行环境变量设置
void vekExtendDebug::executeArgsEnv(BaseGameData data){
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
void vekExtendDebug::ExtendGame(BaseGameData _dataGame){
    if(m_cmd!=nullptr){
        delete m_cmd;
        m_cmd=nullptr;
    }
    m_cmd=new QProcess();
    _data=_dataGame;
    executeArgsEnv(_dataGame);
    /*下面代码用于调试winedbg
   m_cmd->setProcessChannelMode(QProcess::MergedChannels);
   m_cmd->setReadChannel(QProcess::StandardOutput);
   m_cmd->setWorkingDirectory(_dataGame.workPath);
   m_cmd->start("bash");
   m_cmd->setWorkingDirectory(_dataGame.workPath);  
   connect(m_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(onReadyRead()));
   QString dockPath =_dataGame.dockPath+"/"+_dataGame.dockName;
   QString pCodes="WINEPREFIX="+dockPath+" "+_dataGame.winePath+"wine/bin/winedbg"+" "+"--command \'info proc\'";
   m_cmd->write(pCodes.toLocal8Bit()+'\n');
   qDebug()<<pCodes;
   */
    QStringList codeArgs;
    QString gameExe=_dataGame.gameExe;
    if(gameExe.contains(" ",Qt::CaseSensitive)){
        gameExe="\""+gameExe+"\"";
    }
    codeArgs.append(gameExe);
    if(_dataGame.taskMemorySharing){
        codeArgs.append("STAGING_SHARED_MEMORY=1");
    }
    if(_dataGame.taskRealTimePriority){
        codeArgs.append("STAGING_RT_PRIORITY_SERVER=60");
    }
    if(_dataGame.taskMemoryOptimization){
        codeArgs.append("STAGING_WRITECOPY=1");
    }
    if(_dataGame.taskLog){
        codeArgs.append("WINEDEBUG=-all");
    }
    if(_dataGame.gameOtherAgrs!=nullptr){
        codeArgs.append(_dataGame.gameOtherAgrs);
    }
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->setWorkingDirectory(_dataGame.workPath);
    m_cmd->start("bash");
    connect(m_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(onReadyRead()));
    QString codes=_dataGame.winePath+"wine/bin/wine64"+" "+codeArgs.join(" ");
    m_cmd->write(codes.toLocal8Bit()+'\n');

    qDebug()<<"|++++++++++++++++++++++++++++|";
    qDebug()<<"writeCode:"+codes;
    qDebug()<<"workPath:"+_dataGame.workPath;
    qDebug()<<"WineArgs:"+codeArgs.join(" ");
    qDebug()<<"|++++++++++++++++++++++++++++|";
}
