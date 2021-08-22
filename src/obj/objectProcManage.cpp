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
    m_cmd->waitForFinished(300);
    QString procData=m_cmd->readAll();
    qInfo()<<procData;
    m_cmd->write("\x03");
    m_cmd->close();
    m_cmd->kill();
    delete m_cmd;
    m_cmd=nullptr;
    return procData;
}
void objectProcManage::objWineHQKillProc(QString prPid,SappProcData _pInfo){
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
    prc->waitForFinished(500);
    prc->close();
    prc->kill();
    delete prc;
    prc=nullptr;
}
//deepin-wine5进程附加结束
//原理,用QProcess故意拉起一个winedbg进程附加到要结束的进程里面
//然后通过killall强制结束winedbg进程对附加进程进行关闭从而做到后台遗留进程清理
void objectProcManage::objDeepinKillProc(QString prPid,SappProcData _pInfo){
    QProcess* deepinProc=new QProcess();
    deepinProc->setProcessChannelMode(QProcess::MergedChannels);
    deepinProc->setReadChannel(QProcess::StandardOutput);
    deepinProc->start("bash",QIODevice::ReadWrite);
    QString aCodes="WINEPREFIX="+_pInfo.s_proc_docker_path+"/"+_pInfo.s_proc_docker_name+" "+_pInfo.s_proc_wine_path+"/wine/bin/winedbg";
    QString bCodes="attach "+prPid;
    deepinProc->write(aCodes.toLocal8Bit()+'\n');
    deepinProc->write(bCodes.toLocal8Bit()+'\n');
    deepinProc->waitForFinished(300);
    system("killall -I winedbg.exe");
    delete deepinProc;
    deepinProc=nullptr;
}
void objectProcManage::delAttachProc(SappProcData pInfo){
    for(auto b:procAllInfoStr){
        for(auto c:pInfo.vec_proc_attach_list){
            if(b.second.contains(c,Qt::CaseSensitive)){
                QStringList list;
                list.clear();
                list= b.second.split("\n");
                QString kPid;
                for(auto e:list){
                    if(e.contains(c,Qt::CaseSensitive)){
                        //bool ok;
                        qInfo()<<"输出当前行地址:"<<e;
                        kPid="0x"+e.mid(1, 8);
                        qInfo()<<"输出当前进程的PID:"<<kPid;
                        if(pInfo.s_proc_docker_path.contains("deepin",Qt::CaseSensitive)){
                           objDeepinKillProc(kPid,pInfo);
                        }else{
                           objWineHQKillProc(kPid,pInfo);
                        }
                        //kPid=QString::number(e.left(10).toLongLong(&ok,16));
                    }
                }
            }
        }
    }
}
bool objectProcManage::objMainProcExists(){
    QString strProc=objGetProcList(iprocInfo);
    if(strProc.contains(iprocInfo.s_proc_main_name,Qt::CaseSensitive)){
        return true;
    }
    return false;
}
void objectProcManage::getAllProc(){
    procAllInfoStr.clear();
    procAllInfoStr.insert(pair<QString,QString>(iprocInfo.s_proc_docker_name,objGetProcList(iprocInfo)));
    delAttachProc(iprocInfo);
}
void objectProcManage::run(){
    getAllProc();
    system("killall -I winedbg.exe");
}
