#include "src/vek.h"
#include "src/baseRes.h"
#include "src/objectSource.h"
#include "src/vekGetCurl.h"
#include "src/vekInitObject.h"
typedef struct{
    QString version;
    QString urlLogsStr;
    QString urlFileStr;
}verInfo;
verInfo verData;
void unVerData(string vData){
    json jx=json::parse(vData);
    for(auto x:jx.items()){
        if(x.key()=="version"){
            verData.version=QString::fromStdString(x.value());
        }
        if(x.key()=="uFileStr"){
            verData.urlFileStr=QString::fromStdString(x.value());
        }
        if(x.key()=="uLogsStr"){
            verData.urlLogsStr=QString::fromStdString(x.value());
        }
    }
}
bool getVinfo(){
    bool vState=false;
    vekGetCurl* _vekgetcurl=new vekGetCurl;
    string verInfoStr=_vekgetcurl->vekGetData(vekUpInfo.toStdString());
    if(verInfoStr!="error"){
        unVerData(verInfoStr);
        if(verData.version!=APP_VERSION){
            vState=true;
        }
    }
    return vState;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(getVinfo()){
        if(vekMesg("发现新版本,是否执行更新!")){
            QString strPrefix = ":/res/vup/vUpdate";
            if(QFile(QDir::currentPath()+"/vUpdate").exists()){
                QFile(QDir::currentPath()+"/vUpdate").remove();
            }
            QFile::copy(strPrefix,QDir::currentPath()+"/vUpdate");
            QFile::setPermissions(QDir::currentPath()+"/vUpdate",
                                  QFile::ReadOther|
                                  QFile::WriteOther|
                                  QFile::ReadOwner|
                                  QFile::WriteOwner|
                                  QFile::ReadGroup|
                                  QFile::ExeOther|
                                  QFile::ExeUser|
                                  QFile::ExeGroup);
            QProcess* m_cmd=new QProcess();
            m_cmd->startDetached(QDir::currentPath()+"/vUpdate "+verData.version+" "+verData.urlLogsStr+" "+verData.urlFileStr);
            m_cmd->kill();
            a.exit();
            return 0;
        }
    }
    objectSource* objSource=new objectSource;   
    objSource->loadAllData();
    delete objSource;
    objSource=nullptr;
    vek w;
    w.show();
    w.connectObject();
    w.on_action_About_triggered();
    return a.exec();
}

