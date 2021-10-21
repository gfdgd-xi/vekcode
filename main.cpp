#include "src/vek.h"
#include "src/obj/baseRes.h"
#include "src/obj/objectSource.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    objectSource* objSource=new objectSource;
    objSource->loadAllData();
    delete objSource;
    objSource=nullptr;
    vek vekMainWindows;
    vekMainWindows.show();
    vekMainWindows.connectObject();
    vekMainWindows.on_action_About_triggered();
    vekMainWindows.vekThis=&a;
    objectVersionData OBJ_VER;
    OBJ_VER.repair_Wineprc_Stalonetray_Winetricks();
    /*自动更新代码,非推送版本不可取消注释
    /*
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

