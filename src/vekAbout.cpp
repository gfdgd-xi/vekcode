#include "vekAbout.h"
#include "ui_common.h"
#include "vekInitObject.h"
vekAbout::vekAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekAbout)
{
    ui->setupUi(this);
    qwidgetGeometry(this);
    vek_Style(this,0);
}

vekAbout::~vekAbout()
{
    delete vekgetcurl;
    vekgetcurl=nullptr;
    delete ui;
    emit _unVekAbout();
}
void vekAbout::getUpdateLogs(){
    if(vekgetcurl==nullptr){
        vekgetcurl=new vekGetCurl;
    }
    QString upinfo=QString::fromStdString(vekgetcurl->vekGetData(vekUpInfo.toStdString()));
    ui->textEdit_UpLogs->append(upinfo);
}
