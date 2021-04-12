#include "objectPackage.h"

objectPackage::objectPackage(SdockerData _d_date,Spackage _p_data,QString _is_pwd)
{
    d_data=_d_date;
    p_data=_p_data;
    _password=_is_pwd;
    d_path=d_data.s_dockers_path+"/"+d_data.s_dockers_name;
    p_package_tool_path=d_data.s_dockers_wine_path+"/deepin-wine-tools";
}
objectPackage::~objectPackage()
{

}

void objectPackage::EXToolDeb(){
    if(v_package){
        v_package->close();
        delete v_package;
        v_package=nullptr;
    }
    v_package=new QProcess();
    v_package->setProcessChannelMode(QProcess::MergedChannels);
    v_package->setReadChannel(QProcess::StandardOutput);
    connect(v_package,SIGNAL(readyRead()),this,SLOT(ontRead()));
    QString dpkgArgs="echo "+_password+" | sudo -S dpkg -i "+p_package_tool_path+"/*.deb";
    QString aptArgs="echo "+_password+" | sudo -S apt install -f -y";
    QString chmodArgs="echo "+_password+" | sudo -S chmod +x -R "+p_package_tool_path+"/wine-package-script/*";
    v_package->start("bash");
    v_package->write(dpkgArgs.toLocal8Bit()+'\n');
    v_package->write(aptArgs.toLocal8Bit()+'\n');
    v_package->write(dpkgArgs.toLocal8Bit()+'\n');
    v_package->write(chmodArgs.toLocal8Bit()+'\n');

}

void objectPackage::ontRead(){
    QByteArray readout = v_package->readAll();
    emit outQStr(QString::fromLocal8Bit(readout));
}
void objectPackage::EXPackage(){
    if(v_package){
        v_package->close();
        delete v_package;
        v_package=nullptr;
    }
    v_package=new QProcess();
    v_package->setProcessChannelMode(QProcess::MergedChannels);
    v_package->setReadChannel(QProcess::StandardOutput);
    connect(v_package,SIGNAL(readyRead()),this,SLOT(ontRead()));
    v_package->setWorkingDirectory(p_package_tool_path+"/wine-package-script");
    if(p_data.sDesrc.contains(" ",Qt::CaseSensitive)){
        p_data.sDesrc="\""+p_data.sDesrc+"\"";
    }
    QString command = p_package_tool_path+"/wine-package-script/package-vek.sh";
    QStringList args;
    args.append("--d="+p_data.sDesrc);
    args.append("--a="+p_data.sAppNameEN);
    args.append("--c="+p_data.sAppNameCN);
    args.append("--p="+p_data.sDockerName);
    args.append("--dfc="+p_data.sAppType);
    args.append("--dfi="+p_data.sAppIco);
    args.append("--dfme="+p_data.sAppExeName);
    args.append("--ep="+p_data.sAppExePath);
    args.append("--dpn="+p_data.sAppDebName);
    args.append("--edp="+p_data.sAppDebNamePro);
    args.append("--dvs="+p_data.sAppDebVersion);
    args.append("--opn="+p_data.sAppOldDebName);
    qInfo()<<args;
    v_package->start(command,args);
}
