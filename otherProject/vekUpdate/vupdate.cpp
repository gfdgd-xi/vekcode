#include "vupdate.h"
#include "ui_vupdate.h"
#include <QMouseEvent>
#include <QMessageBox>
#include "datacurl.h"
vUpdate::vUpdate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vUpdate)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);
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
    datacurl* _datacurl=new datacurl;
    QString vUStr=QString::fromStdString(_datacurl->vekGetData(vUrlLogStr));
    if(vUStr.contains("error",Qt::CaseSensitive)|vUStr.contains("403",Qt::CaseSensitive)|vUStr.contains("404",Qt::CaseSensitive)|vUStr.contains("505",Qt::CaseSensitive)){
       lableLogShow("网络错误!");
   }else{
       lableLogShow(vUStr);
   }
    delete _datacurl;
    _datacurl=nullptr;
}
//显示log
void vUpdate::lableLogShow(QString str){
    ui->lable_logs->setText(str);
}
void vUpdate::lableVersionShow(QString str){
    ui->lable_version->setText("版本号:"+str);
}
void vUpdate::downloadFile(){
    datacurl* _datacurl=new datacurl;
    _datacurl->SetUrlPath(vUrlFileStr,QDir::currentPath()+"/tempVek");
    ui->task_ProgressBar->show();
    connect(_datacurl,SIGNAL(curlPrgressSignals(long,long,int)),this,SLOT(task_ProgressBarShow(long,long,int)));
    connect(_datacurl,SIGNAL(doneDown()),this,SLOT(runVek()));
    _datacurl->start();
}
void vUpdate::runVek(){
    QString vekNewFile=QDir::currentPath()+"/tempVek";
    QString vekOldFile=QDir::currentPath()+"/vek";
    QFile newFile(vekNewFile);
    QFile oldFile(vekOldFile);
    if(newFile.exists()){
        if(oldFile.exists()){
            oldFile.remove();
        }
        QFile::rename(vekNewFile,QDir::currentPath()+"/vek");

        QFile::setPermissions(QDir::currentPath()+"/vek",
                              QFile::ReadOther|
                              QFile::WriteOther|
                              QFile::ReadOwner|
                              QFile::WriteOwner|
                              QFile::ReadGroup|
                              QFile::ExeOther|
                              QFile::ExeUser|
                              QFile::ExeGroup);

        QProcess* m_cmd=new QProcess();
        m_cmd->setWorkingDirectory(QDir::currentPath());
        m_cmd->startDetached(QDir::currentPath()+"/vek");
        this->close();
    }
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
