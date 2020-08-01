#include "vekGameAddMT.h"
#include "ui_common.h"
#include "vekInitObject.h"

vekGameAddMT::vekGameAddMT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekGameAddMT)
{
    ui->setupUi(this);
    vek_Style(this,0);
    qwidgetGeometry(this);
}

vekGameAddMT::~vekGameAddMT()
{
    emit _unDiyGameAdd();
}
//绑定槽
void vekGameAddMT::vekGameAddConnectObject(BaseGameData* _data,objectTypeView _objType){
    objType=_objType;
    //检测增加游戏必要的设置
    connect(ui->pushButton_Set,&QPushButton::clicked,this,&vekGameAddMT::objectButton);
    //设置游戏安装目录
    connect(ui->pushButton_SetGameExe,&QPushButton::clicked,this,&vekGameAddMT::objectButton);
    //设置游戏安装目录
    connect(ui->pushButton_workPath,&QPushButton::clicked,this,&vekGameAddMT::objectButton);
    //设置Wine容器目录
    connect(ui->pushButton_SetDockPath,&QPushButton::clicked,this,&vekGameAddMT::objectButton);
    //设置ICO文件路径
    connect(ui->pushButton_setIco,&QPushButton::clicked,this,&vekGameAddMT::objectButton);
    //init Dock
    connect(ui->pushButton_initDock,&QPushButton::clicked,this,&vekGameAddMT::objectButton);
    connect(ui->pushButton_SaveDxvkConfFile,&QPushButton::clicked,this,&vekGameAddMT::objectButton);
    connect(ui->checkBox_dxvkConfigState,&QCheckBox::stateChanged,this,&vekGameAddMT::dxvkOptionLink);
    connect(ui->checkBox_stateDxvk,&QCheckBox::stateChanged,this,&vekGameAddMT::dxvkOptionLink);
    //显示当前安装wine
    ui->comboBox_RunWine->clear();
    if(!g_vekLocalData.wineVec.empty())
    {
        for(auto & x :g_vekLocalData.wineVec)
        {
            ui->comboBox_RunWine->addItem(x.first);
        }
        for(auto& d:g_vekLocalData.wineVec){
            for(auto& dx:d.second.wineInstallDxvk){
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
    if(_data!=nullptr){
        //读取配置修改设置
        oldData=_data;
        tempCID=_data->gameCID;
        ui->comboBox_RunWine->setCurrentIndex(ui->comboBox_RunWine->findText(_data->wineVersion));
        ui->comboBox_dockSystemVersion->setCurrentIndex(ui->comboBox_dockSystemVersion->findText(_data->dockSystemVersion));
        //读取游戏名字
        ui->lineEdit_GameName->setText(_data->gameName);
        //读取游戏安装路径
        ui->lineEdit_GameInstallExe->setText(_data->gameExe);
        //读取容器路径
        ui->lineEdit_RunDockPath->setText(_data->dockPath);
        //工作路径
        ui->lineEdit_workPath->setText(_data->workPath);
        //容器名
        ui->comboBox_DockName->setCurrentText(_data->dockName);
        //运行日志
        ui->checkBox_winerunlog->setChecked(_data->taskLog);
        ui->lineEdit_otherAgrs->setText(_data->gameOtherAgrs);
        //dxvk配置文件
        ui->lineEdit_dxvkConfigFIle->setText(_data->dxvkConfigFile);
        ui->checkBox_wineMemorySharing->setChecked(_data->taskMemorySharing);
        ui->checkBox_wineMemoryOptimization->setChecked(_data->taskMemoryOptimization);
        ui->checkBox_wineRealTimePriority->setChecked(_data->taskRealTimePriority);
        ui->checkBox_stateDxvk->setChecked(_data->dxvkState);
        ui->comboBox_dxvkversion->setCurrentText(_data->dxvkVerson);
        ui->checkBox_statedxvkhud->setChecked(_data->dxvkHUD);
        ui->checkBox_DefaultFonts->setChecked(_data->defaultFonts);
        ui->checkBox_Mono->setChecked(_data->monoState);
        ui->checkBox_Gecko->setChecked(_data->geckoState);
        ui->lineEdit_MainProcName->setText(_data->mainPrcoName);
        ui->checkBox_dxvkConfigState->setChecked(_data->dxvkConfigFileState);
    }else{
        dxvkOptionLink();
    }
    loadTableView(ui->tableView_EnvList,_data);
    loadTableView(ui->tableView_ProcList,_data);
    loadTableView(ui->tableView_RegsList,_data);  
    for(auto a:g_vekLocalData.wineVec){
        if(a.first==ui->comboBox_RunWine->currentText()){
            if(!QFile(a.second.wineInstallPath+"/plugs/Mono.msi").exists()){
                ui->checkBox_Mono->setEnabled(false);
            }
            if(!QFile(a.second.wineInstallPath+"/plugs/GeckoX86.msi").exists()&&!QFile(a.second.wineInstallPath+"/plugs/GeckoX86_64.msi").exists()){
                ui->checkBox_Gecko->setEnabled(false);
            }
            if(a.second.wineInstallDxvk.empty()){
                ui->checkBox_stateDxvk->setEnabled(false);
                ui->comboBox_dxvkversion->setEnabled(false);
                ui->checkBox_statedxvkhud->setEnabled(false);
                ui->lineEdit_dxvkConfigFIle->setEnabled(false);
            }
        }
    }
}
void vekGameAddMT::dxvkOptionLinkState(bool cState){
    ui->comboBox_dxvkversion->setEnabled(cState);
    ui->checkBox_statedxvkhud->setEnabled(cState);
    ui->checkBox_dxvkConfigState->setEnabled(cState);
    ui->lineEdit_dxvkConfigFIle->clear();
    ui->textEdit_dxvkConfigFileData->clear();
    ui->lineEdit_dxvkConfigFIle->setEnabled(cState);
    ui->textEdit_dxvkConfigFileData->setEnabled(cState);
    ui->pushButton_SaveDxvkConfFile->setEnabled(cState);

}
void vekGameAddMT::dxvkOptionLink(){
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
                    if(a.second.WineInstallName==ui->comboBox_RunWine->currentText())
                    {
                        dxvkPath=a.second.wineInstallPath+"dxvk/dxvk.conf";
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
void vekGameAddMT::setTableView(QTableView* qtv){
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
void vekGameAddMT::loadTableView(QTableView* qtv,BaseGameData* ePdata){
    tableModel=new QStandardItemModel();
    // set columns
    int i=0;
    QStringList columnTitles;
    if(qtv==ui->tableView_EnvList){
        columnTitles << "环境变量名" << "环境变量值";

        if(ePdata!=nullptr){
            if(!ePdata->dockEnv.empty()){
                for(auto &[k,j]:ePdata->dockEnv){
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
            if(!ePdata->attachProc.empty()){
                for(auto j:ePdata->attachProc){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(j));
                }
            }
        }
    }
    if(qtv==ui->tableView_RegsList){
        columnTitles<<"注册表路径"<<"注册表键"<<"值类型"<<"注册表值";
        if(ePdata!=nullptr){
            if(!ePdata->dockRegs.empty()){
                for(auto j:ePdata->dockRegs){
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
void vekGameAddMT::clicked_rightMenu(const QPoint &/*pos*/)
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
void vekGameAddMT::onTaskBoxContextMenuEvent()
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
void vekGameAddMT::objectAdd(QTableView* qTableView){
    QAbstractItemModel *modessl = qTableView->model();
    modessl->insertRow(modessl->rowCount());
    qTableView->setModel(modessl);
}
void vekGameAddMT::objectDelete(QTableView* qTableView){
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
bool vekGameAddMT::vekGameConfigObj(){
    if(tempData!=nullptr){
        tempData=nullptr;
    }
    tempData=new BaseGameData();
    if(tempCID!=NULL){
        tempData->gameCID=tempCID;
    }else{
        objectJson* _objectJson=new objectJson();
        tempData->gameCID=_objectJson->GetRandomCID();
        tempCID=tempData->gameCID;
        delete _objectJson;
        _objectJson=nullptr;
    }
    tempData->wineVersion=ui->comboBox_RunWine->currentText();
    tempData->gameExe=ui->lineEdit_GameInstallExe->text();
    tempData->gameName=ui->lineEdit_GameName->text();
    tempData->workPath=ui->lineEdit_workPath->text();
    tempData->dockPath=QDir::currentPath()+"/vekDock";
    tempData->dockName="vekON1";
    tempData->gameOtherAgrs=ui->lineEdit_otherAgrs->text();
    tempData->dockSystemVersion=ui->comboBox_dockSystemVersion->currentText();
    //默认设置dockPath和dockName
    if(ui->lineEdit_RunDockPath->text()!=NULL){
        tempData->dockPath=ui->lineEdit_RunDockPath->text();
    }
    if(ui->comboBox_DockName->currentText()!=NULL){
        tempData->dockName=ui->comboBox_DockName->currentText();
    }
    if(ui->lineEdit_dxvkConfigFIle->text()!=NULL){
        tempData->dxvkConfigFile=ui->lineEdit_dxvkConfigFIle->text();
    }
    if(tempData->gameIco==NULL){
        tempData->gameIco=":/res/img/vek.ico";
    }
    //wine 参数
    for(auto &x : g_vekLocalData.wineVec){
        if(x.first==tempData->wineVersion){
            tempData->wineVersion=x.second.WineInstallName;
            tempData->winePath=x.second.wineInstallPath;
            break;
        }
    }
    //dxvk参数
    tempData->mainPrcoName=ui->lineEdit_MainProcName->text();
    tempData->dxvkState=ui->checkBox_stateDxvk->checkState();
    tempData->dxvkVerson=ui->comboBox_dxvkversion->currentText();
    tempData->dxvkHUD=ui->checkBox_statedxvkhud->checkState();
    tempData->dxvkConfigFileState=ui->checkBox_dxvkConfigState->checkState();    
    tempData->dxvkConfigFile=ui->lineEdit_dxvkConfigFIle->text();
    //优化参数
    tempData->taskLog=ui->checkBox_winerunlog->checkState();
    tempData->taskMemorySharing=ui->checkBox_wineMemorySharing->checkState();
    tempData->taskMemoryOptimization=ui->checkBox_wineMemoryOptimization->checkState();
    tempData->taskRealTimePriority=ui->checkBox_wineRealTimePriority->checkState();
    tempData->defaultFonts=ui->checkBox_DefaultFonts->checkState();
    tempData->monoState=ui->checkBox_Mono->checkState();
    tempData->geckoState=ui->checkBox_Gecko->checkState();
    int envCurRow=ui->tableView_EnvList->model()->rowCount();
    int procCurRow=ui->tableView_ProcList->model()->rowCount();
    int regsCurRow=ui->tableView_RegsList->model()->rowCount();
    if(envCurRow>0){
        tempData->dockEnv.clear();
        QAbstractItemModel *modelEnv = ui->tableView_EnvList->model();
        for(int i=0;i<=envCurRow-1;i++){
            QString dataTempA = modelEnv->data(modelEnv->index(i,0)).value<QString>();
            QString dataTempB = modelEnv->data(modelEnv->index(i,1)).value<QString>();
            if(dataTempA!=NULL&dataTempB!=NULL){
                tempData->dockEnv.insert(pair<QString,QString>(dataTempA,dataTempB));
            }
        }
    }
    if(procCurRow>0){
        tempData->attachProc.clear();
        QAbstractItemModel *modelProc = ui->tableView_ProcList->model();
        for(int i=0;i<=procCurRow-1;i++){
            QString dataTempC = modelProc->data(modelProc->index(i,0)).value<QString>();
            qDebug()<<dataTempC;
            if(dataTempC!=NULL){
                tempData->attachProc.push_back(dataTempC);
            }
        }
    }
    if(regsCurRow>0){
        tempData->dockRegs.clear();
        BaseDockRegs _tRegs;
        QAbstractItemModel *modelRegs = ui->tableView_RegsList->model();
        for(int i=0;i<=regsCurRow-1;i++){
            _tRegs.rPath = modelRegs->data(modelRegs->index(i,0)).value<QString>();
            _tRegs.rKey = modelRegs->data(modelRegs->index(i,1)).value<QString>();
            _tRegs.rTValue= modelRegs->data(modelRegs->index(i,2)).value<QString>();
            _tRegs.rValue = modelRegs->data(modelRegs->index(i,3)).value<QString>();
            if(_tRegs.rPath!=NULL&_tRegs.rKey!=NULL&_tRegs.rTValue!=NULL){
                tempData->dockRegs.push_back(_tRegs);
            }
        }
    }
    //检测必要参数
    if(tempData->wineVersion==NULL){
        vekError("请先安装wine");
        return false;
    }
    if(tempData->gameName==NULL)
    {
        vekError("请填写游戏名");
        return false;
    }
    if(tempData->gameExe==NULL)
    {
        vekError("请设置游戏执行文件");
        return false;
    }
    if(tempData->workPath==NULL)
    {
        vekError("请设置游戏工作目录");
        return false;
    }
    if(tempData->dockPath==NULL)
    {
        vekError("请设置wine运行容器路径");
        return false;
    }
    if(tempData->dockName==NULL){
        vekError("请设置容器名字");
        return false;
    }
    if(tempData->mainPrcoName==NULL){
        vekError("主进程名不能为空");
        return false;
    }
    if(tempData->dxvkConfigFileState){
        if(tempData->dxvkConfigFile==NULL){
            vekError("启用dxvk配置文件功能后,必须指定dxvk配置文件路径");
            return false;
        }
    }
    //检测核心参数是否为NULL
    if(tempData->wineVersion==NULL||tempData->winePath==NULL){
        return false;
    }

    return true;
}
//按钮事件集中处理
void vekGameAddMT::objectButton(){
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
    if(action_obnject->objectName()=="pushButton_SetGameExe"){
        QString exePath=QFileDialog::getOpenFileName(qwidget,"选择要添加的程序","","exe Files(*.exe)");
        if(exePath!=NULL){
            QFileInfo fi = QFileInfo(exePath);
            if(ui->lineEdit_GameName->text()==nullptr){
                ui->lineEdit_GameName->setText(fi.baseName());
            }
            ui->lineEdit_GameInstallExe->setText(exePath);
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
        if(vekGameAddObj(false)){
            emit doneAddGame(tempData);
            this->close();
        }
    }
    //初始化
    if(action_obnject->objectName()=="pushButton_initDock"){
        ui->label_TipsText->setText("正在初始化容器请稍后!");
        vekGameAddObj(true);
    }
}

bool vekGameAddMT::vekGameAddObj(bool _forceState){
    if(!vekGameConfigObj()){
        return false;
    }
    objectAddGameMT* vGameAddObj=new objectAddGameMT(tempData,oldData);
    if(!vGameAddObj->InitDockObj(_forceState)){
        vekError("初始化失败!");
    }else{
        vGameAddObj->SaveDataToJson(tempData->dockName,*tempData);
    }
    emit _upData(tempData,objType);
    delete vGameAddObj;
    vGameAddObj=nullptr;
    return true;
}

