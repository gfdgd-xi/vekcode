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
    delete ui;
    emit _unVekAbout();
}

