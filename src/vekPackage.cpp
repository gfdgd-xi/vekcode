#include "vekPackage.h"
#include "ui_common.h"



vekPackage::vekPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekPackage)
{
    ui->setupUi(this);
}
vekPackage::~vekPackage()
{
    delete ui;
}
void vekPackage::initUI(){


}
