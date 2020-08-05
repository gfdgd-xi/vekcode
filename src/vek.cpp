#include "vek.h"
#include "ui_common.h"
vek::vek(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vek)

{
    ui->setupUi(this);
    vek_Style(this,0);  
    qwidgetGeometry(this);
    QString vStr="Vek-";
    vStr.append(APP_VERSION);
    this->setWindowTitle(vStr);
}
vek::~vek()
{
    exitTray(true);
    delete ui;
}
void vek::connectObject(){
    connect(ui->pushButton_vekAddApp,&QPushButton::clicked,this,&vek::vekAddApp);
    connect(ui->pushButton_vekRunApp,&QPushButton::clicked,this,&vek::vekRunApp);
    connect(ui->pushButton_InstallApp,&QPushButton::clicked,this,&vek::installApp);
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
        if(objTray!=nullptr){
           objTray->exitTray();
        }
    }else{
        if(taskList.empty()){
        objTray->exitTray();
        }else{return;}
    }
    if(objTray==nullptr){
        return;
    }
    delete objTray;
    objTray=nullptr;
}
void vek::installApp(){
    ui->tabWidget->objAppInstall();
}
void vek::on_action_EditSource_triggered(){
    if(_vek_source_esit==nullptr){
        _vek_source_esit=new vekSourceEdit();
        _vek_source_esit->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_source_esit->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_source_esit->setGeometry(this->geometry());
        _vek_source_esit->show();
        connect(_vek_source_esit,&vekSourceEdit::_unSourveEdit,this,&vek::unSourceEdit);
    }
}
void vek::vekAddApp()
{   
     ui->tabWidget->addAppSlot();
}
void vek::vekRunApp()
{
    ui->tabWidget->objectRunApp();
}
void vek::on_action_AddApp_triggered()
{
    ui->tabWidget->addAppSlot();
}

void vek::on_action_About_triggered()
{
    if(_vek_About==nullptr){
        _vek_About=new vekAbout();
        _vek_About->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_About->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_About->setGeometry(this->geometry());
        _vek_About->show();
        _vek_About->getUpdateLogs();
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
