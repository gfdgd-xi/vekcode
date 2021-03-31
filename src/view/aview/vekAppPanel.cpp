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
    std::map<QString,DockData>::iterator it;
    std::map<QString,AppData>::reverse_iterator its;
    for(it=g_vekLocalData.local_DockerData.begin();it!=g_vekLocalData.local_DockerData.end();it++){
        vekAppListView *pListView = new vekAppListView();
        pListView->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
        pListView->setViewMode(QListView::IconMode);
        pListView->setFlow(QListView::LeftToRight);
        pListView->setResizeMode(QListView::Adjust);
        m_pBox->addTab(pListView,it->first);
        if(it->second.docker_SystemBitVersion=="win32"){
            QIcon icon(":/res/img/32.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }else{
            QIcon icon(":/res/img/64.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }
        if(!it->second.docker_Data.empty()){
            for(its=it->second.docker_Data.rbegin();its!=it->second.docker_Data.rend();its++){
                AppData *LID=new AppData();
                *LID=its->second;
                connect(pListView, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
                pListView->addItem(LID);
            }
        }
        m_pListMap->insert(std::pair<QString,vekAppListView*>(it->first,pListView));
        pListView->setListMap(m_pListMap,m_pBox);
    }

}

void vekAppPanel::contextMenuEvent( QContextMenuEvent * event )
{
    cindex=m_pBox->tabBar()->tabAt(event->pos());
    if(cindex>-1){
        QMenu *pMenu = new QMenu(this);
        QAction *pAddGroupAct = new QAction(tr("删除容器"),pMenu);
        pAddGroupAct->setObjectName(m_pBox->tabText(cindex));
        pMenu->addAction(pAddGroupAct);
        connect(pAddGroupAct,SIGNAL(triggered (bool)),this,SLOT(deleteGroupSlot(bool)));
        pMenu->exec(QCursor::pos());
        QList<QAction*> list = pMenu->actions();
        foreach (QAction* pAction, list) delete pAction;
        delete pMenu;
    }
}

//读取数据to容器列表
void vekAppPanel::vekLoadJsonData(){
    if(g_vekLocalData.local_DockerData.empty()){
        return;
    }else{
        for(auto& y:g_vekLocalData.local_DockerData){
            for(auto z:y.second.docker_Data){
                vekAppListView* pList= new vekAppListView();
                QString nowTabName=y.first;
                AppData *LID=new AppData();
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
        DockData tmpData=pObject::getDockerData(m_pBox->tabText(m_pBox->currentIndex()));
        vek_app_add->vekAppAddConnectObject(&tmpData,nullptr,ADD);
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
    if(g_vekLocalData.local_WineData.empty()){
        pObject::vekTip("未发现您的电脑上装有wine请安装wine后重试");
        return;
    }
    if(g_vekLocalData.local_DockerData.empty()){
        dState=pObject::vekMesg("您的电脑上未发现容器无法安装软件,是否初始化一个容器用于软件安装");
        if(!dState){
            return;
        }
    }
    DockData baseDockerData;
    AppData  baseAppData;
    objectAppMT* objNewDock=new objectAppMT(&baseAppData,&baseDockerData);
    QString dockName="vekON1";
    baseAppData.app_DefaultFonts=true;
    //判断当前容器数量是否为0;
    if(m_pBox->count()!=0){
        //当前容器目标
        dockName =m_pBox->tabText(m_pBox->currentIndex());
    }else{
        dState=true;
    }
    //dState=true表示容器数量为0,无容器需初始化
    if(dState){
        //涉及一个问题：当容器列表为0
        QString sName;
        if(g_vekLocalData.local_WineData.size()>1){
            QStringList items;
            for(auto wName:g_vekLocalData.local_WineData){
                items<<wName.second.iWineName;
            }
            QString dlgTitle="Wine版本选择";
            QString txtLabel="当前Wine版本列表";
            int     curIndex=0;
            bool    editable=false;
            bool    ok=false;
            sName = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
            if(!ok){
                return;
            }
            for(auto wName:g_vekLocalData.local_WineData){
                if(wName.second.iWineName==sName){
                    baseDockerData.docker_WinePath=g_vekLocalData.local_WineData[sName].iWinePath;
                }
            }
        }else{
            baseDockerData.docker_WinePath=g_vekLocalData.local_WineData.begin()->second.iWinePath;
            sName=g_vekLocalData.local_WineData.begin()->second.iWineName;
        }
        dState=pObject::vekMesg("确认安装程序类型!Yes->32位,NO->64位");
        if(!dState){
            baseDockerData.docker_SystemBitVersion="win64";
        }
        if(g_vekLocalData.local_WineData[sName].iWineName.contains("deepin",Qt::CaseSensitive)&baseDockerData.docker_SystemBitVersion=="win64"){
            pObject::vekError("deepin-wine5不支持64位容器,默认强行以32位初始化容器!");
            baseDockerData.docker_SystemBitVersion="win32";
        }
        for(auto a:g_vekLocalData.local_DockerData){
            if(a.first==dockName){
                dState=pObject::vekMesg("发现相同容器如继续执行将重置该容器,是否覆盖容器创建?");
                break;
            }
        }
        if(!dState){
            addGroupSlot(&baseDockerData);
        }else{
            return;
        }
        baseDockerData.docker_Path=QApplication::applicationDirPath()+"/vekDock";
        baseDockerData.docker_Name=dockName;
        baseDockerData.docker_MonoState=true;
        baseDockerData.docker_GeckoState=true;
        objNewDock->newDock();
    }
    else//否则从全局本地配置文件提取容器参数
    {
        if(g_vekLocalData.local_DockerData.empty()){
            return;
        }else{
            //通过容器名定位当前容器名对应调用当前容器相应功能包含安装软件界面等。
            baseDockerData=g_vekLocalData.local_DockerData.at(dockName);
        }
    }
    if(baseDockerData.docker_WineVersion.contains("deepin",Qt::CaseSensitive)){
        pObject::vekError("deepin-wine5不支持64位容器,可能部分64位软件安装程序无法运行!");
    }
    objectExtend* _objectExtend=new objectExtend();
    OBJTYPE _objType=REMOVE;
    std::vector<QStringList> _codeAgrs;
    _objectExtend->setDockOptionObjectData(baseDockerData,baseAppData.app_CID,_codeAgrs,_objType,BOOTTYPE::BOOTDEFAULT,SERVERTYPE::SERVERDEFAULT);
    _objectExtend->start();
    delete objNewDock;
    objNewDock=nullptr;
}
void vekAppPanel::objInitDock(){
    bool dState=false;
    QString dockName;
    QString dockBit="win32";
    if(g_vekLocalData.local_WineData.empty()){
        pObject::vekTip("未发现您的电脑上装有wine请安装wine后重试");
        return;
    }
    DockData baseDockerData;
    AppData  baseAppData;
    objectAppMT* objNewDock=new objectAppMT(&baseAppData,&baseDockerData);
    baseAppData.app_DefaultFonts=true;
    QString sName;
    QStringList items;
    QStringList itemsbit;
    //选择wine版本
    for(auto wName:g_vekLocalData.local_WineData){
        items<<wName.second.iWineName;
    }
    QString wTitle="选择Wine版本";
    QString wLabel="当前Wine版本列表";
    int     wIndex=0;
    bool    wtable=false;
    bool    w_ok=false;
    sName = QInputDialog::getItem(this, wTitle,wLabel,items,wIndex,wtable,&w_ok);
    if(!w_ok){
        return;
    }
    //选择容器系统版本
    if(sName.contains("deepin",Qt::CaseSensitive)){
        itemsbit<<"win32";
    }else{
        itemsbit<<"win32"<<"win64";
    }
    QString dTitle="选择容器系统版本";
    QString dLabel="支持容器列表";
    int     dIndex=0;
    bool    dtable=false;
    bool    d_ok=false;
    dockBit = QInputDialog::getItem(this, dTitle,dLabel,itemsbit,dIndex,dtable,&d_ok);
    if(!d_ok){
        return;
    }
    //输入容器名
    QString dnTitle="容器名";
    QString dnLabel="建议采用英文名字";
    dockName="vekON1";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;//正常文字输入
    bool dn_ok=false;
    dockName = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,dockName, &dn_ok);
    if(!dn_ok){
        return;
    }
    for(auto wName:g_vekLocalData.local_WineData){
        if(wName.second.iWineName==sName){
            baseDockerData.docker_WinePath=g_vekLocalData.local_WineData[sName].iWinePath;
            break;
        }
    }
    if(dockName==nullptr){
        pObject::vekTip("容器名不能为空!");
        return;
    }
    if(baseDockerData.docker_WinePath==nullptr){
        pObject::vekTip("找不到选用对应Wine");
        return;
    }
    for(auto a:g_vekLocalData.local_DockerData){
        if(a.first==dockName){
            dState=true;
            break;
        }
    }
    if(dState){
        dState=pObject::vekMesg("发现相同容器如继续执行将重置该容器,是否覆盖容器创建?");
        if(!dState){
            return;
        }
    }
    baseDockerData.docker_SystemBitVersion=dockBit;
    baseDockerData.docker_Path=QApplication::applicationDirPath()+"/vekDock";
    baseDockerData.docker_Name=dockName;
    baseDockerData.docker_MonoState=true;
    baseDockerData.docker_GeckoState=true;
    objNewDock->newDock();
    objNewDock=nullptr;
    if(!dState){
        addGroupSlot(&baseDockerData);
    }
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
void vekAppPanel::addAppObject(DockData* dcokData,AppData* appData){
    vekAppListView* pList=new vekAppListView();
    AppData* _tempBaseData=new AppData;
    _tempBaseData=appData;
    QString nowTabName=dcokData->docker_Name;
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
    cTab=0;
    for(auto a:g_vekLocalData.local_DockerData){
        if(a.second.docker_SystemBitVersion=="win32"){
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
void vekAppPanel::addGroupSlot(DockData* dcokData)
{
    if (!dcokData->docker_Name.isEmpty())
    {
        vekAppListView *pListView1 = new vekAppListView(this);
        pListView1->setViewMode(QListView::IconMode);
        pListView1->setFlow(QListView::LeftToRight);
        m_pBox->addTab(pListView1,dcokData->docker_Name);
        m_pListMap->insert(std::pair<QString,vekAppListView*>(dcokData->docker_Name,pListView1));
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
void vekAppPanel::deleteGroupSlot(bool del_static){
    QAction *pEven = qobject_cast<QAction *>(this->sender());
    QString strDockerName=pEven->objectName();
    DockData tDocker=pObject::getDockerData(strDockerName);
    m_pBox->removeTab(cindex);
    qInfo()<<cindex;
    if(tDocker.docker_Path!=nullptr&&strDockerName!=nullptr){
        qInfo()<<tDocker.docker_Path;
        QDir dockPath(tDocker.docker_Path+"/"+strDockerName);
        if(dockPath.exists()){
            dockPath.removeRecursively();
        }
    }
    g_vekLocalData.local_DockerData.erase(strDockerName);
    objectJson _oJson;
    _oJson.deleteDockerNodeData(strDockerName);
    m_pListMap->erase(strDockerName);
}
