#include "vekWineOption.h"
#include "ui_common.h"
#include "obj/pObject.h"

vekWineOption::vekWineOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekWineOption)
{
    ui->setupUi(this);
    InitWineInstall();
    githread = new objectGitWine();
    //下载按钮槽事件绑定
    connect(ui->pushButton_Install,&QPushButton::clicked,this,&vekWineOption::onButton_Install);
    connect(ui->pushButton_deleteWine,&QPushButton::clicked,this,&vekWineOption::deleteWine);
    connect(ui->toolButton_SetInstallDir,&QPushButton::clicked,this,&vekWineOption::on_toolButton);
    //
    connect(githread,&objectGitWine::outputPrgressSignals,this,&vekWineOption::appendTextToLog);
    connect(githread,&objectGitWine::overThreadSignals,this,&vekWineOption::overGitThreadSignals);
    connect(ui->comboBox_wineSrc,&QComboBox::currentTextChanged,this,&vekWineOption::WineVersionComoboBox);

    GetWineGitInfo();
}

vekWineOption::~vekWineOption()
{
    delete ui;
    emit _unInitWineOption();
}

void vekWineOption::InitWineInstall()
{

}
//获取远程仓库wine版本信息
void vekWineOption::GetWineGitInfo(){
    if(!g_vekLocalData.wineSource.empty()){
        for(auto &d:g_vekLocalData.wineSource){
            ui->comboBox_wineSrc->addItem(d.first);
        }
    }
    WineVersionComoboBox();
    ui->lineEdit_InstallPath->setText(QDir::currentPath());
}
void vekWineOption::WineVersionComoboBox(){
    ui->comboBox_wineVer->clear();
    QString nowWineSrc=ui->comboBox_wineSrc->currentText();
    if(nowWineSrc==nullptr){
        nowWineSrc="DefaultSrc";
    }
    if(!g_vekLocalData.wineJsonList.empty()){
        for(auto &d : g_vekLocalData.wineJsonList){
            if(d.first==nowWineSrc){
                for(auto dx:d.second){
                    ui->comboBox_wineVer->addItem(dx.second.WineName);
                }
            }
        }
    }
}
void vekWineOption::onButton_Install()
{
    if(ui->lineEdit_InstallPath->text()==nullptr){
        vekTip("请选择Wine安装路径");
        return;
    }
    QString selPath=ui->lineEdit_InstallPath->text();
    QString selwine=ui->comboBox_wineVer->currentText();
    QString selSrc=ui->comboBox_wineSrc->currentText();
    BaseWineData iWD;
    for(auto [d,p] :g_vekLocalData.wineJsonList){
        if(d==selSrc){
            for(auto dx:p){
                if(dx.first==selwine){
                    iWD.IwineSrc=selSrc;
                    iWD.IwineName=dx.second.WineName;
                    iWD.IwineVer=dx.second.WineVersion;
                    iWD.IwineUrl=dx.second.WineGit;
                    iWD.IwinePath=selPath+"/vekWine/"+dx.second.WineName;
                    iWD.IwineMono=dx.second.Mono;
                    iWD.IwineGeckoX86=dx.second.GeckoX86;
                    iWD.IwineGeckoX86_64=dx.second.GeckoX86_64;
                    for(auto v:dx.second.WineDxvk){
                        iWD.IwineDxvk.insert(iWD.IwineDxvk.end(),v);
                    }
                    break;
                }
            }
        }
    }
    githread->_wd=iWD;
    githread->start();
    controlState(false);
}
void vekWineOption::deleteWine(){
    QString wineName=ui->comboBox_wineVer->currentText();
    QString winePath=nullptr;
    for(auto a:g_vekLocalData.wineVec){
        if(a.first==wineName){
            winePath=a.second.IwinePath;
            break;
        }
    }
    if(vekMesg("您确定要删除"+wineName+"路径为:"+winePath)){
        if(winePath!=nullptr){
            QDir wineInstallDir(winePath);
            if(wineInstallDir.exists()){
                wineInstallDir.removeRecursively();
                g_vekLocalData.wineVec.erase(wineName);
                DeleteWineDataToJson(wineName);
                vekTip("删除成功!");
            }
        }else{
            vekTip("删除失败!");
            return;
        }
    }
}
void vekWineOption::controlState(bool pState){
    ui->pushButton_Install->setEnabled(pState);
    ui->pushButton_deleteWine->setEnabled(pState);
    ui->comboBox_wineSrc->setEnabled(pState);
    ui->comboBox_wineVer->setEnabled(pState);
    ui->lineEdit_InstallPath->setEnabled(pState);
    ui->toolButton_SetInstallDir->setEnabled(pState);
}
void vekWineOption::appendTextToLog()
{
    ui->textEdit->document()->setMaximumBlockCount(200);
    ui->textEdit->append(githread->outputPrgressText);
    QTextCursor cursor=ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}
void vekWineOption::overGitThreadSignals()
{
    githread->exit();
    controlState(true);
}
void vekWineOption::on_toolButton()
{
    QWidget *qwidget = new QWidget();
    QString installPath=QFileDialog::getExistingDirectory(qwidget,"选择Wine保存目录","",QFileDialog::ShowDirsOnly);
    if(installPath!=nullptr){
        ui->lineEdit_InstallPath->setText(installPath);
    }

}
