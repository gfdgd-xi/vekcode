#include "vekWineOption.h"
#include "ui_common.h"
#include "obj/pObject.h"

vekWineOption::vekWineOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekWineOption)
{
    ui->setupUi(this);
    connect(ui->toolButton_SetInstallDir,&QPushButton::clicked,this,&vekWineOption::on_toolButton);
    connect(ui->comboBox_wineSrc,&QComboBox::currentTextChanged,this,&vekWineOption::wineVersionComoboBox);
}

vekWineOption::~vekWineOption()
{
    delete ui;
    emit _unInitWineOption();
}
void vekWineOption::loadWineData(){
    loadWineList(ui->tableView_winen);
    loadWineList(ui->tableView_wined);
}
void vekWineOption::loadWineList(QTableView* qTableView){
    QStringList columnTitles;
    qTableView->disconnect(SIGNAL(customContextMenuRequested(QPoint)));
    ItemModelWine = new QStandardItemModel();
    if(qTableView==ui->tableView_winen){
        columnTitles << "当前源提供Wine版本列表";
        if(!g_vekLocalData.wineJsonList.empty()){
            for(auto &d : g_vekLocalData.wineJsonList){
                if(d.first==ui->comboBox_wineSrc->currentText()){
                    for(auto &x:d.second){
                        ItemModelWine->appendRow(new QStandardItem(x.second.s_remote_wine_name));
                    }
                }
            }
        }
    }else{
        columnTitles << "已安装Wine版本列表";
        if(!g_vekLocalData.wineVec.empty()){
            for(auto &d : g_vekLocalData.wineVec){
                ItemModelWine->appendRow(new QStandardItem(d.second.s_wine_name));
            }
        }
    }
    qTableView->setModel(ItemModelWine);
    qTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    qTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    qTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    qTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(qTableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clicked_rightMenu(QPoint)));
    ItemModelWine->setHorizontalHeaderLabels(columnTitles);

}
void vekWineOption::clicked_rightMenu(const QPoint &pos)
{
    QTableView* signalSrc = (QTableView*)sender();
    QModelIndex index = signalSrc->indexAt(pos);
    qInfo()<<index.row();
    if(index.row()>-1){
        QMenu *pMenu=nullptr;
        QAction *pTask = nullptr;
        if(signalSrc==ui->tableView_winen){
            pMenu = new QMenu(ui->tableView_winen);
            pTask=new QAction(tr("安装"));
            pTask ->setData(1);
            pTask->setObjectName(signalSrc->objectName());
        }else{
            pMenu = new QMenu(ui->tableView_wined);
            pTask = new QAction(tr("删除"));
            pTask ->setData(1);
            pTask->setObjectName(signalSrc->objectName());
        }
        pMenu->addAction(pTask);
        connect(pTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
        pMenu->exec(QCursor::pos());
        QList<QAction*> list = pMenu->actions();
        foreach (QAction* pAction, list) delete pAction;
        delete pMenu;
    }
}
void vekWineOption::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender());
    QTableView* tempQTableView;
    if(pEven->objectName()=="tableView_winen"){
        tempQTableView=ui->tableView_winen;
    }else{
        tempQTableView=ui->tableView_wined;
    }
    int curRow=tempQTableView->currentIndex().row();
    QAbstractItemModel *modessl = tempQTableView->model();
    QModelIndex indextemp = modessl->index(curRow,0);
    QString datatemp = modessl->data(indextemp).value<QString>();
    if(pEven->objectName()=="tableView_winen"){
        installWine(datatemp);
    }else{
        deleteWine(datatemp);
    }
    delete pEven;
}
//获取远程仓库wine版本信息
void vekWineOption::getWineGitInfo(){
    if(!g_vekLocalData.wineSource.empty()){
        for(auto &d:g_vekLocalData.wineSource){
            ui->comboBox_wineSrc->addItem(d.first);
        }
    }
    ui->lineEdit_InstallPath->setText(QApplication::applicationDirPath());
}
void vekWineOption::wineVersionComoboBox(){
    QString nowWineSrc=ui->comboBox_wineSrc->currentText();
    if(nowWineSrc==nullptr){
        nowWineSrc="DefaultSrc";
    }
    loadWineData();
}
void vekWineOption::installWine(QString wineName)
{

    if(ui->lineEdit_InstallPath->text()==nullptr){
        pObject::vekTip("请选择Wine安装路径");
        return;
    }
    QString selPath=ui->lineEdit_InstallPath->text();
    QString selSrc=ui->comboBox_wineSrc->currentText();
    SwineData isWData={};
    for(auto [d,p] :g_vekLocalData.wineJsonList){
        if(d==selSrc){
            for(auto dx:p){
                if(dx.first==wineName){
                    isWData.s_wine_src=selSrc;
                    isWData.s_wine_name=dx.second.s_remote_wine_name;
                    isWData.s_wine_version=dx.second.s_remote_wine_version;
                    isWData.s_wine_url=dx.second.s_remote_wine_git;
                    isWData.s_wine_path=selPath+"/vekWine/"+dx.second.s_remote_wine_name;
                    isWData.s_wine_mono=dx.second.s_remote_wine_mono;
                    isWData.s_wine_gecko_86=dx.second.s_remote_wine_gecko_86;
                    isWData.s_wine_gecko_8664=dx.second.s_remote_wine_gecko_8664;
                    for(auto v:dx.second.s_remote_wine_dxvk){
                        isWData.s_wine_dxvk.insert(isWData.s_wine_dxvk.end(),v);
                    }
                    break;
                }
            }
        }
    }
    obj_Thread= new QThread;
    objWine_Thread = new objectGitWine(isWData);
    connect(this,SIGNAL(ToThread()),objWine_Thread,SLOT(gitWine()));
    connect(objWine_Thread,SIGNAL(toPrgStr(QString)),this,SLOT(appendTextToLog(QString)));
    connect(objWine_Thread,SIGNAL(overThreadSignals(bool)),this,SLOT(overGitThreadSignals(bool)));
    objWine_Thread->moveToThread(obj_Thread);
    obj_Thread->start();
    emit ToThread();
    controlState(false);
}
void vekWineOption::deleteWine(QString wineName){
    int curRow=ui->tableView_wined->model()->rowCount();
    bool sDelWine=true;
    if(curRow-1==0){
        sDelWine=pObject::vekMesg("删除最后一个Wine容器内的程序将无法运行!是否坚持删除?");
    }
    if(sDelWine){
        QString winePath=nullptr;
        for(auto a:g_vekLocalData.wineVec){
            if(a.first==wineName){
                winePath=a.second.s_wine_path;
                break;
            }
        }
        if(pObject::vekMesg("您确定要删除"+wineName+"\n路径为:"+winePath)){
            if(winePath!=nullptr){
                QDir wineInstallDir(winePath);
                if(wineInstallDir.exists()){
                    wineInstallDir.removeRecursively();
                    g_vekLocalData.wineVec.erase(wineName);
                    pObject::deleteWineDataToJson(wineName);
                    loadWineData();
                    pObject::vekTip("删除成功!");
                }
            }else{
                pObject::vekTip("删除失败!");
                return;
            }
        }
    }
}
void vekWineOption::controlState(bool pState){
    ui->tableView_wined->setEnabled(pState);
    ui->tableView_winen->setEnabled(pState);
    ui->comboBox_wineSrc->setEnabled(pState);
    ui->lineEdit_InstallPath->setEnabled(pState);
    ui->toolButton_SetInstallDir->setEnabled(pState);
}
void vekWineOption::appendTextToLog(QString info_logo)
{
    ui->textEdit->document()->setMaximumBlockCount(1000);
    ui->textEdit->append(info_logo);
    QTextCursor cursor=ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}
void vekWineOption::overGitThreadSignals(bool error)
{
    obj_Thread->exit();
    controlState(true);
    if(!error){
        ui->textEdit->append("下载Wine出错请重试!");
    }else{
        loadWineData();
    }
    obj_Thread=nullptr;
}
void vekWineOption::on_toolButton()
{
    QWidget *qwidget = new QWidget();
    QString installPath=QFileDialog::getExistingDirectory(qwidget,"选择Wine保存目录","",QFileDialog::ShowDirsOnly);
    if(installPath!=nullptr){
        ui->lineEdit_InstallPath->setText(installPath);
    }
}
