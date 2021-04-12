#include "vekPackage.h"
#include "ui_common.h"

vekPackage::vekPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekPackage)
{
    ui->setupUi(this);
    vSetDefalutTips();
}
vekPackage::~vekPackage()
{
    emit _unPackage();
    delete ui;
}
//传入打包参数
void vekPackage::vAppData(SdockerData _data,QString _uid){
    if(!_data.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
        pObject::vekTip("不支持非Deepin-Wine容器打包");
        return;
    }else{
        dDockerData=_data;
        dAppUid=_uid;
        vSetDefalut();
    }
}
void vekPackage::vSetDefalutTips(){
    ui->textEdit_AppDescr->setToolTip("例如:Tencent WeChat Client on Deepin Wine");
    ui->textEdit_AppNameEN->setToolTip("例如:WeChat");
    ui->textEdit_AppNameCN->setToolTip("例如:微信");
    ui->textEdit_DockerName->setToolTip("例如:Deepin-WeChat");
    ui->textEdit_AppType->setToolTip("例如:chat;");
    ui->textEdit_AppIco->setToolTip("例如:deepin.com.wechat.svg");
    ui->textEdit_AppMainName->setToolTip("例如:WeChat.exe");
    ui->textEdit_AppMainPath->setToolTip("例如:c:\\Program Files\\Tencent\\WeChat\\WeChat.exe");
    ui->textEdit_AppDebName->setToolTip("例如:com.qq.weixin.deepin");
    ui->textEdit_AppDebNamePro->setToolTip("例如:deepin.com.wechat");
    ui->textEdit_AppDebVersion->setToolTip("例如:2.9.5.41deepin4");
    ui->textEdit_AppOldDebName->setToolTip("例如:deepin.com.wechat");
}
void vekPackage::vSetDefalut(){
    QString appNameEn=sAppNameEN(dDockerData.map_dockers_data[dAppUid].s_main_proc_name);

    ui->textEdit_AppDescr->setText(dDockerData.map_dockers_data[dAppUid].s_name+" Client on Deepin Wine");
    ui->textEdit_AppDescr->setObjectName("应用描述");

    ui->textEdit_AppNameEN->setText(appNameEn.toLower());
    ui->textEdit_AppNameEN->setObjectName("应用名称(英文)");

    ui->textEdit_AppNameCN->setText(dDockerData.map_dockers_data[dAppUid].s_name);
    ui->textEdit_AppNameCN->setObjectName("应用名称(中文)");

    ui->textEdit_DockerName->setText("Deepin-"+appNameEn.toUpper());
    ui->textEdit_DockerName->setObjectName("部署容器名");

    ui->textEdit_AppType->setText(nullptr);
    ui->textEdit_AppType->setObjectName("应用分类");

    ui->textEdit_AppIco->setText("deepin.com."+appNameEn.toLower()+".svg");
    ui->textEdit_AppIco->setObjectName("应用ICO图标");

    ui->textEdit_AppMainName->setText(appNameEn+".exe");
    ui->textEdit_AppMainName->setObjectName("应用主程序名");

    ui->textEdit_AppMainPath->setText(dDockerData.map_dockers_data[dAppUid].s_exe);
    ui->textEdit_AppMainPath->setObjectName("应用主程序路径");

    ui->textEdit_AppDebName->setText("com."+appNameEn.toLower()+".deepin");
    ui->textEdit_AppDebName->setObjectName("最终deb包名");

    ui->textEdit_AppDebNamePro->setText("deepin.com."+appNameEn.toLower());
    ui->textEdit_AppDebNamePro->setObjectName("专业版包名");

    ui->textEdit_AppDebVersion->setText("1.0.0.0deepin5");
    ui->textEdit_AppDebVersion->setObjectName("最终deb包版本号");

    ui->textEdit_AppOldDebName->setText("deepin.com."+appNameEn.toLower());
    ui->textEdit_AppDebVersion->setObjectName("旧包名");
    connect(ui->pushButton_MOVEDOCKER,&QPushButton::clicked,this,&vekPackage::vMoveDockerToDir);
    connect(ui->pushButton_DELETEDOCKER,&QPushButton::clicked,this,&vekPackage::vDelDockerToDir);
    connect(ui->pushButton_InstallTool,&QPushButton::clicked,this,&vekPackage::vInstallPackageTool);
    connect(ui->pushButton_PackageDeb,&QPushButton::clicked,this,&vekPackage::vBuildDebPackage);
    connect(ui->pushButton_sel_exe_path,&QPushButton::clicked,this,&vekPackage::vSelExePath);
}
void vekPackage::vSelExePath(){
    QString exePath=QFileDialog::getOpenFileName(this,"选择执行程序","","exe Files(*.exe)");
    if(exePath!=nullptr){
        QFileInfo fi = QFileInfo(exePath);
        ui->textEdit_AppMainName->setText(fi.fileName());
        QString cArgs=dDockerData.s_dockers_path+"/"+dDockerData.s_dockers_name+"/dosdevices/";
        QString dArgs=dDockerData.s_dockers_path+"/"+dDockerData.s_dockers_name+"/drive_c/";
        qInfo()<<exePath;
        if(exePath.contains(cArgs,Qt::CaseSensitive)){
            exePath=exePath.replace(cArgs,"");
            exePath=exePath.replace("/","\\");
        }else if(exePath.contains(dArgs,Qt::CaseSensitive))
        {
            exePath=exePath.replace(dArgs,"c:\\");
            exePath=exePath.replace("/","\\");
        }
        ui->textEdit_AppMainPath->setText(exePath);
    }
}
bool vekPackage::vCheckOption(){
    QList<QLineEdit *> qLineList = this->findChildren<QLineEdit *>();
    foreach(auto tlb,qLineList)
    {
        if(tlb->text()==nullptr){
            pObject::vekTip(tlb->objectName()+"不能为空!");
            return false;
        }
    }
    pPackageData={};
    pPackageData.sDesrc=ui->textEdit_AppDescr->text();
    pPackageData.sAppNameEN=ui->textEdit_AppNameEN->text();
    pPackageData.sAppNameCN=ui->textEdit_AppNameCN->text();
    pPackageData.sDockerName=ui->textEdit_DockerName->text();
    pPackageData.sAppType=ui->textEdit_AppType->text();
    pPackageData.sAppIco=ui->textEdit_AppIco->text();
    pPackageData.sAppExeName=ui->textEdit_AppMainName->text();
    pPackageData.sAppExePath=ui->textEdit_AppMainPath->text();
    pPackageData.sAppDebName=ui->textEdit_AppDebName->text();
    pPackageData.sAppDebNamePro=ui->textEdit_AppDebNamePro->text();
    pPackageData.sAppDebVersion=ui->textEdit_AppDebVersion->text();
    pPackageData.sAppOldDebName=ui->textEdit_AppOldDebName->text();
    return true;
}
QString vekPackage::sAppNameEN(QString m_path){
    QFileInfo s_AppName(m_path);
    return s_AppName.baseName();
}
void vekPackage::vMoveDockerToDir(){
    if(!vCheckOption()){
        return;
    }else{
        bool dn_ok=false;
        QString dnTitle="输入迁移密码";
        QString dnLabel="输入错误后果自负";
        QString movePassword="";
        QLineEdit::EchoMode echoMode=QLineEdit::Normal;
        movePassword = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,movePassword, &dn_ok);
        if(!dn_ok){
            return;
        }else{
            QString srcDock=dDockerData.s_dockers_path+"/"+dDockerData.s_dockers_name;
            QString tagDock=QDir::homePath()+"/.deepinwine/"+ui->textEdit_DockerName->text();
            if(QDir(tagDock).exists()){
                pObject::vekTip("打包容器已经存在:"+tagDock);
                return;
            }else{
                QString agrs="echo "+movePassword+" | sudo -S cp -rfp "+ srcDock+" "+tagDock;
                system(agrs.toLocal8Bit());
                pObject::vekTip("容器迁移成功:"+tagDock);
            }
        }
    }
}
void vekPackage::vDelDockerToDir(){
    if(!vCheckOption()){
        return;
    }else{
        QString tagDock=QDir::homePath()+"/.deepinwine/"+ui->textEdit_DockerName->text();
        if(!QDir(tagDock).exists()){
            pObject::vekTip("打包容器不存在删除失败:"+tagDock);
            return;
        }else{
            QDir(tagDock).removeRecursively();
            pObject::vekTip("删除打包容器成功"+tagDock);
        }
    }
}

void vekPackage::vInstallPackageTool(){
    bool dn_ok=false;
    QString dnTitle="输入安装密码";
    QString dnLabel="输入错误后果自负";
    QString installPassword="";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;
    installPassword = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,installPassword, &dn_ok);
    if(!dn_ok){
        return;
    }else{
        if(!obj_package){
            delete obj_package;
            obj_package=nullptr;
        }
        obj_package= new objectPackage(dDockerData,pPackageData,installPassword);
        connect(obj_package,SIGNAL(outQStr(QString)),this,SLOT(outLogs(QString)));
        obj_package->EXToolDeb();
    }
}
void vekPackage::vBuildDebPackage(){
    if(vCheckOption()){
        if(!obj_package){
            delete obj_package;
            obj_package=nullptr;
        }
        obj_package= new objectPackage(dDockerData,pPackageData,nullptr);
        connect(obj_package,SIGNAL(outQStr(QString)),this,SLOT(outLogs(QString)));
        obj_package->EXPackage();
    }
}
void vekPackage::outLogs(QString log){
    ui->textEdit_Package_Log->append(log);
}
