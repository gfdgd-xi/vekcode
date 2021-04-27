#include "vekAppAddMT.h"
#include "ui_common.h"

vekAppAddMT::vekAppAddMT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekAppAddMT)
{
    ui->setupUi(this);
    pObject::qwidgetGeometry(this);
}

vekAppAddMT::~vekAppAddMT()
{
    emit _unDiyAppAdd();
}
//绑定槽
void vekAppAddMT::vekAppAddConnectObject(SdockerData* _data,QString _appCID,EADEType _objType){
    objType=_objType;
    //检测增加游戏必要的设置
    connect(ui->pushButton_Set,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置游戏安装目录
    connect(ui->pushButton_SetAppExe,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置游戏安装目录
    connect(ui->pushButton_workPath,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置Wine容器目录
    connect(ui->pushButton_SetDockPath,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置ICO文件路径
    connect(ui->pushButton_setIco,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //init Dock
    connect(ui->pushButton_initDock,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    connect(ui->pushButton_SaveDxvkConfFile,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    connect(ui->checkBox_dxvkConfigState,&QCheckBox::stateChanged,this,&vekAppAddMT::dxvkOptionLoad);
    connect(ui->checkBox_stateDxvk,&QCheckBox::stateChanged,this,&vekAppAddMT::dxvkOptionLoad);
    connect(ui->comboBox_RunWine,&QComboBox::currentTextChanged,this,&vekAppAddMT::wineChanged);
    //显示当前安装wine
    ui->comboBox_RunWine->clear();
    if(!g_vekLocalData.map_wine_list.empty())
    {
        for(auto & x :g_vekLocalData.map_wine_list)
        {
            ui->comboBox_RunWine->addItem(x.first);
        }
        if(!g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_dxvk.empty()){
            for(auto& dx:g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_dxvk){
                ui->comboBox_dxvkversion->addItem(dx);
            }
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
            ui->comboBox_DockName->addItem(a.first);
        }
    }
    initAppAndDockData(_data,_appCID);
    //控件缺省设置
    ui->pushButton_setIco->setIconSize(QSize(80,80));
    ui->pushButton_setIco->setIcon(QIcon(tempAppData->s_ico));
    ui->lineEdit_RunDockPath->setText(tempDockData->s_dockers_path);
    ui->comboBox_DockName->setCurrentText(tempDockData->s_dockers_name);
    ui->comboBox_RunWine->setCurrentText(tempDockData->s_dockers_wine_version);  
    ui->checkBox_Mono->setChecked(tempDockData->s_dockers_mono_state);
    ui->checkBox_Gecko->setChecked(tempDockData->s_dockers_gecko_state);
    ui->comboBox_dockbit->setCurrentText(tempDockData->s_dockers_bit_version);
    ui->comboBox_winebit->setCurrentText(tempDockData->s_dockers_wine_exe_version);
    ui->comboBox_dockSystemVersion->setCurrentText(tempAppData->s_dock_system_version);
    ui->checkBox_Ass->setChecked(tempAppData->b_disable_ass);
    ui->lineEdit_AppName->setText(tempAppData->s_name);
    ui->lineEdit_AppInstallExe->setText(tempAppData->s_exe);
    ui->lineEdit_workPath->setText(tempAppData->s_work_path);
    ui->checkBox_winerunlog->setChecked(tempAppData->b_task_log);
    ui->lineEdit_otherAgrs->setText(tempAppData->s_agrs_code);
    ui->lineEdit_dxvkConfigFIle->setText(tempAppData->s_dxvk_config_file);
    ui->checkBox_wineMemorySharing->setChecked(tempAppData->b_sharedmemory);
    ui->checkBox_wineMemoryOptimization->setChecked(tempAppData->b_writecopy);
    ui->checkBox_wineRealTimePriority->setChecked(tempAppData->b_rtserver);
    ui->checkBox_stateDxvk->setChecked(tempAppData->b_dxvk_state);
    ui->comboBox_dxvkversion->setCurrentText(tempAppData->s_dxvk_version);
    ui->checkBox_statedxvkhud->setChecked(tempAppData->b_dxvk_hud);
    ui->checkBox_DefaultFonts->setChecked(tempAppData->b_default_fonts);
    ui->lineEdit_MainProcName->setText(tempAppData->s_main_proc_name);
    ui->checkBox_dxvkConfigState->setChecked(tempAppData->b_dxvk_config_file_state);
    if(objType==object_setApp){
        if(tempDockData->s_dockers_path!=nullptr){
            ui->comboBox_dockbit->setEnabled(false);
            ui->comboBox_DockName->setEnabled(false);
            ui->comboBox_dockSystemVersion->setEnabled(false);
        }
    }
    dxvkOptionLoad();
    loadTableView(ui->tableView_EnvList,tempAppData);
    loadTableView(ui->tableView_ProcList,tempAppData);
    loadTableView(ui->tableView_RegsList,tempAppData);
    plugsLoad();
}
void vekAppAddMT::initAppAndDockData(SdockerData* _data,QString _appCID){
    //_data nullptr =add
    if(_data->s_dockers_path==nullptr){
        tempDockData=new SdockerData;
        tempDockData->s_dockers_path=QApplication::applicationDirPath()+"/vekDock";
    }else{
        *tempDockData=pObject::getDockerData(_data->s_dockers_name);
        if(_appCID!=nullptr){
            auto it =tempDockData->map_dockers_data.find(_appCID);
            *tempAppData=it->second;
        }
    }
}
void vekAppAddMT::plugsLoad(){
    if(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_mono!=nullptr){
        if(!QFile(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_path+"/plugs/Mono.msi").exists()){
            ui->checkBox_Mono->setEnabled(false);
        }
    }
    if(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_mono!=nullptr){
        if(!QFile(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_path+"/plugs/GeckoX86.msi").exists()&&!QFile(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_path+"/plugs/GeckoX86_64.msi").exists()){
            ui->checkBox_Gecko->setEnabled(false);
        }
    }
    if(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_mono!=nullptr){
        if(!QFile(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_path+"/plugs/Mono.msi").exists()){
            ui->checkBox_Mono->setEnabled(false);
        }
    }
    if(g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_dxvk.empty()){
        ui->checkBox_stateDxvk->setEnabled(false);
        ui->comboBox_dxvkversion->setEnabled(false);
        ui->checkBox_statedxvkhud->setEnabled(false);
        ui->lineEdit_dxvkConfigFIle->setEnabled(false);
    }
}
void vekAppAddMT::dxvkOptionLinkState(bool cState){
    ui->comboBox_dxvkversion->setEnabled(cState);
    ui->checkBox_statedxvkhud->setEnabled(cState);
    ui->checkBox_dxvkConfigState->setEnabled(cState);
    ui->lineEdit_dxvkConfigFIle->clear();
    ui->textEdit_dxvkConfigFileData->clear();
    ui->lineEdit_dxvkConfigFIle->setEnabled(cState);
    ui->textEdit_dxvkConfigFileData->setEnabled(cState);
    ui->pushButton_SaveDxvkConfFile->setEnabled(cState);
}
void vekAppAddMT::dxvkOptionLoad(){
    dxvkOptionLinkState(false);
    if(ui->checkBox_stateDxvk->checkState()){
        dxvkOptionLinkState(true);
        if(ui->checkBox_dxvkConfigState->checkState()){
            QString dxvkPath;
            if(ui->lineEdit_dxvkConfigFIle->text()!=nullptr)
            {
                dxvkPath=ui->lineEdit_dxvkConfigFIle->text();
            }
            else
            {
                auto it=g_vekLocalData.map_wine_list.find(ui->comboBox_RunWine->currentText());
                dxvkPath=it->second.s_local_wine_path+"/dxvk/dxvk.conf";
                ui->lineEdit_dxvkConfigFIle->setText(dxvkPath);
            }
            ui->textEdit_dxvkConfigFileData->setText(pObject::getFileStr(dxvkPath));
        }
    }else{
        ui->checkBox_statedxvkhud->setChecked(false);
        ui->checkBox_dxvkConfigState->setChecked(false);
    }
}
void vekAppAddMT::wineChanged(){
    ui->comboBox_dxvkversion->clear();
    ui->comboBox_dockbit->clear();
    ui->comboBox_winebit->clear();
    if(!g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_dxvk.empty()){
        for(auto& dx:g_vekLocalData.map_wine_list[ui->comboBox_RunWine->currentText()].s_local_wine_dxvk){
            ui->comboBox_dxvkversion->addItem(dx);
        }
    }
    //deepin
    QStringList dWin;
    QStringList dWine;
    dWin<<"win32"<<"win64";
    dWine<<"wine"<<"wine64";
    ui->comboBox_dockbit->addItems(dWin);
    ui->comboBox_winebit->addItems(dWine);
    //winehq
    /*
    QStringList dWinhq;
    QStringList dWinehq;

    dWin<<"win32";
    dWinhq<<"win32"<<"win64";
    dWine<<"wine";
    dWinehq<<"wine"<<"wine64";
    if(ui->comboBox_RunWine->currentText().contains("deepin",Qt::CaseSensitive)){
        ui->comboBox_dockbit->addItems(dWin);
        ui->comboBox_winebit->addItems(dWine);
    }else{
        ui->comboBox_dockbit->addItems(dWinhq);
        ui->comboBox_winebit->addItems(dWinehq);
    }
    */
}
//SetTable
void vekAppAddMT::setTableView(QTableView* qtv){
    qtv->setSelectionBehavior(QAbstractItemView::SelectRows);
    qtv->setSelectionMode(QAbstractItemView::SingleSelection);
    qtv->setSortingEnabled(false);
    qtv->verticalHeader()->hide();
    qtv->setWordWrap(false);
    qtv->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    qtv->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    qtv->setShowGrid(false);
    //ui->tableView_WineSrcList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtv->setAlternatingRowColors(true);  // alternative colors
    qtv->setFrameShape(QFrame::NoFrame);
    qtv->horizontalHeader()->setStretchLastSection(true);
    qtv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
//loadTable
void vekAppAddMT::loadTableView(QTableView* qtv,SappData* ePdata){
    tableModel=new QStandardItemModel();
    // set columns
    int i=0;
    QStringList columnTitles;
    if(qtv==ui->tableView_EnvList){
        columnTitles << "环境变量名" << "环境变量值";

        if(ePdata!=nullptr){
            if(!ePdata->map_docker_regs.empty()){
                for(auto &[k,j]:ePdata->map_docker_regs){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(k));
                    tableModel->setItem(x,1,new QStandardItem(j));
                }
            }
        }
    }
    if(qtv==ui->tableView_ProcList){
        columnTitles <<"附加进程名";
        if(ePdata!=nullptr)
        {
            if(!ePdata->vec_proc_attach_list.empty()){
                for(auto j:ePdata->vec_proc_attach_list){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(j));
                }
            }
        }
    }
    if(qtv==ui->tableView_RegsList){
        columnTitles<<"注册表路径"<<"注册表键"<<"值类型"<<"注册表值";
        if(ePdata!=nullptr){
            if(!ePdata->vec_docker_regs.empty()){
                for(auto j:ePdata->vec_docker_regs){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(j.rPath));
                    tableModel->setItem(x,1,new QStandardItem(j.rKey));
                    tableModel->setItem(x,2,new QStandardItem(j.rTValue));
                    tableModel->setItem(x,3,new QStandardItem(j.rValue));
                }
            }
        }
    }
    setTableView(qtv);
    qtv->setModel(tableModel);
    tableModel->setHorizontalHeaderLabels(columnTitles);
    qtv->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(qtv,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clicked_rightMenu(QPoint)));
}
void vekAppAddMT::clicked_rightMenu(const QPoint &/*pos*/)
{
    QTableView* signalSrc = (QTableView*)sender();  // 获取到了发送该信号按钮的指针
    //创建菜单对象
    QMenu *pMenu = new QMenu(this);
    QAction *pNewTask = new QAction(tr("新建"), this);
    QAction *pDeleteTask = new QAction(tr("删除"), this);
    pNewTask->setData(1);
    pDeleteTask ->setData(2);
    pNewTask->setObjectName(signalSrc->objectName());
    pDeleteTask->setObjectName(signalSrc->objectName());
    //把QAction对象添加到菜单上
    pMenu->addAction(pNewTask);
    pMenu->addAction(pDeleteTask);
    //连接鼠标右键点击信号
    connect(pNewTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pDeleteTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    //在鼠标右键点击的地方显示菜单
    pMenu->exec(QCursor::pos());
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}
void vekAppAddMT::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender());
    int iType = pEven->data().toInt();
    QTableView* _tempQTableView=new QTableView;
    if(pEven->objectName()=="tableView_EnvList"){
        _tempQTableView=ui->tableView_EnvList;
    }else if(pEven->objectName()=="tableView_ProcList"){
        _tempQTableView=ui->tableView_ProcList;
    }else if(pEven->objectName()=="tableView_RegsList"){
        _tempQTableView=ui->tableView_RegsList;
    }
    switch (iType)
    {
    case 1:
        objectAdd(_tempQTableView);
        break;
    case 2:
        objectDelete(_tempQTableView);
        break;
    default:
        break;
    }
}
void vekAppAddMT::objectAdd(QTableView* qTableView){
    QAbstractItemModel *modessl = qTableView->model();
    modessl->insertRow(modessl->rowCount());
    qTableView->setModel(modessl);
}
void vekAppAddMT::objectDelete(QTableView* qTableView){
    int curRow=qTableView->currentIndex().row();
    int curRows = qTableView->model()->rowCount();
    if(curRows==0){
        return;
    }
    if(curRow > -1){
        QAbstractItemModel *modessl = qTableView->model();
        QModelIndex indextemp = modessl->index(curRow,0);
        QString datatemp = modessl->data(indextemp).value<QString>();
        modessl->removeRow(curRow);
        qTableView->setModel(modessl);
    }
}
//控件数据to Class
bool vekAppAddMT::vekAppConfigObj(){  
    if(tempAppData->s_uid==nullptr){
        objectJson _objectJson;
        tempAppData->s_uid=_objectJson.GetRandomCID();
    }
    tempAppData->s_exe=ui->lineEdit_AppInstallExe->text();
    tempAppData->s_name=ui->lineEdit_AppName->text();
    tempAppData->s_work_path=ui->lineEdit_workPath->text();
    tempAppData->s_agrs_code=ui->lineEdit_otherAgrs->text();
    //Docker默认参数

    if(ui->lineEdit_RunDockPath->text()!=nullptr){
        tempDockData->s_dockers_path=ui->lineEdit_RunDockPath->text();
    }else{
        tempDockData->s_dockers_path=QApplication::applicationDirPath()+"/vekDock";
    }
    if(ui->comboBox_DockName->currentText()!=nullptr){
        tempDockData->s_dockers_name=ui->comboBox_DockName->currentText();
    }else{
        tempDockData->s_dockers_name="vekON1";
    }
    tempDockData->s_dockers_wine_version=ui->comboBox_RunWine->currentText();
    auto it=g_vekLocalData.map_wine_list.find(ui->comboBox_RunWine->currentText());
    tempDockData->s_dockers_wine_path=it->second.s_local_wine_path;
    tempDockData->s_dockers_system_version=ui->comboBox_dockSystemVersion->currentText();
    tempDockData->s_dockers_bit_version=ui->comboBox_dockbit->currentText();
    tempDockData->s_dockers_wine_exe_version=ui->comboBox_winebit->currentText();
    tempDockData->s_dockers_mono_state=ui->checkBox_Mono->checkState();
    tempDockData->s_dockers_gecko_state=ui->checkBox_Gecko->checkState();
    tempAppData->b_disable_ass=ui->checkBox_Ass->checkState();
    if(ui->lineEdit_dxvkConfigFIle->text()!=nullptr){
        tempAppData->s_dxvk_config_file=ui->lineEdit_dxvkConfigFIle->text();
    }
    if(tempAppData->s_ico==nullptr){
        tempAppData->s_ico=":/res/img/vek.ico";
    }
    //dxvk参数
    tempAppData->s_dock_system_version=ui->comboBox_dockSystemVersion->currentText();
    tempAppData->s_main_proc_name=ui->lineEdit_MainProcName->text();
    tempAppData->b_dxvk_state=ui->checkBox_stateDxvk->checkState();
    tempAppData->s_dxvk_version=ui->comboBox_dxvkversion->currentText();
    tempAppData->b_dxvk_hud=ui->checkBox_statedxvkhud->checkState();
    tempAppData->b_dxvk_config_file_state=ui->checkBox_dxvkConfigState->checkState();
    tempAppData->s_dxvk_config_file=ui->lineEdit_dxvkConfigFIle->text();
    //优化参数
    tempAppData->b_task_log=ui->checkBox_winerunlog->checkState();
    tempAppData->b_sharedmemory=ui->checkBox_wineMemorySharing->checkState();
    tempAppData->b_writecopy=ui->checkBox_wineMemoryOptimization->checkState();
    tempAppData->b_rtserver=ui->checkBox_wineRealTimePriority->checkState();
    tempAppData->b_default_fonts=ui->checkBox_DefaultFonts->checkState();
    int envCurRow=ui->tableView_EnvList->model()->rowCount();
    int procCurRow=ui->tableView_ProcList->model()->rowCount();
    int regsCurRow=ui->tableView_RegsList->model()->rowCount();
    if(envCurRow>0){
        tempAppData->map_docker_regs.clear();
        QAbstractItemModel *modelEnv = ui->tableView_EnvList->model();
        for(int i=0;i<=envCurRow-1;i++){
            QString dataTempA = modelEnv->data(modelEnv->index(i,0)).value<QString>();
            QString dataTempB = modelEnv->data(modelEnv->index(i,1)).value<QString>();
            if(dataTempA!=nullptr&&dataTempB!=nullptr){
                tempAppData->map_docker_regs.insert(pair<QString,QString>(dataTempA,dataTempB));
            }
        }
    }
    if(procCurRow>0){
        tempAppData->vec_proc_attach_list.clear();
        QAbstractItemModel *modelProc = ui->tableView_ProcList->model();
        for(int i=0;i<=procCurRow-1;i++){
            QString dataTempC = modelProc->data(modelProc->index(i,0)).value<QString>();
            qInfo()<<dataTempC;
            if(dataTempC!=nullptr){
                tempAppData->vec_proc_attach_list.push_back(dataTempC);
            }
        }
    }
    if(regsCurRow>0){
        tempAppData->vec_docker_regs.clear();
        SRegs _tRegs;
        QAbstractItemModel *modelRegs = ui->tableView_RegsList->model();
        for(int i=0;i<=regsCurRow-1;i++){
            _tRegs.rPath = modelRegs->data(modelRegs->index(i,0)).value<QString>();
            _tRegs.rKey = modelRegs->data(modelRegs->index(i,1)).value<QString>();
            _tRegs.rTValue= modelRegs->data(modelRegs->index(i,2)).value<QString>();
            _tRegs.rValue = modelRegs->data(modelRegs->index(i,3)).value<QString>();
            if(_tRegs.rPath!=nullptr&&_tRegs.rKey!=nullptr&&_tRegs.rTValue!=nullptr){
                tempAppData->vec_docker_regs.push_back(_tRegs);
            }
        }
    }
    return checkAllOption();
}
//检查所有必备参数
bool vekAppAddMT::checkAllOption(){
    if(!checkAppOption()){
        return false;
    }
    if(!checkDocerOption()){
        return false;
    }
    if(!checkDxvkOption()){
        return false;
    }
    return true;
}
//检查dxvk参数
bool vekAppAddMT::checkDxvkOption(){
    bool dxvkState=true;
    if(tempAppData->b_dxvk_config_file_state){
        if(tempAppData->s_dxvk_config_file==nullptr){
            pObject::vekError("启用dxvk配置文件功能后,必须指定dxvk配置文件路径");
            dxvkState=false;
        }
    }
    qInfo()<<"dxvk参数"<<dxvkState;
    return dxvkState;
}
//检查App参数
bool vekAppAddMT::checkAppOption(){
    if(tempAppData->s_name==nullptr)
    {
        pObject::vekError("请填写游戏名");
        return false;
    }
    if(tempAppData->s_exe==nullptr)
    {
        pObject::vekError("请设置游戏执行文件");
        return false;
    }
    if(tempAppData->s_work_path==nullptr)
    {
        pObject::vekError("请设置游戏工作目录");
        return false;
    }

    if(tempAppData->s_main_proc_name==nullptr){
        pObject::vekError("主进程名不能为空");
        return false;
    }
    return true;
}
//检查docker参数
//2021-3-18增加对deepin-wine5在64位容器的隔离
//2021-4-25取消对deepin-wine5的隔离且支持deepin-wine5容器
bool vekAppAddMT::checkDocerOption(){
    if(tempDockData->s_dockers_wine_version==nullptr){
        pObject::vekError("请先安装wine");
        return false;
    }
    /*
    if(tempDockData->s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
        if(tempDockData->s_dockers_bit_version=="win64"){
            pObject::vekError("Deepin-Wine5不支持64位容器");
            return false;
        }
    }
    */
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
void vekAppAddMT::objectButton(){
    QObject *object = QObject::sender();
    QPushButton *action_obnject = qobject_cast<QPushButton *>(object);
    QWidget *qwidget = new QWidget();
    //设置游戏ico
    if(action_obnject->objectName()=="pushButton_setIco"){
        QString strIco=QFileDialog::getOpenFileName(qwidget,"选择游戏图标","","Ico Files(*.ico);;PNG Files(*.png);;JPEG Files(*.jpeg)");
        if(strIco!=nullptr){
            ui->pushButton_setIco->setIcon(QIcon(strIco));
        }else{
            ui->pushButton_setIco->setIcon(QIcon(":/res/img/vek.ico"));
        }
    }
    //设置游戏exe
    if(action_obnject->objectName()=="pushButton_SetAppExe"){
        QString exePath=QFileDialog::getOpenFileName(qwidget,"选择要添加的程序","","exe Files(*.exe)");
        if(exePath!=nullptr){
            QFileInfo fi = QFileInfo(exePath);
            if(ui->lineEdit_AppName->text()==nullptr){
                ui->lineEdit_AppName->setText(fi.baseName());
                ui->lineEdit_MainProcName->setText(fi.fileName());
            }
            ui->lineEdit_AppInstallExe->setText(exePath);
            ui->lineEdit_workPath->setText(fi.path());
        }
    }
    //设置工作目录
    if(action_obnject->objectName()=="pushButton_workPath"){
        QString workPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(workPath!=nullptr){
            ui->lineEdit_workPath->setText(workPath);
        }
    }
    //设置DOCK路径
    if(action_obnject->objectName()=="pushButton_SetDockPath"){
        QString dockPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(dockPath!=nullptr){
            ui->lineEdit_RunDockPath->setText(dockPath);
        }
    }
    //保存Save
    if(action_obnject->objectName()=="pushButton_SaveDxvkConfFile"){
        QString savePath=ui->lineEdit_dxvkConfigFIle->text();
        bool vekMesgDxvkSave=pObject::vekMesg("是否把dxvk配置文件保存到"+savePath);
        if(vekMesgDxvkSave)
        {
            if(QFile(savePath).exists()){
                if(pObject::vekMesg("是否覆盖"+savePath)){
                    QFile(savePath).remove();
                }else{
                    savePath = QFileDialog::getSaveFileName(this,tr("选择保存dxvk.conf路径"),".",tr("DxvkConf Files(*.conf)"));
                }
            }
        }else{
            savePath = QFileDialog::getSaveFileName(this,tr("选择保存dxvk.conf路径"),".",tr("DxvkConf Files(*.conf)"));
        }
        if(savePath!=nullptr){
            ui->lineEdit_dxvkConfigFIle->setText(savePath);
            pObject::saveStrToFile(ui->textEdit_dxvkConfigFileData->toPlainText(),savePath);
            ui->lineEdit_dxvkConfigFIle->setText(savePath);
        }
    }
    //确定事件
    if(action_obnject->objectName()=="pushButton_Set"){
        ui->label_TipsText->setText("保存配置中请稍后!");
        if(vekAppAddObj(false)){
            emit doneAddApp(tempDockData,tempAppData);
            this->close();
        }
    }
    //初始化
    if(action_obnject->objectName()=="pushButton_initDock"){
        if(ui->comboBox_dockbit->isEnabled()){
            if(pObject::vekMesg("强制初始化容器会导致部分软件无法运行和适配请慎重!")){
                ui->label_TipsText->setText("正在初始化容器请稍后!");
                vekAppAddObj(true);
            }
        }else{
            if(pObject::vekMesg("是否解锁初始化功能限制请谨慎操作?")){
                ui->comboBox_dockbit->setEnabled(true);
                ui->comboBox_DockName->setEnabled(true);
                ui->comboBox_dockSystemVersion->setEnabled(true);
            }
        }
    }
}

bool vekAppAddMT::vekAppAddObj(bool _forceState){
    if(!vekAppConfigObj()){
        return false;
    }
    objectAppMT* vappAddObj=new objectAppMT(tempAppData,tempDockData);
    if(!vappAddObj->InitDockObj(_forceState)){
        pObject::vekError("初始化失败!");
        return false;
    }else{
        pObject::addAppDataToJson(*tempDockData,*tempAppData);
    }
    if(objType==object_setApp){
        emit _upData(*tempDockData,tempAppData,objType);
    }
    delete vappAddObj;
    vappAddObj=nullptr;
    return true;
}

