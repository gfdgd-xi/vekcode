#include "vek.h"
#include "ui_common.h"
#include <QDesktopServices>
#include <QUrl>
vek::vek(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vek)

{
    ui->setupUi(this);
    vek_Style(this,0);
    connect(ui->pushButton_vekAddGame,&QPushButton::clicked,this,&vek::vekAddGame);
    connect(ui->pushButton_vekRunGame,&QPushButton::clicked,this,&vek::vekRunGame);
    connect(ui->pushButton_InstallApp,&QPushButton::clicked,this,&vek::installApp);
}
vek::~vek()
{
    exitTray(true);
    delete ui;
}
void vek::startTray(){
    if(!g_vekLocalData.wineVec.empty()){
        for(auto a:g_vekLocalData.wineVec){
            if(objTray==nullptr){
                objTray=new objectTray();
                objTray->_baseWineData=a.second;
                objTray->start();
            }
            break;
        }
    }
}
void vek::exitTray(bool trayState){
    if(trayState){
        objTray->exitTray();
    }else{
        if(taskList.empty()){
        objTray->exitTray();
        }else{
            return;
        }
    }
    delete objTray;
    objTray=nullptr;
}
void vek::installApp(){
    bool dState=false;
    if(g_vekLocalData.wineVec.empty()){
        vekTip("未发现您的电脑上装有wine请安装wine后重试");
        return;
    }
    if(g_vekLocalData.dockerVec.empty()){
        dState=vekMesg("您的电脑上未发现容器无法安装软件,是否初始化一个容器用于软件安装");
    }
    BaseGameData basegamedata;
    objectAddGameMT* objNewDock=new objectAddGameMT(&basegamedata,nullptr);
    if(dState){
        QString dockName="vekON1";//自动以CID为名创建
        basegamedata.winePath=g_vekLocalData.wineVec.begin()->second.wineInstallPath;
        basegamedata.dockPath=QDir::currentPath()+"/vekDock";
        basegamedata.dockName=dockName;
        basegamedata.monoState=true;
        basegamedata.geckoState=true;
        basegamedata.defaultFonts=true;
        objNewDock->newDock();
    }else{       
        if(g_vekLocalData.dockerVec.empty()){
            return;
        }else{
            qDebug()<<g_vekLocalData.dockerVec.begin()->first;
            basegamedata=g_vekLocalData.dockerVec.begin()->second.begin()->second;
        }
    }
    objectExtend* _objectExtend=new objectExtend();
    objectType _objType=object_uninstall;
    std::vector<QStringList> _codeAgrs;
    connect(this, SIGNAL(toObjectArgs(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)), _objectExtend, SLOT(setDockOptionObjectData(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)));
    emit(toObjectArgs(basegamedata,_codeAgrs,_objType,objectWineBoot::object_wineboot_default,objectWineServer::object_wineserver_default));
    _objectExtend->start();
    delete objNewDock;
    objNewDock=nullptr;
}
void vek::on_action_EditSource_triggered(){
    if(_vek_source_esit==nullptr){
        _vek_source_esit=new vekSourceEdit();
        _vek_source_esit->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_source_esit->setGeometry(this->geometry());
        _vek_source_esit->show();
        connect(_vek_source_esit,&vekSourceEdit::_unSourveEdit,this,&vek::unSourceEdit);
    }
}
void vek::vekAddGame()
{   
     ui->tabWidget->addGameSlot();
}
void vek::vekRunGame()
{
    ui->tabWidget->objectRunGame();
}
void vek::on_action_AddGame_triggered()
{
    ui->tabWidget->addGameSlot();
}

void vek::on_action_About_triggered()
{
    if(_vek_About==nullptr){
        _vek_About=new vekAbout();
        _vek_About->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_About->setGeometry(this->geometry());
        _vek_About->show();
        connect(_vek_About,&vekAbout::_unVekAbout,this,&vek::unVekAbout);
    }
}
void vek::on_action_Exit_triggered()
{
    this->close();
}

void vek::on_action_WineInstall_triggered()
{
    if(_vek_wine_option==nullptr){
        _vek_wine_option=new vekWineOption();
        _vek_wine_option->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_wine_option->setGeometry(this->geometry());
        _vek_wine_option->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_wine_option->show();
        connect(_vek_wine_option,&vekWineOption::_unInitWineOption,this,&vek::unInitWineOption);
    }
}
void vek::unInitWineOption(){
    _vek_wine_option=nullptr;
}
void vek::unVekAbout(){
    _vek_About=nullptr;
};
void vek::unSourceEdit(){
    _vek_source_esit=nullptr;
}
