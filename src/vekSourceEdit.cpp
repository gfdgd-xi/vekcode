#include "vekSourceEdit.h"
#include "ui_common.h"
vekSourceEdit::vekSourceEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vekSourceEdit)
{
    ui->setupUi(this);
    vek_Style(this,0);
    loadData();
}

vekSourceEdit::~vekSourceEdit()
{
    delete ui;
    emit _unSourveEdit();
}
void vekSourceEdit::loadData(){
    loadSrcDataTableView(ui->tableView_WineSrcList);
    loadSrcDataTableView(ui->tableView_GameSrcList);
    connect(ui->pushButton_Done,&QPushButton::clicked,this,&vekSourceEdit::slotsDone);
}
void vekSourceEdit::setTableView(QTableView* qtv){
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
}
//把数据加载到tableView
void vekSourceEdit::loadSrcDataTableView(QTableView* qTableView)
{
    tableModel=new QStandardItemModel();
    // set columns
    QStringList columnTitles;
    if(qTableView==ui->tableView_WineSrcList){
        columnTitles << "Wine源名" << "源地址";
        int i=0;
        for(auto &[k,j]:g_vekLocalData.wineSource){
            int x=i++;
            tableModel->setItem(x,0,new QStandardItem(k));
            tableModel->setItem(x,1,new QStandardItem(j));
        }
    }else{
        columnTitles << "Game源名" << "源地址";
        int i=0;
        for(auto &[k,j]:g_vekLocalData.appScrSource){
            int x=i++;
            tableModel->setItem(x,0,new QStandardItem(k));
            tableModel->setItem(x,1,new QStandardItem(j));
        }
    }
    setTableView(qTableView);
    qTableView->setModel(tableModel);
    tableModel->setHorizontalHeaderLabels(columnTitles);
    // add contents

    qTableView->setContextMenuPolicy(Qt::CustomContextMenu);  //少这句，右键没有任何反应的。
    connect(qTableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clicked_rightMenu(QPoint)));
}
void vekSourceEdit::clicked_rightMenu(const QPoint &/*pos*/)
{
    QTableView* signalSrc = (QTableView*)sender();  // 获取到了发送该信号按钮的指针
    //创建菜单对象
    QMenu *pMenu = new QMenu(this);
    QAction *pNewTask = new QAction(tr("新建源"), this);
    QAction *pDeleteTask = new QAction(tr("删除源"), this);
    QAction *pUpdateTask = new QAction(tr("更新源"), this);
    pNewTask->setData(1);
    pDeleteTask ->setData(2);
    pUpdateTask->setData(3);
    pNewTask->setObjectName(signalSrc->objectName());
    pDeleteTask->setObjectName(signalSrc->objectName());
    pUpdateTask->setObjectName(signalSrc->objectName());
    //把QAction对象添加到菜单上
    pMenu->addAction(pNewTask);
    pMenu->addAction(pDeleteTask);
    pMenu->addAction(pUpdateTask);
    //连接鼠标右键点击信号
    connect(pNewTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pDeleteTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pUpdateTask, SIGNAL(triggered()),this, SLOT(onTaskBoxContextMenuEvent()));
    //在鼠标右键点击的地方显示菜单
    pMenu->exec(QCursor::pos());
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}

void vekSourceEdit::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender());
    qDebug()<<pEven->objectName();
    int iType = pEven->data().toInt();
    QTableView* _tempQTableView;
    if(pEven->objectName()=="tableView_WineSrcList"){
        _tempQTableView=ui->tableView_WineSrcList;
    }else{
        _tempQTableView=ui->tableView_GameSrcList;
    }
    switch (iType)
    {
    case 1:
        objectAddSrc(_tempQTableView);
        break;
    case 2:
        objectDeleteSrc(_tempQTableView);
        break;
    case 3:
        objectUpdateSrc(_tempQTableView);
        break;
    default:
        break;
    }
}
void vekSourceEdit::objectAddSrc(QTableView* qTableView){
    QAbstractItemModel *modessl = qTableView->model();
    modessl->insertRow(modessl->rowCount());
    qTableView->setModel(modessl);
}
void vekSourceEdit::objectDeleteSrc(QTableView* qTableView){
    int curRow=qTableView->currentIndex().row();
    int curRows = qTableView->model()->rowCount();
    qDebug()<<curRows-1;
    if(curRows-1<=0){
       vekTip("不能删除唯一源");
       return;
    }
    if(curRow > -1){
        QAbstractItemModel *modessl = qTableView->model();
        QModelIndex indextemp = modessl->index(curRow,0);
        QString datatemp = modessl->data(indextemp).value<QString>();
        if(qTableView->objectName()=="tableView_WineSrcList"){
            for(auto[a,b]:g_vekLocalData.wineSource){
                if(a==datatemp){
                    g_vekLocalData.wineSource.erase(a);
                    break;
                }
            }
        }else{
            for(auto[a,b]:g_vekLocalData.appScrSource){
                if(a==datatemp){
                    g_vekLocalData.appScrSource.erase(a);
                    break;
                }
            }
        }
        saveAllData();
        //先删除全局数据，再删除控件数据
        modessl->removeRow(curRow);
        qTableView->setModel(modessl);
    }
}
void vekSourceEdit::saveAllData(){
    objectJson _objectJson;
    _objectJson.WriteLocalData();
}
void vekSourceEdit::objectUpdateSrc(QTableView* qTableView){
    int curRow=qTableView->model()->rowCount();
    if(qTableView->objectName()=="tableView_WineSrcList"){
         g_vekLocalData.wineSource.empty();
         g_vekLocalData.wineJsonList.empty();
    }else{
        g_vekLocalData.appScrSource.empty();
        g_vekLocalData.appJsonList.empty();
    }
    if(curRow>-1){
        QAbstractItemModel *modessl = qTableView->model();
        for(int i=0;i<=curRow-1;i++){
            QString dataTempA = modessl->data(modessl->index(i,0)).value<QString>();
            QString dataTempB = modessl->data(modessl->index(i,1)).value<QString>();
            if(qTableView->objectName()=="tableView_WineSrcList"){
                g_vekLocalData.wineSource.insert(pair<QString,QString>(dataTempA,dataTempB));
            }else{
                g_vekLocalData.appScrSource.insert(pair<QString,QString>(dataTempA,dataTempB));
            }
        }
        objectSource* objSrc=new objectSource;
        objSrc->updateSrcDataObject();
        saveAllData();
    }
}
void vekSourceEdit::slotsDone(){
      objectUpdateSrc(ui->tableView_WineSrcList);
      objectUpdateSrc(ui->tableView_GameSrcList);
      this->close();
}
