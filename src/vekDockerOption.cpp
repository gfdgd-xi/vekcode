#include "vekDockerOption.h"
#include "ui_common.h"

vekDockerOption::vekDockerOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekDockerOption)
{
    ui->setupUi(this);
    pObject::qwidgetGeometry(this);
}

vekDockerOption::~vekDockerOption()
{
    emit _unOption();
}
//绑定槽
void vekDockerOption::vekAppAddConnectObject(const SdockerData& _data){
    tempDockData=new SdockerData();
    *tempDockData=_data;
    connect(ui->pushButton_Save,&QPushButton::clicked,this,&vekDockerOption::objectButton);
    connect(ui->pushButton_SetDockPath,&QPushButton::clicked,this,&vekDockerOption::objectButton);
    connect(ui->checkBox_ICMP,SIGNAL(clicked()),this,SLOT(ICMPChanged()));
    ui->comboBox_WinVersion->clear();
    if(!g_vekLocalData.map_wine_list.empty())
    {
        for(auto & x :g_vekLocalData.map_wine_list)
        {
            ui->comboBox_WinVersion->addItem(x.first);
        }

    }else{
        pObject::vekTip("请先安装Wine");
        this->close();
    }
    for(auto&y:_dockSystemVersion){
        ui->comboBox_dockSystemVersion->addItem(y);
    }
    wineChanged();
    if(!g_vekLocalData.map_docker_list.empty()){
        for(auto &a:g_vekLocalData.map_docker_list){
            ui->comboBox_DockerName->addItem(a.first);
        }
    }
    //控件缺省设置
    ui->lineEdit_DockerPath->setText(tempDockData->s_dockers_path);
    ui->comboBox_DockerName->setCurrentText(tempDockData->s_dockers_name);
    ui->comboBox_WinVersion->setCurrentText(tempDockData->s_dockers_wine_version);
    ui->checkBox_Mono->setChecked(tempDockData->s_dockers_mono_state);
    ui->checkBox_Gecko->setChecked(tempDockData->s_dockers_gecko_state);
    ui->comboBox_dockbit->setCurrentText(tempDockData->s_dockers_bit_version);
    ui->comboBox_winebit->setCurrentText(tempDockData->s_dockers_wine_exe_version);
    ui->comboBox_dockSystemVersion->setCurrentText(tempDockData->s_dockers_system_version);
    ui->checkBox_Ass->setChecked(tempDockData->s_dockers_disable_ass);
    ui->checkBox_winerunlog->setChecked(tempDockData->s_dockers_task_log);
    ui->checkBox_wineMemorySharing->setChecked(tempDockData->s_dockers_sharedmemory);
    ui->checkBox_wineMemoryOptimization->setChecked(tempDockData->s_dockers_writecopy);
    ui->checkBox_wineRealTimePriority->setChecked(tempDockData->s_dockers_rtserver);
    ui->checkBox_DefaultFonts->setChecked(tempDockData->s_dockers_default_fonts);
    ui->checkBox_ICMP->setChecked(tempDockData->s_dockers_ICMP_state);
    if(tempDockData->s_dockers_ICMP_state){
        ui->checkBox_ICMP->setEnabled(false);
    }
    if(g_vekLocalData.map_wine_list[ui->comboBox_WinVersion->currentText()].s_local_wine_mono!=nullptr){
        if(!QFile(g_vekLocalData.map_wine_list[ui->comboBox_WinVersion->currentText()].s_local_wine_path+"/plugs/Mono.msi").exists()){
            ui->checkBox_Mono->setEnabled(false);
        }
    }
    if(g_vekLocalData.map_wine_list[ui->comboBox_WinVersion->currentText()].s_local_wine_mono!=nullptr){
        if(!QFile(g_vekLocalData.map_wine_list[ui->comboBox_WinVersion->currentText()].s_local_wine_path+"/plugs/GeckoX86.msi").exists()&&!QFile(g_vekLocalData.map_wine_list[ui->comboBox_WinVersion->currentText()].s_local_wine_path+"/plugs/GeckoX86_64.msi").exists()){
            ui->checkBox_Gecko->setEnabled(false);
        }
    }
    if(g_vekLocalData.map_wine_list[ui->comboBox_WinVersion->currentText()].s_local_wine_mono!=nullptr){
        if(!QFile(g_vekLocalData.map_wine_list[ui->comboBox_WinVersion->currentText()].s_local_wine_path+"/plugs/Mono.msi").exists()){
            ui->checkBox_Mono->setEnabled(false);
        }
    }
}
void vekDockerOption::ICMPChanged(){
    QCheckBox *button=(QCheckBox*)(sender());
    if(button->checkState()==Qt::Checked){
        bool b_state=pObject::vekMesg("警告：开启ICMP需要管理员权限，开启后无法关闭");
        bool bn_ok=false;
        QString mPassword;
        if(b_state){
            QString dnTitle="输入授权密码";
            QString dnLabel="输入错误后果自负";
            QLineEdit::EchoMode echoMode=QLineEdit::Normal;
            mPassword = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,mPassword, &bn_ok);
        }
        if(b_state&bn_ok){
            qInfo()<<mPassword;
            system(("echo "+mPassword+" | sudo -S chmod +x "+tempDockData->s_dockers_wine_path+"/wine/bin/wine-preloader").toLocal8Bit());
            system(("echo "+mPassword+" | sudo -S chmod +x "+tempDockData->s_dockers_wine_path+"/wine/bin/wine64-preloader").toLocal8Bit());
            ui->checkBox_ICMP->setChecked(true);
            tempDockData->s_dockers_ICMP_state=ui->checkBox_ICMP->checkState();
        }else{
            ui->checkBox_ICMP->setCheckState(Qt::Unchecked);
        }

    }
}
void vekDockerOption::wineChanged(){
    ui->comboBox_dockbit->clear();
    ui->comboBox_winebit->clear();
    QStringList dWin;
    QStringList dWine;
    dWin<<"win32"<<"win64";
    dWine<<"wine"<<"wine64";
    ui->comboBox_dockbit->addItems(dWin);
    ui->comboBox_winebit->addItems(dWine);
}

