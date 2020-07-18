#include "vekGamePanel.h"

vekGamePanel::vekGamePanel(QWidget *parent)
    : QWidget(parent)
{   

    vek_InitTabWidgetListGame();   
    vekLoadJsonData();   
}

vekGamePanel::~vekGamePanel()
{

}
//初始化容器列表
void vekGamePanel::vek_InitTabWidgetListGame(){
    m_pBox = new QTabWidget(this);
    m_pListMap = new std::map<QString,vekGameListView*>();
    for(auto twn :g_vekLocalData.dockerVec){
        vekGameListView *pListView = new vekGameListView();
        pListView->setViewMode(QListView::IconMode);
        pListView->setFlow(QListView::LeftToRight);
        pListView->setResizeMode(QListView::Adjust);
        pListView->setStyleSheet("QListView{icon-size:50px;font:14px;margin-bottom:1px;selection-color: #0a214c;selection-background-color: #C19A6B;} QListView::item{background:#FFFFFF;margin-top:20px;}");
        m_pBox->addTab(pListView,twn.first);
        m_pListMap->insert(std::pair<QString,vekGameListView*>(twn.first,pListView));
        pListView->setListMap(m_pListMap,m_pBox);
    }
    m_pBox->setMaximumSize(788,510);
    m_pBox->setMinimumSize(788,510);
    this->setMinimumSize(788,513);
}
//读取数据to容器列表
void vekGamePanel::vekLoadJsonData(){
    if(!g_vekLocalData.dockerVec.empty()){
        for(auto& y:g_vekLocalData.dockerVec){
            for(auto x:y.second){
                if(y.first==x.second.dockName){
                    vekGameListView* pList= new vekGameListView();
                    QString nowTabName=y.first;
                    BaseGameData *LID=new BaseGameData;
                    LID->gameCID=x.second.gameCID;
                    LID->gameName=x.second.gameName;
                    LID->gameIco=x.second.gameIco;
                    LID->gameExe=x.second.gameExe;
                    LID->gameOtherAgrs=x.second.gameOtherAgrs;
                    LID->winePath=x.second.winePath;
                    LID->wineVersion=x.second.wineVersion;
                    LID->dockPath=x.second.dockPath;
                    LID->dockName=x.second.dockName;
                    LID->dockSystemVersion=x.second.dockSystemVersion;
                    LID->workPath=x.second.workPath;
                    LID->dxvkState=x.second.dxvkState;
                    LID->dxvkVerson=x.second.dxvkVerson;
                    LID->dxvkHUD=x.second.dxvkHUD;
                    LID->dxvkConfigFile=x.second.dxvkConfigFile;
                    LID->dxvkConfigFileState=x.second.dxvkConfigFileState;
                    LID->taskLog=x.second.taskLog;
                    LID->taskMemoryOptimization=x.second.taskMemoryOptimization;
                    LID->taskMemorySharing=x.second.taskMemorySharing;
                    LID->taskRealTimePriority=x.second.taskRealTimePriority;
                    LID->defaultFonts=x.second.defaultFonts;
                    LID->monoState=x.second.monoState;
                    LID->geckoState=x.second.geckoState;
                    LID->mainPrcoName=x.second.mainPrcoName;
                    LID->attachProc=x.second.attachProc;
                    LID->dockEnv=x.second.dockEnv;
                    LID->dockLibs=x.second.dockLibs;
                    LID->dockRegs=x.second.dockRegs;
                    for(std::map<QString,vekGameListView*>::iterator it = m_pListMap->begin();it!=m_pListMap->end();it++)
                    {
                        if(it->first==nowTabName)
                            pList=it->second;
                    }
                    pList->setViewMode(QListView::IconMode);
                    pList->setFlow(QListView::LeftToRight);
                    connect(pList, SIGNAL(_startTray()), this->parentWidget()->parentWidget()->parentWidget(), SLOT(startTray()));
                    pList->addItem(LID);
                }
            }
        }
    }
}
void vekGamePanel::contextMenuEvent( QContextMenuEvent * event )
{
    /*
    QMenu *pMenu = new QMenu(this);
    QAction *pAddGameAct = new QAction(tr("增加游戏"),pMenu);
    pMenu->addAction(pAddGameAct);
    connect(pAddGameAct,SIGNAL(triggered (bool)),this,SLOT(addGameSlot(QWidget)));
    QAction *pAddGroupAct = new QAction(tr("添加分组"),pMenu);
    pMenu->addAction(pAddGroupAct);
    connect(pAddGroupAct,SIGNAL(triggered (bool)),this,SLOT(addGroupSlot(bool)));
    pMenu->popup(mapToGlobal(event->pos()));
    */
}
void vekGamePanel::addGameSlot(){
    if(vek_game_multi_add==nullptr){
        vek_game_multi_add=new vekGameAddMulti();
        vek_game_multi_add->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_game_multi_add->setWindowTitle("Vek游戏增加方式选择");
        connect(vek_game_multi_add,&vekGameAddMulti::_unMultGameAdd,this,&vekGamePanel::unMultGameAdd);
        connect(vek_game_multi_add,&vekGameAddMulti::_MultiGameDiy,this,&vekGamePanel::addGameDiy);
        connect(vek_game_multi_add,&vekGameAddMulti::_MultiGameAuto,this,&vekGamePanel::addGameAuto);
        vek_game_multi_add->show();
    }
}
void vekGamePanel::addGameDiy(){
    if(vek_game_add==nullptr){
        vek_game_add=new vekGameAddMT();
        vek_game_add->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_game_add->setGeometry(this->geometry());
        vek_game_add->setWindowTitle("VekGameAdd");
        vek_game_add->show();
        connect(this, SIGNAL(toObjDiyArgs_ptr(BaseGameData*)), vek_game_add, SLOT(vekGameAddConnectObject(BaseGameData*)));
        emit(toObjDiyArgs_ptr(nullptr));
        connect(vek_game_add,&vekGameAddMT::_unDiyGameAdd,this,&vekGamePanel::unDiyGameAdd);
        connect(vek_game_add,SIGNAL(doneAddGame(BaseGameData*)), this, SLOT(addGameObject(BaseGameData*)));
    }
}
void vekGamePanel::addGameAuto(){
    if(vek_game_add_auto==nullptr){
        vek_game_add_auto=new vekGameAddAT();
        vek_game_add_auto->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_game_add_auto->setGeometry(this->geometry());
        vek_game_add_auto->setWindowTitle("自动配置容器");
        vek_game_add_auto->show();
        connect(this, SIGNAL(toObjAutoArgs_ptr(BaseGameData*)), vek_game_add_auto, SLOT(connectDockObject(BaseGameData*)));
        emit(toObjAutoArgs_ptr(nullptr));
        connect(vek_game_add_auto,&vekGameAddAT::_unAutoDock,this,&vekGamePanel::unAutoDock);
        connect(vek_game_add_auto,SIGNAL(autoObjDock(BaseGameData*)),this,SLOT(addGameObject(BaseGameData*)));
    }
}


