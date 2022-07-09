#include "vgit.h"
#include "ui_vgit.h"

vGit::vGit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vGit)
{
    ui->setupUi(this);
    setWindowFlags (Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

vGit::~vGit()
{
    delete ui;
}

