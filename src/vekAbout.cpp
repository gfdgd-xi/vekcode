#include "vekAbout.h"
#include "ui_common.h"
#include "obj/pObject.h"
vekAbout::vekAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekAbout)
{
    ui->setupUi(this);
    qwidgetGeometry(this);
}

vekAbout::~vekAbout()
{
    delete ui;
    emit _unVekAbout();
}

