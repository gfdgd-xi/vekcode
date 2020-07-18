#include "objectProcManage.h"

objectProcManage::objectProcManage(QObject *parent) : QThread(parent)
{

}
objectProcManage::~objectProcManage(){

}
QString objectProcManage::objGetProcList(procInfo pInfo){
    m_cmd=new QProcess();
    //设置通道模式error和out合并
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->start("bash");
    QString pCodes="WINEPREFIX="+pInfo.dockPath+"/"+pInfo.dockName+" "+pInfo.winePath+"wine/bin/winedbg"+" "+"--command \"info proc\"";
    m_cmd->write(pCodes.toLocal8Bit()+'\n');
    m_cmd->waitForFinished(10);
    QString procData=m_cmd->readAll();
    qDebug()<<procData;
    m_cmd->close();
    m_cmd->kill();
    delete m_cmd;
    m_cmd=nullptr;
    return procData;
}
void objectProcManage::objDelProc(QProcess* prc,QString prPid,procInfo _pInfo){
    prc->setProcessChannelMode(QProcess::MergedChannels);
    prc->setReadChannel(QProcess::StandardOutput);
    prc->start("bash");
    //设置工作目录
    QString pCodes="WINEPREFIX="+_pInfo.dockPath+"/"+_pInfo.dockName+" "+_pInfo.winePath+"wine/bin/winedbg";
    QString dCodes="attach "+prPid;
    QString kCodes="kill";
    QString qCodes="quit";
    //进入当前容器的winedbg
    prc->write(pCodes.toLocal8Bit()+'\n');
    //通过pid选择进程
    prc->write(dCodes.toLocal8Bit()+'\n');
    //写入关闭指令
    prc->write(kCodes.toLocal8Bit()+'\n');
    //退出winedbg
    prc->write(qCodes.toLocal8Bit()+'\n');
    //关闭并kill QProcess;
    prc->waitForFinished(10);
    prc->close();
    prc->kill();
    delete prc;
    prc=nullptr;
}
void objectProcManage::delAttachProc(procInfo pInfo){
    for(auto b:procAllInfoStr){
        for(auto c:pInfo.attachProc){
            if(b.second.contains(c,Qt::CaseSensitive)){
                QStringList list;
                list.clear();
                list= b.second.split("\n");
                QString kPid;
                qDebug()<<kPid;
                for(auto e:list){
                    if(e.contains(c,Qt::CaseSensitive)){
                        bool ok;
                        kPid=QString::number(e.left(10).toLongLong(&ok,16));
                    }
                }
                if(kPid!=NULL){
                    prc=new QProcess();
                    objDelProc(prc,kPid,pInfo);
                }
            }
        }
    }
}
void objectProcManage::getAllProc(){
    procAllInfoStr.clear();
    procAllInfoStr.insert(pair<QString,QString>(iprocInfo.dockName,objGetProcList(iprocInfo)));
    delAttachProc(iprocInfo);
}
void objectProcManage::run(){
    qDebug()<<"删除进程";
    getAllProc();
}
