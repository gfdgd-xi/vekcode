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
bool objectVersionData::upDataVek(){
    bool upStatic=false;
    if(getVersionStr()){
        if(pObject::vekMesg("发现新版本,是否执行更新!")){
            QString strPrefix = ":/res/vup/vUpdate";
            if(QFile(QApplication::applicationDirPath()+"/vUpdate").exists()){
                QFile(QApplication::applicationDirPath()+"/vUpdate").remove();
            }
            QFile::copy(strPrefix,QApplication::applicationDirPath()+"/vUpdate");
            QFile::setPermissions(QApplication::applicationDirPath()+"/vUpdate",
                                  QFile::ReadOther|
                                  QFile::WriteOther|
                                  QFile::ReadOwner|
                                  QFile::WriteOwner|
                                  QFile::ReadGroup|
                                  QFile::ExeOther|
                                  QFile::ExeUser|
                                  QFile::ExeGroup);
            upStatic=true;
        }
    }
    return upStatic;
}
