#include "objectVersionData.h"

objectVersionData::objectVersionData()
{

}
objectVersionData::~objectVersionData()
{

}
bool objectVersionData::unVersionData(string vData){
    try {
        json jx=json::parse(vData);
        for(auto x:jx.items()){
            if(x.key()=="version"){
                sVersion=QString::fromStdString(x.value());
            }
            if(x.key()=="uFileStr"){
                sUrlLogs=QString::fromStdString(x.value());
            }
            if(x.key()=="uLogsStr"){
                sUrlFile=QString::fromStdString(x.value());
            }
            if(x.key()=="urlFilePassword"){
                sUrlFilePassword=QString::fromStdString(x.value());
            }
            if(x.key()=="uFileSHA512"){
                sFileSHA512=QString::fromStdString(x.value());
            }
        }
        return true;
    } catch (...) {
        return false;
    }

}
bool objectVersionData::getVersionStr(){
    bool vState=false;
    objectGetCurl* _vekgetcurl=new objectGetCurl;
    string verInfoStr=_vekgetcurl->vekGetData(vekUpInfo.toStdString());
    if(verInfoStr!="error"){
        if(!unVersionData(verInfoStr)){
            return vState;
        }else if(sVersion!=APP_VERSION){
            vState=true;
        }
    }
    return vState;
}
void objectVersionData::repairFilePerm(QString file){
    QFile::setPermissions(file,
                          QFile::ReadOther|
                          QFile::WriteOther|
                          QFile::ReadOwner|
                          QFile::WriteOwner|
                          QFile::ReadGroup|
                          QFile::ExeOther|
                          QFile::ExeUser|
                          QFile::ExeGroup);
}
void objectVersionData::copyFile(QString strFileName){
    QString fileDir=QApplication::applicationDirPath()+"/vekScript/";
    QString filePath=QApplication::applicationDirPath()+"/vekScript/"+strFileName;
    QString strPrefix = ":/res/script/"+strFileName;
    /*
    if(QFile(filePath).exists()){
        QFile(filePath).remove();
    }
    */
    if(!QDir(fileDir).exists()){
        QDir().mkdir(fileDir);
    }
    QFile::copy(strPrefix,filePath);
}
void objectVersionData::repair_Wineprc_Stalonetray_Winetricks(){
    repair_Stalonetray();
    repair_Wineprc();
    repair_Winetricks();
}
void objectVersionData::repair_Stalonetray(){
    QString strName;
    strName=pFileName[1];
    copyFile(strName);
    repairFilePerm(QApplication::applicationDirPath()+"/vekScript/"+strName);
}
void objectVersionData::repair_Wineprc(){
    QString strName;
    strName=pFileName[0];
    copyFile(strName);
    copyFile(strName);
    repairFilePerm(QApplication::applicationDirPath()+"/vekScript/"+strName);
}
void objectVersionData::repair_Winetricks(){
    QString strName;
    strName=pFileName[2];
    copyFile(strName);
    repairFilePerm(QApplication::applicationDirPath()+"/vekScript/"+strName);
}

bool objectVersionData::upDataVek(){
    bool upStatic=false;
    if(getVersionStr()){
        if(pObject::vekMesg("发现新版本,是否执行更新!")){
            QString strPrefix = ":/res/vup/vUpdate";
            if(QFile(QApplication::applicationDirPath()+"/vUpdate").exists()){
                QFile(QApplication::applicationDirPath()+"/vUpdate").remove();
            }
            QFile::copy(strPrefix,QApplication::applicationDirPath()+"/vUpdate");
            repairFilePerm(QApplication::applicationDirPath()+"/vUpdate");
            upStatic=true;
        }
    }
    return upStatic;
}
