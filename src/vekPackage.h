#ifndef VEKPACKAGE_H
#define VEKPACKAGE_H

#include "obj/common.h"

namespace Ui {
class vekPackage;

}

class vekPackage : public QDialog
{
    Q_OBJECT

public:
    explicit vekPackage(QWidget *parent = nullptr);
    ~vekPackage();
    void vAppData(SdockerData,QString);
private:
    Ui::vekPackage *ui;
    SdockerData dDockerData;
    QString dAppUid;   
    void vSetDefalut();
    void vSetDefalutTips();
    bool vCheckOption();
    QString sAppNameEN(QString);
    //导入打包参数
    void vInPutBuildDebArgs();
    //导出打包参数
    void vOutPutBuildDebArgs();
    //打开容器目录
    void vOpenDockerToDir();
    //自动打包
    void vBuildDebPackage();
private slots:
    //迁移容器
    void vMoveDockerToDir();
    void vDelDockerToDir();
signals:
     void _unPackage();
};
#endif // VEKDEBUG_H
