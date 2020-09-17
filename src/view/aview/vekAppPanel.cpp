#include "vekAppPanel.h"
#include <QGridLayout>
vekAppPanel::vekAppPanel(QWidget *parent)
    : QWidget(parent)
{   
    vek_InitTabWidgetListApp();
    //vekLoadJsonData();
}

vekAppPanel::~vekAppPanel()
{

}
int cTab=0;
//初始化容器列表
void vekAppPanel::vek_InitTabWidgetListApp(){
    QGridLayout *gridLayout = new QGridLayout(this);
    m_pBox = new QTabWidget(this);
    gridLayout->addWidget(m_pBox);
    gridLayout->setContentsMargins(0,0,0,0);
    m_pBox->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    m_pListMap = new std::map<QString,vekAppListView*>();
    cTab=0;
    std::map<QString,BaseDockData>::iterator it;
    std::map<QString,BaseAppData>::reverse_iterator its;
    for(it=g_vekLocalData.dockerVec.begin();it!=g_vekLocalData.dockerVec.end();it++){
        vekAppListView *pListView = new vekAppListView();
        pListView->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
        pListView->setViewMode(QListView::IconMode);
        pListView->setFlow(QListView::LeftToRight);
        pListView->setResizeMode(QListView::Adjust);
        m_pBox->addTab(pListView,it->first);
        if(it->second.DockerVer=="win32"){
            QIcon icon(":/res/img/32.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }else{
            QIcon icon(":/res/img/64.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }
        if(!it->second.dData.empty()){
            for(its=it->second.dData.rbegin();its!=it->second.dData.rend();its++){
                BaseAppData *LID=new BaseAppData();
                *LID=its->second;
                connect(pListView, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
                pListView->addItem(LID);
            }
        }
        m_pListMap->insert(std::pair<QString,vekAppListView*>(it->first,pListView));
        pListView->setListMap(m_pListMap,m_pBox);
    }

}
//读取数据to容器列表
void vekAppPanel::vekLoadJsonData(){
    if(g_vekLocalData.dockerVec.empty()){
        return;
    }else{
        for(auto& y:g_vekLocalData.dockerVec){
            for(auto z:y.second.dData){
                vekAppListView* pList= new vekAppListView();
                QString nowTabName=y.first;
                BaseAppData *LID=new BaseAppData();
                *LID=z.second;
                for(std::map<QString,vekAppListView*>::iterator it = m_pListMap->begin();it!=m_pListMap->end();it++)
                {
                    if(it->first==nowTabName){
                        pList=it->second;
                        break;
                    }
                }
                pList->setViewMode(QListView::IconMode);
                pList->setFlow(QListView::LeftToRight);
                connect(pList, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
                pList->addItem(LID);
            }
        }
    }
}
void vekAppPanel::addAppSlot(){
    if(vek_app_multi_add==nullptr){
        vek_app_multi_add=new vekAppAddMulti();
        vek_app_multi_add->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_multi_add->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_multi_add->setWindowTitle("Vek游戏增加方式选择");
        connect(vek_app_multi_add,&vekAppAddMulti::_unMultAppAdd,this,&vekAppPanel::unMultAppAdd);
        connect(vek_app_multi_add,&vekAppAddMulti::_MultiAppDiy,this,&vekAppPanel::addAppDiy);
        connect(vek_app_multi_add,&vekAppAddMulti::_MultiAppAuto,this,&vekAppPanel::addAppAuto);
        vek_app_multi_add->show();
    }
}
void vekAppPanel::addAppDiy(){
    if(vek_app_add==nullptr){
        vek_app_add=new vekAppAddMT();
        vek_app_add->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_add->setWindowTitle("Vek软件增加");
        vek_app_add->vekAppAddConnectObject(nullptr,nullptr,object_addApp);
        vek_app_add->show();
        connect(vek_app_add,&vekAppAddMT::_unDiyAppAdd,this,&vekAppPanel::unDiyAppAdd);
        connect(vek_app_add,SIGNAL(doneAddApp(BaseDockData*,BaseAppData*)), this, SLOT(addAppObject(BaseDockData*,BaseAppData*)));
    }
}
void vekAppPanel::addAppAuto(){
    if(vek_app_add_auto==nullptr){
        vek_app_add_auto=new vekAppAddAT();
        vek_app_add_auto->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add_auto->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_add_auto->setWindowTitle("自动配置容器");
        vek_app_add_auto->connectDockObject();
        vek_app_add_auto->show();
        connect(vek_app_add_auto,&vekAppAddAT::_unAutoDock,this,&vekAppPanel::unAutoDock);
        connect(vek_app_add_auto,SIGNAL(autoObjDock(BaseDockData*,BaseAppData*)),this,SLOT(addAppObject(BaseDockData*,BaseAppData*)));
    }
}
void vekAppPanel::objAppInstall(){
    bool dState=false;
    if(g_vekLocalData.wineVec.empty()){
        vekTip("未发现您的电脑上装有wine请安装wine后重试");
        return;
    }
    if(g_vekLocalData.dockerVec.empty()){
        dState=vekMesg("您的电脑上未发现容器无法安装软件,是否初始化一个容器用于软件安装");
        if(!dState){
            return;
        }
    }
    BaseDockData baseDockerData;
    BaseAppData  baseAppData;
    objectAppMT* objNewDock=new objectAppMT(&baseAppData,&baseDockerData);
    QString dockName="vekON1";
    baseAppData.DefaultFonts=true;
    if(m_pBox->count()!=0){
        dockName =m_pBox->tabText(m_pBox->currentIndex());
    }else{
        dState=true;
    }
    if(dState){
        baseDockerData.WinePath=g_vekLocalData.wineVec.begin()->second.IwinePath;
        baseDockerData.DockerPath=QDir::currentPath()+"/vekDock";
        baseDockerData.DockerName=dockName;
        baseDockerData.MonoState=true;
        baseDockerData.GeckoState=true;
        objNewDock->newDock();
    }else{
        if(g_vekLocalData.dockerVec.empty()){
            return;
        }else{
            baseDockerData=g_vekLocalData.dockerVec.at(dockName);
        }
    }
    objectExtend* _objectExtend=new objectExtend();
    objectType _objType=object_uninstall;
    std::vector<QStringList> _codeAgrs;
    _objectExtend->setDockOptionObjectData(baseDockerData,baseAppData.AppCID,_codeAgrs,_objType,objectWineBoot::object_wineboot_default,objectWineServer::object_wineserver_default);
    _objectExtend->start();
    delete objNewDock;
    objNewDock=nullptr;
}

void vekAppPanel::objectRunApp(){
    if(m_pListMap!=nullptr){
        m_pListMap->at(m_pBox->tabText(m_pBox->currentIndex()))->ObjectRun();
    }
}
void vekAppPanel::unAutoDock(){
    vek_app_add_auto=nullptr;
}
void vekAppPanel::unMultAppAdd(){
    vek_app_multi_add=nullptr;
}
void vekAppPanel::unDiyAppAdd(){
    vek_app_add=nullptr;
}
void vekAppPanel::addAppObject(BaseDockData* dcokData,BaseAppData* appData){
    vekAppListView* pList=new vekAppListView();
    BaseAppData* _tempBaseData=new BaseAppData;
    _tempBaseData=appData;
    QString nowTabName=dcokData->DockerName;
    bool tabState=false;
    if(m_pListMap->count(nowTabName)>0){
        tabState=true;
    }
    if(!tabState){
        addGroupSlot(dcokData);
    }
    for(std::map<QString,vekAppListView*>::iterator it = m_pListMap->begin();it!=m_pListMap->end();it++)
    {
        if(it->first==nowTabName){
            pList=it->second;
            break;
        }
    }
    pList->setViewMode(QListView::IconMode);
    pList->setFlow(QListView::LeftToRight);
    connect(pList, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
    pList->addItem(_tempBaseData);
}
void vekAppPanel::upTabIco(){
    for(auto a:g_vekLocalData.dockerVec){
        if(a.second.DockerVer=="win32"){
            QIcon icon(":/res/img/32.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }else{
            QIcon icon(":/res/img/64.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }
    }
}
void vekAppPanel::addGroupSlot(BaseDockData* dcokData)
{
    cTab=0;
    if (!dcokData->DockerName.isEmpty())
    {
        vekAppListView *pListView1 = new vekAppListView(this);
        pListView1->setViewMode(QListView::IconMode);
        pListView1->setFlow(QListView::LeftToRight);
        m_pBox->addTab(pListView1,dcokData->DockerName);
        m_pListMap->insert(std::pair<QString,vekAppListView*>(dcokData->DockerName,pListView1));
    }
    upTabIco();
    //要确保每个MyListView钟的m_pListMap都是一致的，不然就会有错了。
    //因为弹出的菜单进行转移的时候需要用到
    std::map<QString,vekAppListView*>::iterator it;
    for (it=m_pListMap->begin(); it != m_pListMap->end(); ++it)
    {
        vekAppListView* pList = it->second;
        pList->setListMap(m_pListMap,m_pBox);
    }
}