void vekGamePanel::objectRunGame(){
    if(m_pListMap!=nullptr){
       m_pListMap->at(m_pBox->tabText(m_pBox->currentIndex()))->ObjectRun();
    }
}
void vekGamePanel::unAutoDock(){
    vek_game_add_auto=nullptr;
}
void vekGamePanel::unMultGameAdd(){
    vek_game_multi_add=nullptr;
}
void vekGamePanel::unDiyGameAdd(){
    vek_game_add=nullptr;
}
void vekGamePanel::addGameObject(BaseGameData* data){
    vekGameListView* pList;
    BaseGameData* _tempBaseData=data;
    QString nowTabName=_tempBaseData->dockName;
    bool tabState=false;
    std::map<QString,vekGameListView*>::iterator it = m_pListMap->begin();
    for (it;it != m_pListMap->end();++it)
    {
        if(it->first==nowTabName){
            qDebug()<<it->first;
            qDebug()<<"页存在";
            tabState=true;
        }
    }
    if(!tabState){
        qDebug()<<"增加页";
        addGroupSlot(_tempBaseData);
    }
    for(std::map<QString,vekGameListView*>::iterator it = m_pListMap->begin();it!=m_pListMap->end();it++)
    {
        if(it->first==nowTabName)
            pList=it->second;
    }
    pList->setViewMode(QListView::IconMode);
    pList->setFlow(QListView::LeftToRight);
    connect(pList, SIGNAL(_startTray()), this->parentWidget()->parentWidget()->parentWidget(), SLOT(startTray()));
    pList->addItem(_tempBaseData);
}
void vekGamePanel::addGroupSlot(BaseGameData* data)
{
    if (!data->dockName.isEmpty())
    {
        qDebug()<<"no nullptr";
        vekGameListView *pListView1 = new vekGameListView(this);
        pListView1->setViewMode(QListView::IconMode);
        pListView1->setFlow(QListView::LeftToRight);
        pListView1->setStyleSheet("QListView{icon-size:50px;font:14px;margin-bottom:1px;selection-color: #0a214c;selection-background-color: #C19A6B;} QListView::item{background:#FFFFFF;margin-top:20px;}");
        m_pBox->addTab(pListView1,data->dockName);
        m_pListMap->insert(std::pair<QString,vekGameListView*>(data->dockName,pListView1));
    }
    //要确保每个MyListView钟的m_pListMap都是一致的，不然就会有错了。
    //因为弹出的菜单进行转移的时候需要用到
    std::map<QString,vekGameListView*>::iterator it = m_pListMap->begin();
    for (it; it != m_pListMap->end(); ++it)
    {
        vekGameListView* pList = it->second;
        pList->setListMap(m_pListMap,m_pBox);
    }
}
