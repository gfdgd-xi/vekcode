#include "vekGameAddMulti.h"
#include "ui_common.h"

vekGameAddMulti::vekGameAddMulti(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekGameAddMulti)
{
    ui->setupUi(this);
    connectObject();
}

vekGameAddMulti::~vekGameAddMulti()
{
    delete ui;
    ui=nullptr;
    emit _unMultGameAdd();
}
void vekGameAddMulti::connectObject(){
    connect(ui->pushButton_AddDiy,&QPushButton::clicked,this,&vekGameAddMulti::MultiGameDiy);
    connect(ui->pushButton_AddAuto,&QPushButton::clicked,this,&vekGameAddMulti::MultiGameAuto);
}
void vekGameAddMulti::MultiGameDiy(){
    emit _MultiGameDiy();
    this->close();
}
void vekGameAddMulti::MultiGameAuto(){
    emit _MultiGameAuto();
    this->close();
}
