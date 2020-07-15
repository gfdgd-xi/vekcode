#include "vekAbout.h"
#include "ui_common.h"
#include "vekInitObject.h"
vekAbout::vekAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekAbout)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint & Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("关于");
    vek_Style(this,0);
}

vekAbout::~vekAbout()
{
    delete ui;
    emit _unVekAbout();
}
