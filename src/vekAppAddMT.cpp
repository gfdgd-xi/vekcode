#include "vekAppAddMT.h"
#include "ui_common.h"

vekAppAddMT::vekAppAddMT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekAppAddMT)
{
    ui->setupUi(this);
    vek_Style(this,0);
    qwidgetGeometry(this);
}

vekAppAddMT::~vekAppAddMT()
{
    emit _unDiyAppAdd();
}
//绑定槽
void vekAppAddMT::vekAppAddConnectObject(BaseDockData* _data,QString _appCID,objectTypeView _objType){
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
    connect(ui->checkBox_dxvkConfigState,&QCheckBox::stateChanged,this,&vekAppAddMT::dxvkOptionLink);
    connect(ui->checkBox_stateDxvk,&QCheckBox::stateChanged,this,&vekAppAddMT::dxvkOptionLink);
    //显示当前安装wine
    ui->comboBox_RunWine->clear();
    if(!g_vekLocalData.wineVec.empty())
    {
        for(auto & x :g_vekLocalData.wineVec)
        {
            ui->comboBox_RunWine->addItem(x.first);
        }
        for(auto& d:g_vekLocalData.wineVec){
            for(auto& dx:d.second.IwineDxvk){
                ui->comboBox_dxvkversion->addItem(dx);
            }
        }
    }else{
        vekTip("请先安装Wine");
        this->close();
    }
    for(auto&y:_dockSystemVersion){
        ui->comboBox_dockSystemVersion->addItem(y);
    }
    //控件缺省设置
    ui->pushButton_setIco->setIconSize(QSize(80,80));
    ui->pushButton_setIco->setIcon(QIcon(":/res/img/vek.ico"));
    ui->lineEdit_RunDockPath->setText(QDir::currentPath()+"/vekDock");
    QStringList _tempDockName;
    if(!g_vekLocalData.dockerVec.empty()){
        for(auto &a:g_vekLocalData.dockerVec){
            _tempDockName.append(a.first);
        }
        _tempDockName = _tempDockName.toSet().toList();
        for(auto a:_tempDockName){
            ui->comboBox_DockName->addItem(a);
        }
    }else{
        ui->comboBox_DockName->setCurrentText("vekON1");
    }
    for(auto n:_dockVer){
        ui->comboBox_dockbit->addItem(n);
    }
    for(auto m:_dockWineVer){
        ui->comboBox_winebit->addItem(m);
    }
    for(auto a:_data->dData){
        if(a.first==_appCID){
            *tempAppData=a.second;
            break;
        }
    }
    if(tempAppData!=nullptr){
        ui->comboBox_RunWine->setCurrentIndex(ui->comboBox_RunWine->findText(_data->WineVersion));
        ui->comboBox_dockSystemVersion->setCurrentIndex(ui->comboBox_dockSystemVersion->findText(_data->DockerSystemVersion));
        //读取游戏名字
        ui->lineEdit_AppName->setText(tempAppData->AppName);
        //读取游戏安装路径
        ui->lineEdit_AppInstallExe->setText(tempAppData->AppExe);
        //读取容器路径
        ui->lineEdit_RunDockPath->setText(_data->DockerPath);
        //工作路径
        ui->lineEdit_workPath->setText(tempAppData->WorkPath);
        //容器名
        ui->comboBox_DockName->setCurrentText(_data->DockerName);
        //运行日志
        ui->checkBox_winerunlog->setChecked(tempAppData->TaskLog);
        ui->lineEdit_otherAgrs->setText(tempAppData->AppOtherAgrs);
        //dxvk配置文件
        ui->lineEdit_dxvkConfigFIle->setText(tempAppData->DxvkConfigFile);
        ui->checkBox_wineMemorySharing->setChecked(tempAppData->TaskMemorySharing);
        ui->checkBox_wineMemoryOptimization->setChecked(tempAppData->TaskMemoryOptimization);
        ui->checkBox_wineRealTimePriority->setChecked(tempAppData->TaskRealTimePriority);
        ui->checkBox_stateDxvk->setChecked(tempAppData->DxvkState);
        ui->comboBox_dxvkversion->setCurrentText(tempAppData->DxvkVerson);
        ui->checkBox_statedxvkhud->setChecked(tempAppData->DxvkHUD);
        ui->checkBox_DefaultFonts->setChecked(tempAppData->DefaultFonts);
        ui->checkBox_Mono->setChecked(_data->MonoState);
        ui->checkBox_Gecko->setChecked(_data->GeckoState);
        ui->lineEdit_MainProcName->setText(tempAppData->MainPrcoName);
        ui->checkBox_dxvkConfigState->setChecked(tempAppData->DxvkConfigFileState);
        ui->comboBox_dockbit->setCurrentText(_data->DockerVer);
        ui->comboBox_winebit->setCurrentText(_data->DockerWineVersion);
        ui->comboBox_dockbit->setEnabled(false);
    }else{
        dxvkOptionLink();
    }
    loadTableView(ui->tableView_EnvList,tempAppData);
    loadTableView(ui->tableView_ProcList,tempAppData);
    loadTableView(ui->tableView_RegsList,tempAppData);
    for(auto a:g_vekLocalData.wineVec){
        if(a.first==ui->comboBox_RunWine->currentText()){
            if(!QFile(a.second.IwinePath+"/plugs/Mono.msi").exists()){
                ui->checkBox_Mono->setEnabled(false);
            }
            if(!QFile(a.second.IwinePath+"/plugs/GeckoX86.msi").exists()&&!QFile(a.second.IwinePath+"/plugs/GeckoX86_64.msi").exists()){
                ui->checkBox_Gecko->setEnabled(false);
            }
            if(a.second.IwineDxvk.empty()){
                ui->checkBox_stateDxvk->setEnabled(false);
                ui->comboBox_dxvkversion->setEnabled(false);
                ui->checkBox_statedxvkhud->setEnabled(false);
                ui->lineEdit_dxvkConfigFIle->setEnabled(false);
            }
        }
    }
   temDockData=_data;
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
void vekAppAddMT::dxvkOptionLink(){
    dxvkOptionLinkState(false);
    if(ui->checkBox_stateDxvk->checkState()){
        dxvkOptionLinkState(true);
        if(ui->checkBox_dxvkConfigState->checkState()){
            QString dxvkPath;
            if(ui->lineEdit_dxvkConfigFIle->text()!=NULL)
            {
                dxvkPath=ui->lineEdit_dxvkConfigFIle->text();
            }
            else
            {
                for(auto a:g_vekLocalData.wineVec)
                {
                    if(a.second.IwineName==ui->comboBox_RunWine->currentText())
                    {
                        dxvkPath=a.second.IwinePath+"dxvk/dxvk.conf";
                        ui->lineEdit_dxvkConfigFIle->setText(dxvkPath);
                        break;
                    }
                }
            }
            ui->textEdit_dxvkConfigFileData->setText(getFileStr(dxvkPath));
        }
    }else{
        ui->checkBox_statedxvkhud->setChecked(false);
        ui->checkBox_dxvkConfigState->setChecked(false);
    }
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
void vekAppAddMT::loadTableView(QTableView* qtv,BaseAppData* ePdata){
    tableModel=new QStandardItemModel();
    // set columns
    int i=0;
    QStringList columnTitles;
    if(qtv==ui->tableView_EnvList){
        columnTitles << "环境变量名" << "环境变量值";

        if(ePdata!=nullptr){
            if(!ePdata->DockerEnv.empty()){
                for(auto &[k,j]:ePdata->DockerEnv){
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
            if(!ePdata->AttachProc.empty()){
                for(auto j:ePdata->AttachProc){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(j));
                }
            }
        }
    }
    if(qtv==ui->tableView_RegsList){
        columnTitles<<"注册表路径"<<"注册表键"<<"值类型"<<"注册表值";
        if(ePdata!=nullptr){
            if(!ePdata->DockerRegs.empty()){
                for(auto j:ePdata->DockerRegs){
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
    QTableView* _tempQTableView;
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
    if(tempAppData==nullptr){
        objectJson* _objectJson=new objectJson();
        tempAppData->AppCID=_objectJson->GetRandomCID();
        delete _objectJson;
        _objectJson=nullptr;
    }
    temDockData->WineVersion=ui->comboBox_RunWine->currentText();
    tempAppData->AppExe=ui->lineEdit_AppInstallExe->text();
    tempAppData->AppName=ui->lineEdit_AppName->text();
    tempAppData->WorkPath=ui->lineEdit_workPath->text();
    temDockData->DockerPath=QDir::currentPath()+"/vekDock";
    temDockData->DockerName="vekON1";
    tempAppData->AppOtherAgrs=ui->lineEdit_otherAgrs->text();
    temDockData->DockerSystemVersion=ui->comboBox_dockSystemVersion->currentText();
    //默认设置dockPath和dockName
    if(ui->lineEdit_RunDockPath->text()!=NULL){
        temDockData->DockerPath=ui->lineEdit_RunDockPath->text();
    }
    if(ui->comboBox_DockName->currentText()!=NULL){
        temDockData->DockerName=ui->comboBox_DockName->currentText();
    }
    if(ui->lineEdit_dxvkConfigFIle->text()!=NULL){
        tempAppData->DxvkConfigFile=ui->lineEdit_dxvkConfigFIle->text();
    }
    if(tempAppData->AppIco==NULL){
        tempAppData->AppIco=":/res/img/vek.ico";
    }
    //wine 参数
    for(auto &x : g_vekLocalData.wineVec){
        if(x.first==temDockData->WineVersion){
            temDockData->WineVersion=x.second.IwineName;
            temDockData->WinePath=x.second.IwinePath;
            break;
        }
    }
    temDockData->DockerVer=ui->comboBox_dockbit->currentText();
    temDockData->DockerWineVersion=ui->comboBox_winebit->currentText();
    //dxvk参数
    tempAppData->MainPrcoName=ui->lineEdit_MainProcName->text();
    tempAppData->DxvkState=ui->checkBox_stateDxvk->checkState();
    tempAppData->DxvkVerson=ui->comboBox_dxvkversion->currentText();
    tempAppData->DxvkHUD=ui->checkBox_statedxvkhud->checkState();
    tempAppData->DxvkConfigFileState=ui->checkBox_dxvkConfigState->checkState();
    tempAppData->DxvkConfigFile=ui->lineEdit_dxvkConfigFIle->text();
    //优化参数
    tempAppData->TaskLog=ui->checkBox_winerunlog->checkState();
    tempAppData->TaskMemorySharing=ui->checkBox_wineMemorySharing->checkState();
    tempAppData->TaskMemoryOptimization=ui->checkBox_wineMemoryOptimization->checkState();
    tempAppData->TaskRealTimePriority=ui->checkBox_wineRealTimePriority->checkState();
    tempAppData->DefaultFonts=ui->checkBox_DefaultFonts->checkState();
    temDockData->MonoState=ui->checkBox_Mono->checkState();
    temDockData->GeckoState=ui->checkBox_Gecko->checkState();
    int envCurRow=ui->tableView_EnvList->model()->rowCount();
    int procCurRow=ui->tableView_ProcList->model()->rowCount();
    int regsCurRow=ui->tableView_RegsList->model()->rowCount();
    if(envCurRow>0){
        tempAppData->DockerEnv.clear();
        QAbstractItemModel *modelEnv = ui->tableView_EnvList->model();
        for(int i=0;i<=envCurRow-1;i++){
            QString dataTempA = modelEnv->data(modelEnv->index(i,0)).value<QString>();
            QString dataTempB = modelEnv->data(modelEnv->index(i,1)).value<QString>();
            if(dataTempA!=NULL&dataTempB!=NULL){
                tempAppData->DockerEnv.insert(pair<QString,QString>(dataTempA,dataTempB));
            }
        }
    }
    if(procCurRow>0){
        tempAppData->AttachProc.clear();
        QAbstractItemModel *modelProc = ui->tableView_ProcList->model();
        for(int i=0;i<=procCurRow-1;i++){
            QString dataTempC = modelProc->data(modelProc->index(i,0)).value<QString>();
            qDebug()<<dataTempC;
            if(dataTempC!=NULL){
                tempAppData->AttachProc.push_back(dataTempC);
            }
        }
    }
    if(regsCurRow>0){
        tempAppData->DockerRegs.clear();
        BaseDockRegs _tRegs;
        QAbstractItemModel *modelRegs = ui->tableView_RegsList->model();
        for(int i=0;i<=regsCurRow-1;i++){
            _tRegs.rPath = modelRegs->data(modelRegs->index(i,0)).value<QString>();
            _tRegs.rKey = modelRegs->data(modelRegs->index(i,1)).value<QString>();
            _tRegs.rTValue= modelRegs->data(modelRegs->index(i,2)).value<QString>();
            _tRegs.rValue = modelRegs->data(modelRegs->index(i,3)).value<QString>();
            if(_tRegs.rPath!=NULL&_tRegs.rKey!=NULL&_tRegs.rTValue!=NULL){
                tempAppData->DockerRegs.push_back(_tRegs);
            }
        }
    }
    //检测必要参数
    if(temDockData->WineVersion==NULL){
        vekError("请先安装wine");
        return false;
    }
    if(tempAppData->AppName==NULL)
    {
        vekError("请填写游戏名");
        return false;
    }
    if(tempAppData->AppExe==NULL)
    {
        vekError("请设置游戏执行文件");
        return false;
    }
    if(tempAppData->WorkPath==NULL)
    {
        vekError("请设置游戏工作目录");
        return false;
    }
    if(temDockData->DockerPath==NULL)
    {
        vekError("请设置wine运行容器路径");
        return false;
    }
    if(temDockData->DockerName==NULL){
        vekError("请设置容器名字");
        return false;
    }
    if(tempAppData->MainPrcoName==NULL){
        vekError("主进程名不能为空");
        return false;
    }
    if(tempAppData->DxvkConfigFileState){
        if(tempAppData->DxvkConfigFile==NULL){
            vekError("启用dxvk配置文件功能后,必须指定dxvk配置文件路径");
            return false;
        }
    }
    //检测核心参数是否为NULL
    if(temDockData->WineVersion==NULL||temDockData->WinePath==NULL){
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
        if(strIco!=NULL){
            ui->pushButton_setIco->setIcon(QIcon(strIco));
        }else{
            ui->pushButton_setIco->setIcon(QIcon(":/res/img/vek.ico"));
        }
    }
    //设置游戏exe
    if(action_obnject->objectName()=="pushButton_SetAppExe"){
        QString exePath=QFileDialog::getOpenFileName(qwidget,"选择要添加的程序","","exe Files(*.exe)");
        if(exePath!=NULL){
            QFileInfo fi = QFileInfo(exePath);
            if(ui->lineEdit_AppName->text()==nullptr){
                ui->lineEdit_AppName->setText(fi.baseName());
            }
            ui->lineEdit_AppInstallExe->setText(exePath);
            ui->lineEdit_workPath->setText(fi.path());
        }
    }
    //设置工作目录
    if(action_obnject->objectName()=="pushButton_workPath"){
        QString workPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(workPath!=NULL){
            ui->lineEdit_workPath->setText(workPath);
        }
    }
    //设置DOCK路径
    if(action_obnject->objectName()=="pushButton_SetDockPath"){
        QString dockPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(dockPath!=NULL){
            ui->lineEdit_RunDockPath->setText(dockPath);
        }
    }
    //保存Save
    if(action_obnject->objectName()=="pushButton_SaveDxvkConfFile"){
        QString savePath=ui->lineEdit_dxvkConfigFIle->text();
        bool vekMesgDxvkSave=vekMesg("是否把dxvk配置文件保存到"+savePath);
        if(vekMesgDxvkSave)
        {
            if(QFile(savePath).exists()){
                if(vekMesg("是否覆盖"+savePath)){
                    QFile(savePath).remove();
                }else{
                    savePath = QFileDialog::getSaveFileName(this,tr("选择保存dxvk.conf路径"),".",tr("DxvkConf Files(*.conf)"));
                }
            }
        }else{
            savePath = QFileDialog::getSaveFileName(this,tr("选择保存dxvk.conf路径"),".",tr("DxvkConf Files(*.conf)"));
        }
        if(savePath!=NULL){
            ui->lineEdit_dxvkConfigFIle->setText(savePath);
            saveStrToFile(ui->textEdit_dxvkConfigFileData->toPlainText(),savePath);
            ui->lineEdit_dxvkConfigFIle->setText(savePath);
        }
    }
    //确定事件
    if(action_obnject->objectName()=="pushButton_Set"){
        ui->label_TipsText->setText("保存配置中请稍后!");
        if(vekAppAddObj(false)){
            emit doneAddApp(tempAppData);
            this->close();
        }
    }
    //初始化
    if(action_obnject->objectName()=="pushButton_initDock"){
        if(ui->comboBox_dockbit->isEnabled()){
            if(vekMesg("强制初始化容器会导致部分软件无法运行和适配请慎重!")){
                ui->label_TipsText->setText("正在初始化容器请稍后!");
                vekAppAddObj(true);
            }
        }else{
            if(vekMesg("是否解锁初始化功能限制请谨慎操作?")){
                ui->comboBox_dockbit->setEnabled(true);
            }
        }
    }
}

bool vekAppAddMT::vekAppAddObj(bool _forceState){
    if(!vekAppConfigObj()){
        return false;
    }
    objectAppMT* vappAddObj=new objectAppMT(tempAppData,temDockData);
    if(!vappAddObj->InitDockObj(_forceState)){
        vekError("初始化失败!");
    }else{
        vappAddObj->SaveDataToJson(temDockData->DockerName,*tempAppData);
    }
    emit _upData(tempAppData,objType);
    delete vappAddObj;
    vappAddObj=nullptr;
    return true;
}

