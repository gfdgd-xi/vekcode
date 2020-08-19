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
    QString pCodes="WINEPREFIX="+pInfo.pDockPath+"/"+pInfo.pDockName+" "+pInfo.pWinePath+"/wine/bin/wine winedbg"+" "+"--command \"info proc\"";
    m_cmd->write(pCodes.toLocal8Bit()+'\n');
    m_cmd->waitForFinished(1000);
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
    QString aCodes="WINEPREFIX="+_pInfo.pDockPath+"/"+_pInfo.pDockName+" "+_pInfo.pWinePath+"/wine/bin/winedbg";
    QString bCodes="attach "+prPid;
    QString cCodes="kill";
    QString dCodes="quit";
    //进入当前容器的winedbg
    prc->write(aCodes.toLocal8Bit()+'\n');
    //通过pid选择进程
    prc->write(bCodes.toLocal8Bit()+'\n');
    //写入关闭指令
    prc->write(cCodes.toLocal8Bit()+'\n');
    //退出winedbg
    prc->write(dCodes.toLocal8Bit()+'\n');
    //关闭并kill QProcess;
    prc->waitForFinished(1000);
    prc->close();
    prc->kill();
    delete prc;
    prc=nullptr;
}
void objectProcManage::delAttachProc(procInfo pInfo){
    for(auto b:procAllInfoStr){
        for(auto c:pInfo.pAttachProc){
            if(b.second.contains(c,Qt::CaseSensitive)){
                QStringList list;
                list.empty();
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
                    prc=new QProcess(this);
                    objDelProc(prc,kPid,pInfo);
                }
            }
        }
    }
}
void objectProcManage::getAllProc(){
    procAllInfoStr.empty();
    procAllInfoStr.insert(pair<QString,QString>(iprocInfo.pDockName,objGetProcList(iprocInfo)));
    delAttachProc(iprocInfo);
}
void objectProcManage::run(){
    getAllProc();
}
