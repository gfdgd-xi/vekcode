#include "src/vek.h"
#include "src/obj/baseRes.h"
#include "src/obj/objectSource.h"
#include "src/obj/objectJson.h"

QString mainSrc="https://bitbucket.org/jacklee_CN/vekserver/raw/9d1749e1ded4e2b687f0c014a36f4ae335faa4dd/mainSrcUrl.json";
bool getGSrcUrl(){
    QString f_config=QDir::currentPath()+"/MainSrcUrl.config";
    QFile f_file(f_config);
    if(f_file.exists()){
        std::fstream in(f_config.toStdString(),std::fstream::in);
        if(!in.is_open()){
            qDebug()<<"Can't open the file!";
        }else{
            std::string str;
            while(std::getline(in,str)){
                mainSrc=QString::fromStdString(str);
                break;
            }
        }
        in.close();
    }else{
        std::ofstream out(f_config.toStdString(),std::ios::binary);
        out<<mainSrc.toStdString();
        out.close();
    }
    objectGetCurl* objSource=new objectGetCurl;
    std::string data=objSource->vekGetData(mainSrc.toStdString());
    if(data!="error"&&!data.empty()){
       objectJson* oj=new objectJson;
       if(oj->unSrcData(data)){
           objectSource* objSource=new objectSource;
           objSource->loadAllData();
           delete objSource;
           objSource=nullptr;
       }
       delete oj;
       oj=nullptr;
       return true;
    }else{
       return false;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!getGSrcUrl()){
        pObject::vekTip("主服务器无法连接!");
        return 0;
    }
    vek vekMainWindows;
    vekMainWindows.show();
    vekMainWindows.connectObject();
    vekMainWindows.on_action_About_triggered();
    vekMainWindows.vekThis=&a;
    objectVersionData OBJ_VER;
    OBJ_VER.repair_Wineprc_Stalonetray_Winetricks();
    /*自动更新代码,非推送版本不可取消注释
    if(OBJ_VER.upDataVek()){
        QProcess* m_cmd=new QProcess();
        m_cmd->setWorkingDirectory(QApplication::applicationDirPath());
        m_cmd->startDetached(QApplication::applicationDirPath()+"/vUpdate "+OBJ_VER.sVersion+" "+OBJ_VER.sUrlFile+" "+OBJ_VER.sUrlLogs+" "+OBJ_VER.sUrlFilePassword+" "+OBJ_VER.sFileSHA512);
        m_cmd->kill();
        a.exit();
        return 0;
    }
    */
    return a.exec();
}