//控件数据to struct
bool vekDockerOption::vekAppConfigObj(){
    //Docker默认参数
    if(ui->lineEdit_DockerPath->text()!=nullptr){
        tempDockData->s_dockers_path=ui->lineEdit_DockerPath->text();
    }else{
        tempDockData->s_dockers_path=QApplication::applicationDirPath()+"/vekDock";
    }
    if(ui->comboBox_DockerName->currentText()!=nullptr){
        tempDockData->s_dockers_name=ui->comboBox_DockerName->currentText();
    }else{
        tempDockData->s_dockers_name="vekON1";
    }
    tempDockData->s_dockers_wine_version=ui->comboBox_WinVersion->currentText();
    tempDockData->s_dockers_wine_path= g_vekLocalData.map_wine_list[tempDockData->s_dockers_wine_version].s_local_wine_path;
    tempDockData->s_dockers_system_version=ui->comboBox_dockSystemVersion->currentText();
    tempDockData->s_dockers_bit_version=ui->comboBox_dockbit->currentText();
    tempDockData->s_dockers_wine_exe_version=ui->comboBox_winebit->currentText();
    tempDockData->s_dockers_mono_state=ui->checkBox_Mono->checkState();
    tempDockData->s_dockers_gecko_state=ui->checkBox_Gecko->checkState();
    //优化参数
    tempDockData->s_dockers_ICMP_state=ui->checkBox_ICMP->checkState();
    tempDockData->s_dockers_disable_ass=ui->checkBox_Ass->checkState();
    tempDockData->s_dockers_task_log=ui->checkBox_winerunlog->checkState();
    tempDockData->s_dockers_sharedmemory=ui->checkBox_wineMemorySharing->checkState();
    tempDockData->s_dockers_writecopy=ui->checkBox_wineMemoryOptimization->checkState();
    tempDockData->s_dockers_default_fonts=ui->checkBox_DefaultFonts->checkState();
    tempDockData->s_dockers_rtserver=ui->checkBox_wineRealTimePriority->checkState();
    return checkDocerOption();
}
//检查docker参数
bool vekDockerOption::checkDocerOption(){
    if(tempDockData->s_dockers_wine_version==nullptr){
        pObject::vekError("请先安装wine");
        return false;
    }
    if(tempDockData->s_dockers_path==nullptr)
    {
        pObject::vekError("请设置wine运行容器路径");
        return false;
    }
    if(tempDockData->s_dockers_name==nullptr){
        pObject::vekError("请设置容器名字");
        return false;
    }
    if(tempDockData->s_dockers_wine_path==nullptr){
        pObject::vekError("请先安装wine");
        return false;
    }
    return true;
}
//按钮事件集中处理
void vekDockerOption::objectButton(){
    QObject *object = QObject::sender();
    QPushButton *action_obnject = qobject_cast<QPushButton *>(object);
    //设置DOCK路径
    if(action_obnject->objectName()=="pushButton_SetDockPath"){
        QWidget *qwidget = new QWidget();
        QString dockPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(dockPath!=nullptr){
            ui->lineEdit_DockerPath->setText(dockPath);
        }
    }
    //确定事件
    if(action_obnject->objectName()=="pushButton_Save"){
        ui->label_TipsText->setText("保存配置中请稍后!");
        if(vekAppConfigObj()){
            saveOptionData();
        }
        this->close();
    }
    //初始化
    /*
    if(action_obnject->objectName()=="pushButton_initDock"){
        if(ui->comboBox_dockbit->isEnabled()){
            if(pObject::vekMesg("强制初始化容器会导致部分软件无法运行和适配请慎重!")){
                ui->label_TipsText->setText("正在初始化容器请稍后!");
                forceInitDocer();
            }
        }else{
            if(pObject::vekMesg("是否解锁初始化功能限制请谨慎操作?")){
                ui->comboBox_dockbit->setEnabled(true);
                ui->comboBox_DockerName->setEnabled(true);
                ui->comboBox_dockSystemVersion->setEnabled(true);
            }
        }
    }
    */
}

void vekDockerOption::saveOptionData(){
    SappData* temAppData=new SappData();
    objectAppMT* vappAddObj=new objectAppMT(tempDockData,temAppData);
    vappAddObj->changeSettings(CHANGETYPE::CHANGETYPEDOCKER);
}
bool vekDockerOption::forceInitDocer(){
    if(!vekAppConfigObj()){
        return false;
    }
    SappData* temAppData=new SappData();
    objectAppMT* vappAddObj=new objectAppMT(tempDockData,temAppData);
    if(vappAddObj->InitDocker(true)){
        pObject::vekError("初始化失败!");
        return false;
    }else{
        pObject::saveDockerDataToJson(*tempDockData,tempDockData->s_dockers_name);
    }
    delete vappAddObj;
    vappAddObj=nullptr;
    return true;
}
