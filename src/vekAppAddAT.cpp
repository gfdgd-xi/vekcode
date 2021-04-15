#include "vekAppAddAT.h"
#include "ui_common.h"
#include <QListWidget>
vekAppAddAT::vekAppAddAT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekAppAddAT)
{
    ui->setupUi(this);
    pObject::qwidgetGeometry(this);
}

vekAppAddAT::~vekAppAddAT()
{
    emit _unAutoDock();
}
void vekAppAddAT::connectDockObject(SdockerData _dockeData){
    connect(ui->pushButton_DockDone,&QPushButton::clicked,this,&vekAppAddAT::addAutoApp);
    connect(ui->pushButton_AutoJson,&QPushButton::clicked,this,&vekAppAddAT::SetObject);
    connect(ui->pushButton_AutoDockPath,&QPushButton::clicked,this,&vekAppAddAT::SetObject);
    connect(ui->pushButton_SetExePath,&QPushButton::clicked,this,&vekAppAddAT::SetObject);
    if(g_vekLocalData.map_wine_list.empty())
    {
        pObject::vekTip("请先安装Wine");
        return;
        this->close();
    }else{
        defalutValue();
        ui->comboBox_WinVersion->setCurrentText(_dockeData.s_dockers_wine_version);
        ui->comboBox_DockName->setCurrentText(_dockeData.s_dockers_name);
        ui->lineEdit_DockPath->setText(_dockeData.s_dockers_path);
    }
}
void vekAppAddAT::defalutValue(){
    for(auto & x :g_vekLocalData.map_wine_list)
    {
        ui->comboBox_WinVersion->addItem(x.first);
    }

    for(auto & d:g_vekLocalData.map_app_src_list){
        ui->comboBox_SrcApp->addItem(d.first);
    }
    if(!g_vekLocalData.map_docker_list.empty()){
        for(auto &a:g_vekLocalData.map_docker_list){
            ui->comboBox_DockName->addItem(a.first);
        }
    }else{
        ui->comboBox_DockName->setCurrentText("vekON1");
    }
    ui->lineEdit_DockPath->setText(QApplication::applicationDirPath()+"/vekDock");
}
void vekAppAddAT::SetObject(){
    QObject *object = QObject::sender();
    QPushButton *action_obnject = qobject_cast<QPushButton *>(object);
    QWidget *qwidget = new QWidget();
    if(action_obnject->objectName()=="pushButton_AutoJson"){
        QString strPath=QFileDialog::getOpenFileName(qwidget,"选择JSON脚本","","Json Files(*.json)");
        if(strPath!=nullptr){
            ui->comboBox_JsonUrl->setCurrentText(strPath);
        }
    }
    if(action_obnject->objectName()=="pushButton_AutoDockPath"){
        QString dockPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(dockPath!=nullptr){
            ui->lineEdit_DockPath->setText(dockPath);
        }
    }
    if(action_obnject->objectName()=="pushButton_SetExePath"){
        QString strPath=QFileDialog::getOpenFileName(qwidget,"选择游戏EXE执行文件","","EXE Files(*.exe)");
        if(strPath!=nullptr){
            QFileInfo fi = QFileInfo(strPath);
            ui->lineEdit_AppExePath->setText(strPath);
        }
    }

}
void vekAppAddAT::addAutoApp(){
    if(ui->comboBox_JsonUrl->currentText()==nullptr){
        pObject::vekTip("请设置Json文件");
        return;
    }
    if(ui->comboBox_DockName->currentText()==nullptr){
        pObject::vekTip("请为容器命名");
        return;
    }
    if(ui->lineEdit_DockPath->text()==nullptr){
        pObject::vekTip("请指定容器保存路径");
        return;
    }
    if(ui->comboBox_WinVersion->currentText()==nullptr){
        pObject::vekTip("请安装wine!");
        this->close();
        return;
    }
    if(ui->lineEdit_AppExePath->text()==nullptr){
        pObject::vekTip("请设置游戏运行exe文件路径");
        return;
    }
    SappData* autoAppData=new SappData;
    SdockerData* autoDockData=new SdockerData;
    SdockerData btmp=pObject::getDockerData(ui->comboBox_DockName->currentText());
    if(btmp.s_dockers_path==nullptr){
        autoDockData->s_dockers_name=ui->comboBox_DockName->currentText();
        autoDockData->s_dockers_path=ui->lineEdit_DockPath->text();
        autoDockData->s_dockers_wine_version=ui->comboBox_WinVersion->currentText();
    }else{
        *autoDockData=btmp;
    }
    SappDeployInfo pAppJsonData=ui->comboBox_JsonUrl->oData;
    if(pAppJsonData.s_deploy_app_name==nullptr){
        pAppJsonData.s_deploy_app_json=ui->comboBox_JsonUrl->currentText();
    }
    autoAppData->s_exe=ui->lineEdit_AppExePath->text();
    objectAppAT* objAutoAddApp=new objectAppAT();
    objAutoAddApp->connectDockAutoData(*autoDockData,*autoAppData,pAppJsonData);
    connect(objAutoAddApp,SIGNAL(Tips(QString)),this,SLOT(TipText(QString)));
    connect(objAutoAddApp,SIGNAL(Error(QString,bool)),this,SLOT(ErrorText(QString,bool)));
    connect(objAutoAddApp,SIGNAL(Done(SdockerData*,SappData*)),this,SLOT(ObjDone(SdockerData*,SappData*)));
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
void vekAppAddAT::ObjDone(SdockerData* _aDockData,SappData* aAppData){
    pObject::addAppDataToJson(*_aDockData,*aAppData);
    emit autoObjDock(_aDockData,aAppData);
    this->close();
}
