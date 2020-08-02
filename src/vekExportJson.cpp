#include "vekExportJson.h"
#include "ui_vekExportJson.h"

vekExportJson::vekExportJson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekExportJson)
{
    ui->setupUi(this);
    connect(ui->pushButton_otherSave,&QPushButton::clicked,this,&vekExportJson::SaveJson);
}

vekExportJson::~vekExportJson()
{
    emit _unExportJson();
    delete ui;
}
void vekExportJson::ExportJson(BaseAppData _bAppData){
   objectJson* oJson=new objectJson;
   QString tJson=QString::fromStdString(oJson->exportJson(_bAppData).dump(4));
   ui->textEdit_OutPutStr->setText(tJson);
}
void vekExportJson::SaveJson(){
    QString saveStr=ui->textEdit_OutPutStr->toPlainText();
    QString savePath = QFileDialog::getSaveFileName(this,tr("选择保存json路径"),".",tr("json Files(*.json)"));
    bool vekMesgDxvkSave=false;
    if(savePath!=nullptr&saveStr!=nullptr){
       vekMesgDxvkSave=vekMesg("是否把json配置文件保存到"+savePath);
    }else{
        return;
    }
    if(vekMesgDxvkSave)
    {
        if(QFile(savePath).exists()){
            if(vekMesg("是否覆盖"+savePath)){
                QFile(savePath).remove();
            }else{
                savePath = QFileDialog::getSaveFileName(this,tr("选择保存json路径"),".",tr("json Files(*.json)"));
            }
        }
    }else{
        savePath = QFileDialog::getSaveFileName(this,tr("选择保存json路径"),".",tr("json Files(*.json)"));
    }
    if(savePath!=NULL){
        saveStrToFile(ui->textEdit_OutPutStr->toPlainText(),savePath);
    }
}
