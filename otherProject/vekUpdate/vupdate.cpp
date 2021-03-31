#include "vupdate.h"
#include "ui_vupdate.h"
#include <QMouseEvent>
#include <QMessageBox>

vUpdate::vUpdate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vUpdate)
{
    ui->setupUi(this);
    this->loadStyleSheet(":/qss/rsc/css.qss");  
}

vUpdate::~vUpdate()
{
    delete ui;
}
void vUpdate::connectOBject(){
    connect(ui->pushButton_UpdateNow,&QPushButton::clicked,this,&vUpdate::on_ButtonClicked);
    connect(ui->pushButton_UpdateNo,&QPushButton::clicked,this,&vUpdate::on_ButtonClicked);
    ui->task_ProgressBar->setMinimum(0);  // 最小值
    ui->task_ProgressBar->setMaximum(0);  // 最大值
    ui->task_ProgressBar->hide();
}
void vUpdate::loadStyleSheet(const QString &styleSheetFile)
{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
    else
    {
        QMessageBox::information(this,"tip","cannot find qss file");
    }
}

void vUpdate::on_ButtonClicked()
{
    QObject *object = QObject::sender();
    QPushButton *action_obnject = qobject_cast<QPushButton *>(object);
    if(action_obnject->objectName()=="pushButton_UpdateNow"){
        ui->pushButton_UpdateNow->setEnabled(false);
        ui->pushButton_UpdateNo->setEnabled(false);
        nPos=0;
        downloadFile();
    }
    if(action_obnject->objectName()=="pushButton_UpdateNo"){
        this->close();
    }
}
void vUpdate::GetVerInfo(){
    dcurl=new datacurl(vUrlLogStr,nullptr);
    QString vUStr=QString::fromStdString(dcurl->vekGetData(vUrlLogStr));
    if(vUStr.contains("error",Qt::CaseSensitive)|vUStr.contains("403",Qt::CaseSensitive)|vUStr.contains("404",Qt::CaseSensitive)|vUStr.contains("505",Qt::CaseSensitive)){
       lableLogShow("网络错误!");
   }else{
       lableLogShow(vUStr);
   }
    delete dcurl;
    dcurl=nullptr;
}
//显示log
void vUpdate::lableLogShow(QString str){
    ui->lable_logs->setText(str);
}
void vUpdate::lableVersionShow(QString str){
    ui->lable_version->setText("版本号:"+str);
}
void vUpdate::downloadFile(){
    ui->task_ProgressBar->show();
    obj_Thread= new QThread;
    dcurl = new datacurl(vUrlFileStr,QApplication::applicationDirPath()+"/tempVek");
    //绑定下载
    connect(this,SIGNAL(ToThread()),dcurl,SLOT(vUp()));
    //绑定进度条
    connect(dcurl,SIGNAL(toPrgStr(long,long,int)),this,SLOT(task_ProgressBarShow(long,long,int)));
    //绑定线程结束后解包动作
    connect(dcurl,SIGNAL(doneDown(bool,bool)),this,SLOT(overThread(bool,bool)));
    //move To Thread
    dcurl->moveToThread(obj_Thread);
    obj_Thread->start();
    emit ToThread();
    controlSatae(false);
}
void vUpdate::overThread(bool tState,bool objTip){
   if(!objTip){
        QMessageBox::warning(nullptr,"TIP","网络出错请重试!");
   }else{
       upVek();
   }
   controlSatae(tState);
}
void vUpdate::controlSatae(bool dState){
    ui->pushButton_UpdateNow->setEnabled(dState);
    ui->pushButton_UpdateNo->setEnabled(dState);
}
void vUpdate::upVek(){
    QString uFilePath=QApplication::applicationDirPath()+"/tempVek";
    char* uFile=("unzip -P "+vUrlPassWord+" "+uFilePath).toLocal8Bit().data();
    system(uFile);
    QFileInfo fileInfo(vUrlFileStr);
    QString fName=fileInfo.baseName();
    uFilePath=QApplication::applicationDirPath()+"/"+fName+"/vek";
    qInfo()<<fName;
    qInfo()<<uFilePath;
    char* uCP=("cp -r -p "+uFilePath+" "+QApplication::applicationDirPath()+"/vek").toLocal8Bit().data();
    system(uCP);
    QDir uDir=QApplication::applicationDirPath()+"/"+fName;
    if(uDir.exists()){
        uDir.removeRecursively();
    }
    QFile::setPermissions(QApplication::applicationDirPath()+"/vek",
                          QFile::ReadOther|
                          QFile::WriteOther|
                          QFile::ReadOwner|
                          QFile::WriteOwner|
                          QFile::ReadGroup|
                          QFile::ExeOther|
                          QFile::ExeUser|
                          QFile::ExeGroup);
    QProcess* m_cmd=new QProcess();
    m_cmd->setWorkingDirectory(QApplication::applicationDirPath());
    m_cmd->startDetached(QApplication::applicationDirPath()+"/vek");
    this->close();
}
void vUpdate::task_ProgressBarShow(long dlnow,long dltd,int dlPos){
    if(dlPos!=nPos){
        ui->task_ProgressBar->setRange(0,dltd);
        ui->task_ProgressBar->setMaximum(dltd);
        ui->task_ProgressBar->setValue(dlnow);
        ui->task_ProgressBar->setFormat(QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(dlPos)));
    }else{
        nPos=dlPos;
    }
    if(dlPos==100){
        ui->pushButton_UpdateNow->setEnabled(true);
        ui->pushButton_UpdateNo->setEnabled(true);
    }

}
