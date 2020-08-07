#include "vekAppPanel.h"
#include <QGridLayout>
vekAppPanel::vekAppPanel(QWidget *parent)
    : QWidget(parent)
{   

    vek_InitTabWidgetListApp();
    vekLoadJsonData();
}

vekAppPanel::~vekAppPanel()
{

}
//初始化容器列表
void vekAppPanel::vek_InitTabWidgetListApp(){
    QGridLayout *gridLayout = new QGridLayout(this);
    m_pBox = new QTabWidget(this);
    gridLayout->addWidget(m_pBox);
    gridLayout->setContentsMargins(0,0,0,0);
    m_pBox->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    m_pListMap = new std::map<QString,vekAppListView*>();
    for(auto twn :g_vekLocalData.dockerVec){
        vekAppListView *pListView = new vekAppListView();
        pListView->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
        pListView->setViewMode(QListView::IconMode);
        pListView->setFlow(QListView::LeftToRight);
        pListView->setResizeMode(QListView::Adjust);
        m_pBox->addTab(pListView,twn.first);
        m_pListMap->insert(std::pair<QString,vekAppListView*>(twn.first,pListView));
        pListView->setListMap(m_pListMap,m_pBox);
    }
}
//读取数据to容器列表
void vekAppPanel::vekLoadJsonData(){
    if(!g_vekLocalData.dockerVec.empty()){
        for(auto& y:g_vekLocalData.dockerVec){
            for(auto x:y.second){
                if(y.first==x.second.dockName){
                    vekAppListView* pList= new vekAppListView();
                    QString nowTabName=y.first;
                    BaseAppData *LID=new BaseAppData;
                    *LID=x.second;
                    for(std::map<QString,vekAppListView*>::iterator it = m_pListMap->begin();it!=m_pListMap->end();it++)
                    {
                        if(it->first==nowTabName){
                            pList=it->second;
                            break;
                        }
                    }
                    pList->setViewMode(QListView::IconMode);
                    pList->setFlow(QListView::LeftToRight);
                    qDebug()<<this->parentWidget()->parentWidget();
                    connect(pList, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
                    pList->addItem(LID);
                }
            }
        }
    }
}
void vekAppPanel::addAppSlot(){
    if(vek_app_multi_add==nullptr){
        vek_app_multi_add=new vekAppAddMulti();
        vek_app_multi_add->setAttribute(Qt::WA_DeleteOnClose,true);
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
        vek_app_add->setGeometry(this->geometry());
        vek_app_add->setWindowTitle("VekAppAdd");
        vek_app_add->show();
        connect(this, SIGNAL(toObjDiyArgs_ptr(BaseAppData*,objectTypeView)), vek_app_add, SLOT(vekAppAddConnectObject(BaseAppData*,objectTypeView)));
        emit(toObjDiyArgs_ptr(nullptr,object_addApp));
        connect(vek_app_add,&vekAppAddMT::_unDiyAppAdd,this,&vekAppPanel::unDiyAppAdd);
        connect(vek_app_add,SIGNAL(doneAddApp(BaseAppData*)), this, SLOT(addAppObject(BaseAppData*)));
    }
}
void vekAppPanel::addAppAuto(){
    if(vek_app_add_auto==nullptr){
        vek_app_add_auto=new vekAppAddAT();
        vek_app_add_auto->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add_auto->setGeometry(this->geometry());
        vek_app_add_auto->setWindowTitle("自动配置容器");
        vek_app_add_auto->show();
        connect(this, SIGNAL(toObjAutoArgs_ptr(BaseAppData*)), vek_app_add_auto, SLOT(connectDockObject(BaseAppData*)));
        emit(toObjAutoArgs_ptr(nullptr));
        connect(vek_app_add_auto,&vekAppAddAT::_unAutoDock,this,&vekAppPanel::unAutoDock);
        connect(vek_app_add_auto,SIGNAL(autoObjDock(BaseAppData*)),this,SLOT(addAppObject(BaseAppData*)));
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
    BaseAppData baseAppdata;
    objectAppAddMT* objNewDock=new objectAppAddMT(&baseAppdata,nullptr);
    QString dockName="vekON1";
    if(m_pBox->count()!=0){
       dockName =m_pBox->tabText(m_pBox->currentIndex());
    }else{
       dState=true;
    }
    if(dState){
        baseAppdata.winePath=g_vekLocalData.wineVec.begin()->second.wineInstallPath;
        baseAppdata.dockPath=QDir::currentPath()+"/vekDock";
        baseAppdata.dockName=dockName;
        baseAppdata.monoState=true;
        baseAppdata.geckoState=true;
        baseAppdata.defaultFonts=true;
        objNewDock->newDock();
    }else{
        if(g_vekLocalData.dockerVec.empty()){
            return;
        }else{
            for(auto a:g_vekLocalData.dockerVec){
                if(dockName==a.first){
                    baseAppdata=a.second.begin()->second;
                    break;
                }
            }
        }
    }
    objectExtend* _objectExtend=new objectExtend();
    objectType _objType=object_uninstall;
    std::vector<QStringList> _codeAgrs;
    connect(this, SIGNAL(toObjectArgs(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)), _objectExtend, SLOT(setDockOptionObjectData(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)));
    emit(toObjectArgs(baseAppdata,_codeAgrs,_objType,objectWineBoot::object_wineboot_default,objectWineServer::object_wineserver_default));
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
void vekAppPanel::addAppObject(BaseAppData* data){
    vekAppListView* pList=new vekAppListView(this);
    BaseAppData* _tempBaseData=data;
    QString nowTabName=_tempBaseData->dockName;
    bool tabState=false;
    std::map<QString,vekAppListView*>::iterator it = m_pListMap->begin();
    for (it;it != m_pListMap->end();++it)
    {
        if(it->first==nowTabName){
            tabState=true;
            break;
        }
    }
    if(!tabState){
        addGroupSlot(_tempBaseData);
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
void vekAppPanel::addGroupSlot(BaseAppData* data)
{
    if (!data->dockName.isEmpty())
    {
        vekAppListView *pListView1 = new vekAppListView(this);
        pListView1->setViewMode(QListView::IconMode);
        pListView1->setFlow(QListView::LeftToRight);
        m_pBox->addTab(pListView1,data->dockName);
        m_pListMap->insert(std::pair<QString,vekAppListView*>(data->dockName,pListView1));
    }
    //要确保每个MyListView钟的m_pListMap都是一致的，不然就会有错了。
    //因为弹出的菜单进行转移的时候需要用到
    std::map<QString,vekAppListView*>::iterator it = m_pListMap->begin();
    for (it; it != m_pListMap->end(); ++it)
    {
        vekAppListView* pList = it->second;
        pList->setListMap(m_pListMap,m_pBox);
    }
}
