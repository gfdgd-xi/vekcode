#ifndef VEKPACKAGE_H
#define VEKPACKAGE_H

#include "obj/common.h"
#include "obj/objectPackage.h"
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
    Spackage pPackageData;
    objectPackage* obj_package;
    QString dAppUid;
    void vSetDefalut();
    void vSetDefalutTips();
    bool vCheckOption();
    QString sAppNameEN(QString);
    //打开容器目录
    void vOpenDockerToDir();
private slots:
    //迁移容器
    void vMoveDockerToDir();
    void vDelDockerToDir();
    void vInstallPackageTool();
    void vBuildDebPackage();
    void vSelExePath();
    void outLogs(QString);
signals:
    void _unPackage();
};
#endif // VEKDEBUG_H
