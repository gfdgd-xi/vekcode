#include "vekAppPanel.h"
#include <QGridLayout>
vekAppPanel::vekAppPanel(QWidget *parent)
    : QWidget(parent)
{   
    vek_InitTabWidgetListApp();
}

vekAppPanel::~vekAppPanel()
{

}

QSize icoSize(25,20);
//初始化容器列表
void vekAppPanel::vek_InitTabWidgetListApp(){   
    QGridLayout *gridLayout = new QGridLayout(this);
    m_pBox = new QTabWidget(this);
    gridLayout->addWidget(m_pBox);
    gridLayout->setContentsMargins(0,0,0,0);
    m_pBox->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    m_pListMap = new std::map<QString,vekAppListView*>();
    std::map<QString,SdockerData>::iterator it;
    std::map<QString,SappData>::reverse_iterator its;
    m_pBox->setIconSize(icoSize);
    QString icoStr;
    QIcon icon;
    int cTab=0;
    for(it=g_vekLocalData.map_docker_list.begin();it!=g_vekLocalData.map_docker_list.end();it++){
        vekAppListView *pListView = new vekAppListView();
        pListView->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
        pListView->setViewMode(QListView::IconMode);
        pListView->setFlow(QListView::LeftToRight);
        pListView->setResizeMode(QListView::Adjust);
        m_pBox->addTab(pListView,it->first);
        if(it->second.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
            if(it->second.s_dockers_bit_version=="win32"){
                icoStr=":/res/img/D32.png";
            }else{
                icoStr=":/res/img/D64.png";
            }
        }else{
            if(it->second.s_dockers_bit_version=="win32"){
                icoStr=":/res/img/H32.png";
            }else{
                icoStr=":/res/img/H64.png";

            }
        }
        QIcon icon(icoStr);
        m_pBox->setTabIcon(cTab,icon);
        cTab+=1;
        if(!it->second.map_dockers_data.empty()){
            for(its=it->second.map_dockers_data.rbegin();its!=it->second.map_dockers_data.rend();its++){
                SappData *LID=new SappData();
                *LID=its->second;
                connect(pListView, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
                pListView->addItem(LID);
            }
        }
        m_pListMap->insert(std::pair<QString,vekAppListView*>(it->first,pListView));
        pListView->setListMap(m_pListMap,m_pBox);
    }

}
void vekAppPanel::changeQTwidgetStyle(QTabWidget::TabPosition iTab){
    if(iTab==QTabWidget::West){
        m_pBox->setTabPosition(QTabWidget::West);
        m_pBox->tabBar()->setStyle(new vekAppCustomBarStyle);
    }else{
        m_pBox->setTabPosition(QTabWidget::North);
        m_pBox->tabBar()->setStyle(nullptr);
    }
}
void vekAppPanel::contextMenuEvent( QContextMenuEvent * event )
{
    cindex=m_pBox->tabBar()->tabAt(event->pos());
    if(cindex>-1){
        pMenu = new QMenu(this);
        for(int i=0;i<=dockerops.size()-1;i++){
            QAction *pObject=new QAction(dockerops[i],pMenu);
            pMenu->addAction(pObject);
            pObject->setObjectName(QString::number(i, 10));
            connect(pObject,SIGNAL(triggered (bool)),this,SLOT(DockerObject()));
        }
        pMenu->exec(QCursor::pos());
        QList<QAction*> list = pMenu->actions();
        foreach (QAction* pAction, list) delete pAction;
        delete pMenu;
    }
}
void vekAppPanel::DockerObject(){
    QObject *object = QObject::sender();
    QAction *action_obnject = qobject_cast<QAction *>(object);
    int object_int=action_obnject->objectName().toInt();
    objectExtend* _objectExtend=new objectExtend();
    ExtendType exType=EX_DOCKER;
    ExtendArgs exArgs;
    std::vector<QStringList> _codeAgrs;
    switch(object_int){
    case 0:
         addAppSlot();
         return;
    case 1:
        setDockerSlot();
        return;
    case 2:
        exArgs.ex_docker=object_docker_winecfg;
        break;
    case 3:
        exArgs.ex_docker=object_docker_regedit;
        break;
    case 4:
        exArgs.ex_docker=object_docker_control;
        break;
    case 5:
        exArgs.ex_docker=object_docker_uninstall;
        break;
    case 6:
        exArgs.ex_docker=object_docker_allforcekill;
    case 7:
        deleteGroupSlot(true);
        return;
    case 8:
        exArgs.ex_docker=object_docker_winetricks_gui;
        break;
    case 9:
        exArgs.ex_docker=object_docker_winetricks_cmd_libs;
        _codeAgrs=vekWinetricks_cArgs();
        if(_codeAgrs.empty()){
            return;
        }
        break;
    }
    _objectExtend->setDockOptionObjectData(pObject::getDockerData(m_pBox->tabText(m_pBox->currentIndex())),nullptr,_codeAgrs,exArgs,exType);
    _objectExtend->start();
}
std::vector<QStringList> vekAppPanel::vekWinetricks_cArgs(){
    QString dlgTitle="winetricks命令框";
    QString txtLabel="直接输入功能,多个库和功能空格隔开\n例如:vcrun2012 vcrun2015\n命令:--self-update 可以在线更新winetricks";
    QString defaultInput;
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;//正常文字输入
    bool ok=false;
    QString arg = QInputDialog::getText(nullptr, dlgTitle,txtLabel, echoMode,defaultInput, &ok);
    std::vector<QStringList> args;
    if (ok && !arg.isEmpty())
    {
        QStringList _args=arg.split(" ");
        args.push_back(_args);
    }
    return args;
}
//设置选项
void vekAppPanel::setDockerSlot(){
    if(vek_docker_option==nullptr){
        //绑定传参槽
        vek_docker_option=new vekDockerOption();
        vek_docker_option->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_docker_option->setWindowTitle("Docker设置");
        SdockerData tmpData=pObject::getDockerData(m_pBox->tabText(m_pBox->currentIndex()));
        vek_docker_option->vekAppAddConnectObject(tmpData);
        vek_docker_option->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_docker_option->show();
        connect(vek_docker_option,&vekDockerOption::_unOption,this,&vekAppPanel::unDockOption);
        //connect(vek_docker_option,SIGNAL(_upData(SdockerData,SappData*,EADEType)),this,SLOT(setUpDelData(SdockerData,SappData*,EADEType)));
    }
}
void vekAppPanel::addAppSlot(){
    if(vek_app_add_model==nullptr){
        vek_app_add_model=new vekAppAddModel();
        vek_app_add_model->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add_model->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_add_model->setWindowTitle("Vek游戏增加方式选择");
        connect(vek_app_add_model,&vekAppAddModel::_unMultAppAdd,this,&vekAppPanel::unMultAppAdd);
        connect(vek_app_add_model,&vekAppAddModel::_MultiAppDiy,this,&vekAppPanel::AddAppDiyType);
        connect(vek_app_add_model,&vekAppAddModel::_MultiAppAuto,this,&vekAppPanel::AddAppAutoType);
        vek_app_add_model->show();
    }
}
void vekAppPanel::AddAppDiyType(){
    if(vek_app_add==nullptr){
        vek_app_add=new vekAppOption();
        vek_app_add->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_add->setWindowTitle("Vek软件增加");
        SdockerData tmpData=pObject::getDockerData(m_pBox->tabText(m_pBox->currentIndex()));
        vek_app_add->vekAppAddConnectObject(&tmpData,nullptr,object_addApp);
        vek_app_add->show();
        connect(vek_app_add,&vekAppOption::_unDiyAppAdd,this,&vekAppPanel::unDiyAppAdd);
        connect(vek_app_add,SIGNAL(doneAddApp(SdockerData*,SappData*)), this, SLOT(addAppObject(SdockerData*,SappData*)));
    }
}
void vekAppPanel::AddAppAutoType(){
    if(vek_app_add_auto==nullptr){
        vek_app_add_auto=new vekAppAutoOption();
        vek_app_add_auto->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add_auto->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_add_auto->setWindowTitle("自动配置容器");
        SdockerData tmpData=pObject::getDockerData(m_pBox->tabText(m_pBox->currentIndex()));
        vek_app_add_auto->connectDockObject(tmpData);
        vek_app_add_auto->show();
        connect(vek_app_add_auto,&vekAppAutoOption::_unAutoDock,this,&vekAppPanel::unAutoDock);
        connect(vek_app_add_auto,SIGNAL(autoObjDock(SdockerData*,SappData*)),this,SLOT(addAppObject(SdockerData*,SappData*)));
    }
}
void vekAppPanel::objInitDocker(INITTYPE iType){
    if(g_vekLocalData.map_wine_list.empty()){
        pObject::vekTip("未发现您的电脑上装有wine请安装wine后重试");
        return;
    }
    bool dState=false;
    SdockerData tempDockerData;
    SappData tempAppData;
    ExtendType exType=EX_DOCKER;
    ExtendArgs exArgs;
    exArgs.ex_boot=object_wineboot_i;
    objectAppMT* objNewDock=new objectAppMT(&tempDockerData,&tempAppData);
    tempDockerData.s_dockers_default_fonts=false;
    tempDockerData.s_dockers_mono_state=false;
    tempDockerData.s_dockers_gecko_state=false;
    QString dockName="vekON1";
    QString dockBit="win32";
    if(iType==INITDOCKER){
        //init docker
        QString swVer;
        QStringList items;
        QStringList itemsbit;
        //选择wine版本
        for(auto wName:g_vekLocalData.map_wine_list){
            items<<wName.second.s_local_wine_name;
        }
        QString wTitle="选择Wine版本";
        QString wLabel="当前Wine版本列表";
        int     wIndex=0;
        bool    wtable=false;
        bool    w_ok=false;
        swVer = QInputDialog::getItem(this, wTitle,wLabel,items,wIndex,wtable,&w_ok);
        if(!w_ok){
            return;
        }
        itemsbit<<"win32"<<"win64";
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
        for(auto wName:g_vekLocalData.map_wine_list){
            if(wName.second.s_local_wine_name==swVer){
                tempDockerData.s_dockers_wine_path=g_vekLocalData.map_wine_list[swVer].s_local_wine_path;
                tempDockerData.s_dockers_wine_version=g_vekLocalData.map_wine_list[swVer].s_local_wine_name;
                break;
            }
        }
        if(dockName==nullptr){
            pObject::vekTip("容器名不能为空!");
            return;
        }
        if(tempDockerData.s_dockers_wine_path==nullptr){
            pObject::vekTip("找不到选用对应Wine");
            return;
        }
        bool font_stste=pObject::vekMesg("是否安装默认字体");
        if(font_stste)
        {
            tempDockerData.s_dockers_default_fonts=true;
        }
        bool mono_stste=pObject::vekMesg("是否安装Mono组件");
        if(mono_stste)
        {
            tempDockerData.s_dockers_mono_state=true;
        }
        bool gecko_stste=pObject::vekMesg("是否安装Gecko组件");
        if(gecko_stste)
        {
            tempDockerData.s_dockers_gecko_state=true;
        }
        for(auto a:g_vekLocalData.map_docker_list){
            if(a.first==dockName){
                pObject::vekMesg("已存在相同名容器,无法创建容器!");
                return;
            }
        }
        tempDockerData.s_dockers_wine_exe_version="wine";
        tempDockerData.s_dockers_bit_version=dockBit;
        tempDockerData.s_dockers_path=QApplication::applicationDirPath()+"/vekDock";
        tempDockerData.s_dockers_name=dockName;
        objNewDock->InitDocker(true);
        addGroupSlot(&tempDockerData);
    }else{
        //install app
        if(g_vekLocalData.map_docker_list.empty()){
            dState=pObject::vekMesg("您的电脑上未发现容器无法安装软件,是否初始化一个容器用于软件安装");
            if(!dState){
                return;
            }
        }
        exArgs.ex_docker=object_docker_uninstall;
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
            QStringList items;
            for(auto wName:g_vekLocalData.map_wine_list){
                items<<wName.second.s_local_wine_name;
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
            for(auto wName:g_vekLocalData.map_wine_list){
                if(wName.second.s_local_wine_name==sName){
                    tempDockerData.s_dockers_wine_path=g_vekLocalData.map_wine_list[sName].s_local_wine_path;
                    tempDockerData.s_dockers_wine_version=g_vekLocalData.map_wine_list[sName].s_local_wine_name;
                }
            }
            QStringList itemsbit;
            //选择容器系统版本
            /*
            if(sName.contains("deepin",Qt::CaseSensitive)){
                itemsbit<<"win32";
            }else{
                itemsbit<<"win32"<<"win64";
            }
            */
            itemsbit<<"win32"<<"win64";
            QString dTitle="选择容器系统版本";
            QString dLabel="支持容器列表";
            int     dIndex=0;
            bool    dtable=false;
            bool    d_ok=false;
            dockBit = QInputDialog::getItem(this, dTitle,dLabel,itemsbit,dIndex,dtable,&d_ok);
            if(!d_ok){
                return;
            }
            bool font_stste=pObject::vekMesg("是否安装默认字体");
            if(font_stste)
            {
                tempDockerData.s_dockers_default_fonts=true;
            }
            bool mono_stste=pObject::vekMesg("是否安装Mono组件");
            if(mono_stste)
            {
                tempDockerData.s_dockers_mono_state=true;
            }
            bool gecko_stste=pObject::vekMesg("是否安装Gecko组件");
            if(gecko_stste)
            {
                tempDockerData.s_dockers_gecko_state=true;
            }
            tempDockerData.s_dockers_wine_exe_version="wine";
            tempDockerData.s_dockers_path=QApplication::applicationDirPath()+"/vekDock";
            tempDockerData.s_dockers_name=dockName;
            tempDockerData.s_dockers_bit_version=dockBit;
            objNewDock->InitDocker(true);
            addGroupSlot(&tempDockerData);
        }
        else//否则从全局本地配置文件提取容器参数
        {
            if(g_vekLocalData.map_wine_list.empty()){
                return;
            }else{
                //通过容器名定位当前容器名对应调用当前容器相应功能包含安装软件界面等。
                tempDockerData=g_vekLocalData.map_docker_list.at(dockName);
            }
        }
        /*
        if(tempDockerData.s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
            pObject::vekError("deepin-wine5不支持64位容器,可能部分64位软件安装程序无法运行!");
        }
        */
        objectExtend* _objectExtend=new objectExtend();
        std::vector<QStringList> _codeAgrs;
        _objectExtend->setDockOptionObjectData(tempDockerData,nullptr,_codeAgrs,exArgs,exType);
        _objectExtend->start();
    }
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
void vekAppPanel::unDockOption(){
    vek_docker_option=nullptr;
}
void vekAppPanel::unMultAppAdd(){
    vek_app_add_model=nullptr;
}
void vekAppPanel::unDiyAppAdd(){
    vek_app_add=nullptr;
}
void vekAppPanel::addAppObject(SdockerData* dcokData,SappData* appData){
    vekAppListView* pList=new vekAppListView();
    SappData* _tempBaseData=new SappData;
    _tempBaseData=appData;
    QString nowTabName=dcokData->s_dockers_name;
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
    //m_pBox
    int xTab=m_pBox->count();
    m_pBox->setIconSize(icoSize);
    QString icoStr;
    QIcon icon;
    for(int i=0;i<=xTab-1;i++){
        QString dockName=m_pBox->tabText(i);
        if(g_vekLocalData.map_docker_list[dockName].s_dockers_wine_version.contains("deepin",Qt::CaseSensitive)){
            if(g_vekLocalData.map_docker_list[dockName].s_dockers_bit_version=="win32"){
                icoStr=":/res/img/D32.png";
            }else{
                icoStr=":/res/img/D64.png";
            }
        }else{
            if(g_vekLocalData.map_docker_list[dockName].s_dockers_bit_version=="win32"){
                icoStr=":/res/img/H32.png";
            }else{
                icoStr=":/res/img/H64.png";
            }
        }
        QIcon icon(icoStr);
        m_pBox->setTabIcon(i,icon);
    }
}
void vekAppPanel::addGroupSlot(SdockerData* dcokData)
{
    if (!dcokData->s_dockers_name.isEmpty())
    {
        vekAppListView *pListView1 = new vekAppListView();
        pListView1->setViewMode(QListView::IconMode);
        pListView1->setFlow(QListView::LeftToRight);
        m_pBox->addTab(pListView1,dcokData->s_dockers_name);
        m_pListMap->insert(std::pair<QString,vekAppListView*>(dcokData->s_dockers_name,pListView1));
    }
    //要确保每个MyListView钟的m_pListMap都是一致的，不然就会有错了。
    //因为弹出的菜单进行转移的时候需要用到
    std::map<QString,vekAppListView*>::iterator it;
    for (it=m_pListMap->begin(); it != m_pListMap->end(); ++it)
    {
        vekAppListView* pList = it->second;
        pList->setListMap(m_pListMap,m_pBox);
    }
    upTabIco();
}
void vekAppPanel::deleteGroupSlot(bool del_static){
    UNUSED(del_static);

    SdockerData tDocker=pObject::getDockerData(m_pBox->tabText(m_pBox->currentIndex()));
    m_pBox->removeTab(cindex);
    qInfo()<<cindex;
    qInfo()<<tDocker.s_dockers_path;
    qInfo()<<tDocker.s_dockers_name;
    if(tDocker.s_dockers_path!=nullptr&&tDocker.s_dockers_name!=nullptr){
        qInfo()<<tDocker.s_dockers_path;
        QDir dockPath(tDocker.s_dockers_path+"/"+tDocker.s_dockers_name);
        if(dockPath.exists()){
            dockPath.removeRecursively();
        }
    }
    g_vekLocalData.map_docker_list.erase(tDocker.s_dockers_name);
    objectJson _oJson;
    _oJson.deleteDockerNodeData(tDocker.s_dockers_name);
    m_pListMap->erase(tDocker.s_dockers_name);
}
