#include "vekAppAddMulti.h"
#include "ui_common.h"

vekAppAddMulti::vekAppAddMulti(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekAppAddMulti)
{
    ui->setupUi(this);
    vek_Style(this,0);
    connectObject();
}

vekAppAddMulti::~vekAppAddMulti()
{
    delete ui;
    ui=nullptr;
    emit _unMultAppAdd();
}
void vekAppAddMulti::connectObject(){
    connect(ui->pushButton_AddDiy,&QPushButton::clicked,this,&vekAppAddMulti::MultiAppDiy);
    connect(ui->pushButton_AddAuto,&QPushButton::clicked,this,&vekAppAddMulti::MultiAppAuto);
}
void vekAppAddMulti::MultiAppDiy(){
    emit _MultiAppDiy();
    this->close();
}
void vekAppAddMulti::MultiAppAuto(){
    emit _MultiAppAuto();
    this->close();
}
