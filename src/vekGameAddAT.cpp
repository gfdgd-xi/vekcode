#include "vekGameAddAT.h"
#include "ui_common.h"

vekGameAddAT::vekGameAddAT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekGameAddAT)
{
    ui->setupUi(this);
}

vekGameAddAT::~vekGameAddAT()
{
    delete ui;
    emit _unAutoDock();
}
void vekGameAddAT::connectDockObject(BaseGameData* _data){
    autoGameData=_data;
    if(autoGameData==nullptr){
        autoGameData=new BaseGameData();
    }
    connect(ui->pushButton_DockDone,&QPushButton::clicked,this,&vekGameAddAT::addAutoGame);
    connect(ui->pushButton_AutoJson,&QPushButton::clicked,this,&vekGameAddAT::SetObject);
    connect(ui->pushButton_AutoDockPath,&QPushButton::clicked,this,&vekGameAddAT::SetObject);
    connect(ui->pushButton_SetExePath,&QPushButton::clicked,this,&vekGameAddAT::SetObject);
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
    for(auto & d:g_vekLocalData.gameScrSource){
        ui->comboBox_SrcGame->addItem(d.first);
    }
    for(auto & v:g_vekLocalData.gameJsonList){
        if(v.first==ui->comboBox_SrcGame->currentText()){
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
void vekGameAddAT::SetObject(){
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
           ui->lineEdit_GameExePath->setText(strPath);
        }
    }

}
QString vekGameAddAT::JsonType(QString str){
    //查看jsonPaht头是否为http或者https
    if(str.startsWith("http",Qt::CaseSensitive)){
        return str;
    }
    if(str.startsWith("https",Qt::CaseSensitive)){
        return str;
    }
    if(str.endsWith("json",Qt::CaseSensitive)){
        return str;
    }
    for(auto & v:g_vekLocalData.gameJsonList){
        if(v.first==ui->comboBox_SrcGame->currentText()){
            for(auto & y:v.second){
                if(y.first==str){
                    str=y.second;
                }
            }
        }
    }
    return str;
}
void vekGameAddAT::addAutoGame(){
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
        return;
        this->close();
    }
    if(ui->lineEdit_GameExePath->text()==nullptr){
         vekTip("请设置游戏运行exe文件路径");
         return;
    }
    ObjectAddDataAT objAddDataAT;  
    objAddDataAT.pJsonPath=JsonType(ui->comboBox_JsonUrl->currentText());
    objAddDataAT.pDockName=ui->comboBox_DockName->currentText();
    objAddDataAT.pDckPath=ui->lineEdit_DockPath->text();
    objAddDataAT.pWineVersion=ui->comboBox_WinVersion->currentText();
    objAddDataAT.pGameExePath=ui->lineEdit_GameExePath->text();
    objAddDataAT.pBaseGameData=autoGameData;
    if(objAutoAddGame!=nullptr){
        delete objAutoAddGame;
        objAutoAddGame=nullptr;
    }
    objAutoAddGame=new objectAddGameAT(objAddDataAT);
    connect(objAutoAddGame,SIGNAL(Tips(QString)),this,SLOT(TipText(QString)));
    connect(objAutoAddGame,SIGNAL(Error(QString,bool)),this,SLOT(ErrorText(QString,bool)));
    connect(objAutoAddGame,SIGNAL(Done()),this,SLOT(ObjDone()));
    objAutoAddGame->start();
    controlState(false);
}
void vekGameAddAT::controlState(bool pState){
    ui->comboBox_SrcGame->setEnabled(pState);
    ui->comboBox_JsonUrl->setEnabled(pState);
    ui->pushButton_AutoJson->setEnabled(pState);
    ui->comboBox_WinVersion->setEnabled(pState);
    ui->lineEdit_DockPath->setEnabled(pState);
    ui->pushButton_AutoDockPath->setEnabled(pState);
    ui->comboBox_DockName->setEnabled(pState);
    ui->lineEdit_GameExePath->setEnabled(pState);
    ui->pushButton_SetExePath->setEnabled(pState);
    ui->pushButton_DockDone->setEnabled(pState);
}
void vekGameAddAT::TipText(QString TipInfo)
{
    ui->label_ProgText->setText(TipInfo);
}
void vekGameAddAT::ErrorText(QString ErrorInfo,bool cState){
    ui->label_ProgText->setText(ErrorInfo);
    controlState(cState);
}
void vekGameAddAT::ObjDone(){
    emit autoObjDock(autoGameData);
    this->close();
}
