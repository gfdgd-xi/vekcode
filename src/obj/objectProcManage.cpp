#include "objectProcManage.h"

objectProcManage::objectProcManage(QObject *parent) : QThread(parent)
{

}
objectProcManage::~objectProcManage(){

}
QString objectProcManage::objGetProcList(SappProcData pInfo){
    m_cmd=new QProcess();
    //设置通道模式error和out合并
    m_cmd->setProcessChannelMode(QProcess::MergedChannels);
    m_cmd->setReadChannel(QProcess::StandardOutput);
    m_cmd->start("bash",QIODevice::ReadWrite);
    QString pCodes="WINEPREFIX="+pInfo.s_proc_docker_path+"/"+pInfo.s_proc_docker_name+" "+pInfo.s_proc_wine_path+"/wine/bin/wine winedbg"+" "+"--command \"info proc\"";
    m_cmd->write(pCodes.toLocal8Bit()+'\n');
    m_cmd->waitForFinished(500);
    QString procData=m_cmd->readAll();
    qInfo()<<procData;
    m_cmd->write("\x03");
    if(m_cmd){
        m_cmd->close();
        m_cmd->kill();
        delete m_cmd;
        m_cmd=nullptr;
    }
    return procData;
}
void objectProcManage::objDelProc(QString prPid,SappProcData _pInfo){
    prc=new QProcess();
    prc->setProcessChannelMode(QProcess::MergedChannels);
    prc->setReadChannel(QProcess::StandardOutput);
    prc->start("bash",QIODevice::ReadWrite);
    //设置工作目录
    QString aCodes="WINEPREFIX="+_pInfo.s_proc_docker_path+"/"+_pInfo.s_proc_docker_name+" "+_pInfo.s_proc_wine_path+"/wine/bin/winedbg";
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
    prc->write("\x03");
    if(prc){
        prc->close();
        prc->kill();
        delete prc;
        prc=nullptr;
    }
}
void objectProcManage::delAttachProc(SappProcData pInfo){
    for(auto b:procAllInfoStr){
        for(auto c:pInfo.vec_proc_attach_list){
            if(b.second.contains(c,Qt::CaseSensitive)){
                QStringList list;
                list.clear();
                list= b.second.split("\n");
                QString kPid;
                qInfo()<<kPid;
                for(auto e:list){
                    if(e.contains(c,Qt::CaseSensitive)){
                        bool ok;
                        kPid=QString::number(e.left(10).toLongLong(&ok,16));
                    }
                }
                if(kPid!=NULL){
                    objDelProc(kPid,pInfo);
                }
            }
        }
    }
}
void objectProcManage::getAllProc(){
    procAllInfoStr.clear();
    procAllInfoStr.insert(pair<QString,QString>(iprocInfo.s_proc_docker_name,objGetProcList(iprocInfo)));
    delAttachProc(iprocInfo);
}
void objectProcManage::run(){
    getAllProc();
}
