#include "vekExtendDebug.h"
#include "ui_common.h"
vekExtendDebug::vekExtendDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekExtendDebug)
{
    ui->setupUi(this);
}
vekExtendDebug::~vekExtendDebug()
{
    emit _unVekDebug();
    delete ui;
}
void vekExtendDebug::ConnectDebugObject(QString dockName,QString appCID){
    connect(ui->pushButton_DebugStart,&QPushButton::clicked,this,&vekExtendDebug::ExtendApp);
    connect(ui->pushButton_DebugDllAdd,&QPushButton::clicked,this,&vekExtendDebug::addDll);
    connect(ui->pushButton_DebugDllDel,&QPushButton::clicked,this,&vekExtendDebug::delDll);
    connect(ui->pushButton_DebugForceExit,&QPushButton::clicked,this,&vekExtendDebug::exitDebug);
    connect(ui->radioButton_write_log,SIGNAL(toggled(bool)),this,SLOT(onRadioClickFruits()));
    for(auto xz:dllList){
        ui->comboBox_DebugDllList->addItem(xz);
    }
    for(auto a:g_vekLocalData.map_docker_list){
        if(a.first==dockName){
            for(auto b:a.second.map_dockers_data){
                if(b.second.s_uid==appCID){
                    appData=b.second;
                    dockData=a.second;
                    break;
                }
            }
        }
    }

    if(!QDir(fileDir).exists()){
        QDir().mkdir(fileDir);
    }
    ui->radioButton_write_log->setChecked(writeState);
}

void vekExtendDebug::outputMessage(QString oMsg)
{
    ui->logTextEdit->document()->setMaximumBlockCount(1000);
        if(oMsg!=nullptr){
            ui->logTextEdit->append(oMsg);
        }
        if(writeState){
            QFile file(fileDir+appData.s_name+"_"+qStrTime+"_log.txt");
            file.open(QIODevice::WriteOnly | QIODevice::Append);
            QTextStream text_stream(&file);
            text_stream << oMsg << "\r\n";
           file.flush();
            file.close();
       }
        QTextCursor cursor=ui->logTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->logTextEdit->setTextCursor(cursor);
}
void vekExtendDebug::onRadioClickFruits()
{
    if (ui->radioButton_write_log->isChecked())
    {
        writeState=true;
    }
    else
    {
        writeState=false;
    }
}

void vekExtendDebug::addDll(){
    QString xData="+"+ui->comboBox_DebugDllList->currentText();
    if(!DebugDllStr.empty()){
        for(auto x:DebugDllStr){
            if(x==xData){
                return;
            }
        }
        if(DebugDllStr.size()>=1){
            DebugDllStr.append(",");
        }
    }
    DebugDllStr.append(xData);
    upDllStr();
}
void vekExtendDebug::delDll(){
    QString tData;
    if(DebugDllStr.empty()){
        return;
    }
    for(auto x:DebugDllStr){
        tData="+"+ui->comboBox_DebugDllList->currentText();
        if(x==tData){
            DebugDllStr.removeOne(tData);
            if(DebugDllStr.size()>1){
                DebugDllStr.removeLast();
            }
            upDllStr();
        }
    }
}

void vekExtendDebug::ExtendApp(){
    QDateTime dateTime(QDateTime::currentDateTime());
    qStrTime=dateTime.toString("yy_MM_dd_hh_mm_ss");
    objectDebug* objDebug=new objectDebug();
    objDebug->setArgs(dockData,appData,DebugDllStr);
    QObject::connect(objDebug,SIGNAL(outLogEmit(QString)),this,SLOT(outputMessage(QString)));
    objDebug->start();
}
void vekExtendDebug::exitDebug(){
    objectDebug* objDebug=new objectDebug();
    objDebug->setArgs(dockData,appData,DebugDllStr);
    objDebug->exitDebug();
    delete objDebug;
    objDebug=nullptr;
}
void vekExtendDebug::upDllStr(){
    ui->lineEdit_DebugDllStr->setText(DebugDllStr.join(""));
}
