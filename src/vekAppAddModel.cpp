#include "vekAppAddModel.h"
#include "ui_common.h"

vekAppAddModel::vekAppAddModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekAppAddModel)
{
    ui->setupUi(this);
    connectObject();
}

vekAppAddModel::~vekAppAddModel()
{
    delete ui;
    emit _unMultAppAdd();
}
void vekAppAddModel::connectObject(){
    connect(ui->pushButton_AddDiy,&QPushButton::clicked,this,&vekAppAddModel::MultiAppDiy);
    connect(ui->pushButton_AddAuto,&QPushButton::clicked,this,&vekAppAddModel::MultiAppAuto);
}
void vekAppAddModel::MultiAppDiy(){
    emit _MultiAppDiy();
    this->close();
}
void vekAppAddModel::MultiAppAuto(){
    emit _MultiAppAuto();
    this->close();
}
