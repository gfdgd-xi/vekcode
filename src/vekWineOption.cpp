#include "vekWineOption.h"
#include "ui_common.h"
#include "vekInitObject.h"

vekWineOption::vekWineOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekWineOption)
{
    ui->setupUi(this);
    InitWineInstall();
    githread = new vekGitWine();
    //下载按钮槽事件绑定
    connect(ui->pushButton_Install,&QPushButton::clicked,this,&vekWineOption::onButton_Install);
    connect(ui->pushButton_deleteWine,&QPushButton::clicked,this,&vekWineOption::deleteWine);
    connect(ui->toolButton_SetInstallDir,&QPushButton::clicked,this,&vekWineOption::on_toolButton);
    //
    connect(githread,&vekGitWine::outputPrgressSignals,this,&vekWineOption::appendTextToLog);
    connect(githread,&vekGitWine::overThreadSignals,this,&vekWineOption::overGitThreadSignals);
    connect(ui->comboBox_wineSrc,&QComboBox::currentTextChanged,this,&vekWineOption::WineVersionComoboBox);

    vek_Style(this,0);
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
                    iWD.IwinePath=selPath+"/vekWine/"+dx.second.WineName+"/";
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
      QString winePath=ui->lineEdit_InstallPath->text();
      if(wineName==NULL&&winePath==NULL){
          return;
      }
      BaseWineData _bWineData;
      for(auto a:g_vekLocalData.wineVec){
          if(a.first==wineName){
              g_vekLocalData.wineVec.erase(a.first);
              break;
          }
      }
      QDir wineInstallDir(winePath+"/vekWine/"+wineName);
      if(wineInstallDir.exists()){
           wineInstallDir.removeRecursively();
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
    QString installPath=QFileDialog::getExistingDirectory(qwidget,"选择Wine保存目录","",nullptr);
    if(installPath!=NULL){
       ui->lineEdit_InstallPath->setText(installPath);
    }

}
