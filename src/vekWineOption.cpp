#include "vekWineOption.h"
#include "ui_common.h"
#include "obj/pObject.h"

vekWineOption::vekWineOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekWineOption)
{
    ui->setupUi(this);
    githread = new objectGitWine();
    //下载按钮槽事件绑定
    //connect(ui->pushButton_Install,&QPushButton::clicked,this,&vekWineOption::onButton_Install);
    //connect(ui->pushButton_deleteWine,&QPushButton::clicked,this,&vekWineOption::deleteWine);
    connect(ui->toolButton_SetInstallDir,&QPushButton::clicked,this,&vekWineOption::on_toolButton);
    //
    connect(githread,SIGNAL(outputPrgressSignals()),this,SLOT(appendTextToLog()));
    connect(githread,SIGNAL(overThreadSignals(bool)),this,SLOT(overGitThreadSignals(bool)));
    connect(ui->comboBox_wineSrc,&QComboBox::currentTextChanged,this,&vekWineOption::WineVersionComoboBox);
    GetWineGitInfo();


}

vekWineOption::~vekWineOption()
{
    delete ui;
    emit _unInitWineOption();
}
void vekWineOption::loadData(){
    LoadWineList(ui->tableView_winen);
    LoadWineList(ui->tableView_wined);
}
void vekWineOption::LoadWineList(QTableView* qTableView){

    if(qTableView==ui->tableView_winen){
        ItemModelWinen = new QStandardItemModel();
        if(!g_vekLocalData.wineJsonList.empty()){
            for(auto &d : g_vekLocalData.wineJsonList){
                for(auto &x:d.second){
                    ItemModelWinen->appendRow(new QStandardItem(x.second.WineName));
                }
            }
            qTableView->setModel(ItemModelWinen);
            ItemModelWinen->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("当前源提供Wine版本列表"));
        }
    }else{      
        ItemModelWined = new QStandardItemModel();
        if(!g_vekLocalData.wineVec.empty()){
            for(auto &d : g_vekLocalData.wineVec){
                ItemModelWined->appendRow(new QStandardItem(d.second.IwineName));
            }
        }
        qTableView->setModel(ItemModelWined);
        ItemModelWined->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("已安装Wine版本列表"));
    }
    qTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    qTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    qTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //绑定右键
    qTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(qTableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clicked_rightMenu(QPoint)));
}
void vekWineOption::AddWine(){

}
void vekWineOption::RemoveWine(){

}
void vekWineOption::clicked_rightMenu(const QPoint &pos)
{
    QTableView* signalSrc = (QTableView*)sender();  // 获取到了发送该信号按钮的指针
    QModelIndex index = signalSrc->indexAt(pos);
    _pos=pos;
    //创建菜单对象
    if(index.row()>-1){
        if(signalSrc==ui->tableView_winen){
            QMenu *pMenu = new QMenu(ui->tableView_winen);
            QAction *pInstallTask = new QAction(tr("安装"));
            pInstallTask->setData(1);
            pInstallTask->setObjectName(signalSrc->objectName());
            //把QAction对象添加到菜单上
            pMenu->addAction(pInstallTask);
            //连接鼠标右键点击信号
            connect(pInstallTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
            pMenu->exec(QCursor::pos());
            QList<QAction*> list = pMenu->actions();
            foreach (QAction* pAction, list) delete pAction;
            delete pMenu;
        }else{
            QMenu *pMenu = new QMenu(ui->tableView_wined);
            QAction *pDeleteTask = new QAction(tr("删除"));
            pDeleteTask ->setData(1);
            pDeleteTask->setObjectName(signalSrc->objectName());
            //把QAction对象添加到菜单上
            pMenu->addAction(pDeleteTask);
            //连接鼠标右键点击信号
            connect(pDeleteTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
            pMenu->exec(QCursor::pos());
            QList<QAction*> list = pMenu->actions();
            foreach (QAction* pAction, list) delete pAction;
            delete pMenu;
        }
    }
}
void vekWineOption::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender());

    if(pEven->objectName()=="tableView_winen"){
        QModelIndex index = ui->tableView_winen->indexAt(_pos);
        QAbstractItemModel *modessl = ui->tableView_winen->model();
        QModelIndex indextemp = modessl->index(index.row(),0);
        QString selwine = modessl->data(indextemp).value<QString>();
        installWine(selwine);
    }else{
        QModelIndex index = ui->tableView_wined->indexAt(_pos);
        QAbstractItemModel *modessl = ui->tableView_wined->model();
        QModelIndex indextemp = modessl->index(index.row(),0);
        QString selwine = modessl->data(indextemp).value<QString>();
        deleteWine(selwine);
    }
    delete pEven;
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
    QString nowWineSrc=ui->comboBox_wineSrc->currentText();
    if(nowWineSrc==nullptr){
        nowWineSrc="DefaultSrc";
    }
    loadData();
}
void vekWineOption::installWine(QString wineName)
{

    if(ui->lineEdit_InstallPath->text()==nullptr){
        vekTip("请选择Wine安装路径");
        return;
    }
    QString selPath=ui->lineEdit_InstallPath->text();
    QString selSrc=ui->comboBox_wineSrc->currentText();
    BaseWineData iWD;
    for(auto [d,p] :g_vekLocalData.wineJsonList){
        if(d==selSrc){
            for(auto dx:p){
                if(dx.first==wineName){
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
void vekWineOption::deleteWine(QString wineName){
    int curRow=ui->tableView_wined->model()->rowCount();
    bool sDelWine=true;
    if(curRow-1==0){
        sDelWine=vekMesg("删除最后一个Wine容器内的程序将无法运行!是否坚持删除?");
    }
    if(sDelWine){
        QString winePath=nullptr;
        for(auto a:g_vekLocalData.wineVec){
            if(a.first==wineName){
                winePath=a.second.IwinePath;
                break;
            }
        }
        if(vekMesg("您确定要删除"+wineName+"\n路径为:"+winePath)){
            if(winePath!=nullptr){
                QDir wineInstallDir(winePath);
                if(wineInstallDir.exists()){
                    wineInstallDir.removeRecursively();
                    g_vekLocalData.wineVec.erase(wineName);
                    DeleteWineDataToJson(wineName);
                    vekTip("删除成功!");
                    QModelIndex index = ui->tableView_wined->indexAt(_pos);
                    ItemModelWined->removeRow(index.row());
                    ui->tableView_wined->setModel(ItemModelWined);
                }
            }else{
                vekTip("删除失败!");
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
void vekWineOption::appendTextToLog()
{
    ui->textEdit->document()->setMaximumBlockCount(1000);
    ui->textEdit->append(githread->outputPrgressText);
    QTextCursor cursor=ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}
void vekWineOption::overGitThreadSignals(bool error)
{
    githread->exit();
    controlState(true);
    if(!error){
       ui->textEdit->append("下载Wine出错请重试!");
    }else{
        QtConcurrent::run([=]()
        {
            loadData();
        });
    }
}
void vekWineOption::on_toolButton()
{
    QWidget *qwidget = new QWidget();
    QString installPath=QFileDialog::getExistingDirectory(qwidget,"选择Wine保存目录","",QFileDialog::ShowDirsOnly);
    if(installPath!=nullptr){
        ui->lineEdit_InstallPath->setText(installPath);
    }

}
