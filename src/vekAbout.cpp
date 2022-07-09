#include "vekAbout.h"
#include "ui_common.h"
#include "obj/pObject.h"
#include "obj/objectGetCurl.h"
vekAbout::vekAbout() :ui(new Ui::vekAbout)
{
    ui->setupUi(this);
    pObject::qwidgetGeometry(this);
}

vekAbout::~vekAbout()
{

}
void vekAbout::GetVerInfo(){
    objectGetCurl* _datacurl=new objectGetCurl;
    QString vUStr=QString::fromStdString(_datacurl->vekGetData(g_srcUrl.SrcLogShow.toStdString()));
    if(vUStr.contains("error",Qt::CaseSensitive)|vUStr.contains("403",Qt::CaseSensitive)|vUStr.contains("404",Qt::CaseSensitive)|vUStr.contains("505",Qt::CaseSensitive)){
        vUStr="网络错误!";
    }
    delete _datacurl;
    _datacurl=nullptr;
    ui->textEdit4->setText(vUStr);
}

