#include "objectTray.h"

objectTray::objectTray(QObject *parent) : QThread(parent)
{
    parent=nullptr;
}
objectTray::~objectTray(){
    delete m_cmd;
    m_cmd=nullptr;
}
void objectTray::startTray(){
    m_cmd->closeReadChannel(QProcess::StandardOutput);
    m_cmd->closeReadChannel(QProcess::StandardError);
    m_cmd->setWorkingDirectory(_baseWineData.wineInstallPath+"wine/bin");
    m_cmd->start(_baseWineData.wineInstallPath+"wine/bin/stalonetray");
}
void objectTray::exitTray(){
   m_cmd->start();
   m_cmd->write("\x03");
   m_cmd->close();
   m_cmd->kill();
}
void objectTray::run(){
    m_cmd=new QProcess();
    startTray();
}
