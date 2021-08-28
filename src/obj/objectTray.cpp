#include "objectTray.h"
#include <QDebug>
objectTray::objectTray(QObject *parent) : QThread(parent)
{

}
objectTray::~objectTray(){

}
void objectTray::StartTray(){
    m_cmd->closeReadChannel(QProcess::StandardOutput);
    m_cmd->closeReadChannel(QProcess::StandardError);
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setWorkingDirectory(QApplication::applicationDirPath()+"/vekScript");
    m_cmd->start(QApplication::applicationDirPath()+"/vekScript/stalonetray");
    //m_cmd->waitForFinished(-1);
    while(!procManages.empty()){
        sleep(1);
    }
    ExitTray();
}
void objectTray::ExitTray(){
    if(procManages.empty()){
        if(m_cmd){
            m_cmd->write("\x03");
            m_cmd->close();
            m_cmd->kill();
            delete m_cmd;
            m_cmd=nullptr;
        }
    }
}
void objectTray::run(){
    if(m_cmd){
        delete m_cmd;
        m_cmd=nullptr;
    }
    m_cmd=new QProcess();
    StartTray();
}
