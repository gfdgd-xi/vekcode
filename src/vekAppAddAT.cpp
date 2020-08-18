#include "vekAppAddAT.h"
#include "ui_common.h"
#include <QListWidget>
vekAppAddAT::vekAppAddAT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekAppAddAT)
{
    ui->setupUi(this);
    vek_Style(this,0);
    qwidgetGeometry(this);
}

vekAppAddAT::~vekAppAddAT()
{
    delete ui;
    emit _unAutoDock();
}
void vekAppAddAT::connectDockObject(){
    connect(ui->pushButton_DockDone,&QPushButton::clicked,this,&vekAppAddAT::addAutoApp);
    connect(ui->pushButton_AutoJson,&QPushButton::clicked,this,&vekAppAddAT::SetObject);
    connect(ui->pushButton_AutoDockPath,&QPushButton::clicked,this,&vekAppAddAT::SetObject);
    connect(ui->pushButton_SetExePath,&QPushButton::clicked,this,&vekAppAddAT::SetObject);
    if(!g_vekLocalData.wineVec.empty())
    {
        for(auto & x :g_vekLocalData.wineVec)
        {
            ui->comboBox_WinVersion->addItem(x.first);
        }
    }else{
        vekTip("请先安装Wine");
        this->close();
    }

    for(auto & d:g_vekLocalData.appScrSource){
        ui->comboBox_SrcApp->addItem(d.first);
    }

    for(auto & v:g_vekLocalData.appJsonList){
        if(v.first==ui->comboBox_SrcApp->currentText()){
            for(auto & y:v.second){
                ui->comboBox_JsonUrl->addItem(y.first);
            }
            break;
        }
    }

    QStringList _tempDockName;
    if(!g_vekLocalData.dockerVec.empty()){
        for(auto &a:g_vekLocalData.dockerVec){
            _tempDockName.append(a.first);
        }
        _tempDockName = _tempDockName.toSet().toList();
        for(auto a:_tempDockName){
            ui->comboBox_DockName->addItem(a);
        }
    }else{
        ui->comboBox_DockName->setCurrentText("vekON1");
    }
    ui->lineEdit_DockPath->setText(QDir::currentPath()+"/vekDock");
}
void vekAppAddAT::SetObject(){
    QObject *object = QObject::sender();
    QPushButton *action_obnject = qobject_cast<QPushButton *>(object);
    QWidget *qwidget = new QWidget();
    if(action_obnject->objectName()=="pushButton_AutoJson"){
        QString strPath=QFileDialog::getOpenFileName(qwidget,"选择JSON脚本","","Json Files(*.json)");
        if(strPath!=NULL){
            ui->comboBox_JsonUrl->setCurrentText(strPath);
        }
    }
    if(action_obnject->objectName()=="pushButton_AutoDockPath"){
        QString dockPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(dockPath!=NULL){
            ui->lineEdit_DockPath->setText(dockPath);
        }
    }
    if(action_obnject->objectName()=="pushButton_SetExePath"){
        QString strPath=QFileDialog::getOpenFileName(qwidget,"选择游戏EXE执行文件","","EXE Files(*.exe)");
        if(strPath!=NULL){
            QFileInfo fi = QFileInfo(strPath);
            ui->lineEdit_AppExePath->setText(strPath);
        }
    }

}
void vekAppAddAT::addAutoApp(){
    if(ui->comboBox_JsonUrl->currentText()==nullptr){
        vekTip("请设置Json文件");
        return;
    }
    if(ui->comboBox_DockName->currentText()==nullptr){
        vekTip("请为容器命名");
        return;
    }
    if(ui->lineEdit_DockPath->text()==nullptr){
        vekTip("请指定容器保存路径");
        return;
    }
    if(ui->comboBox_WinVersion->currentText()==nullptr){
        vekTip("请安装wine!");
        this->close();
        return;
    }
    if(ui->lineEdit_AppExePath->text()==nullptr){
        vekTip("请设置游戏运行exe文件路径");
        return;
    }
    bool dataState=false;
    for(auto a:g_vekLocalData.dockerVec){
        if(a.first==ui->comboBox_WinVersion->currentText()){
            dataState=true;
            *autoDockData=a.second;
            break;
        }
    }
    if(!dataState){
        autoDockData->DockerName=ui->comboBox_DockName->currentText();
        autoDockData->DockerPath=ui->lineEdit_DockPath->text();
        autoDockData->WineVersion=ui->comboBox_WinVersion->currentText();
    }
    QString pJsonPath=ui->comboBox_JsonUrl->currentText();
    autoAppData->AppExe=ui->lineEdit_AppExePath->text();
    objectAppAT* objAutoAddApp=new objectAppAT();
    objAutoAddApp->connectDockAutoData(*autoDockData,*autoAppData,pJsonPath);
    connect(objAutoAddApp,SIGNAL(Tips(QString)),this,SLOT(TipText(QString)));
    connect(objAutoAddApp,SIGNAL(Error(QString,bool)),this,SLOT(ErrorText(QString,bool)));
    connect(objAutoAddApp,SIGNAL(Done()),this,SLOT(ObjDone()));
    objAutoAddApp->start();
    controlState(false);
}
void vekAppAddAT::controlState(bool pState){
    ui->comboBox_SrcApp->setEnabled(pState);
    ui->comboBox_JsonUrl->setEnabled(pState);
    ui->pushButton_AutoJson->setEnabled(pState);
    ui->comboBox_WinVersion->setEnabled(pState);
    ui->lineEdit_DockPath->setEnabled(pState);
    ui->pushButton_AutoDockPath->setEnabled(pState);
    ui->comboBox_DockName->setEnabled(pState);
    ui->lineEdit_AppExePath->setEnabled(pState);
    ui->pushButton_SetExePath->setEnabled(pState);
    ui->pushButton_DockDone->setEnabled(pState);
}
void vekAppAddAT::TipText(QString TipInfo)
{
    ui->label_ProgText->setText(TipInfo);
}
void vekAppAddAT::ErrorText(QString ErrorInfo,bool cState){
    ui->label_ProgText->setText(ErrorInfo);
    controlState(cState);
}
void vekAppAddAT::ObjDone(){
    emit autoObjDock(autoDockData,autoAppData);
    this->close();
}
