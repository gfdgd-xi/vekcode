#include "vekAppListView.h"


vekAppListView::vekAppListView( QWidget *parent):QListView(parent)
{
    parent=nullptr;
    m_hitIndex = -1;
    m_pModel = new vekAppData;
    this->setModel(m_pModel);
    m_pListMap = NULL;
}

vekAppListView::~vekAppListView()
{
}
void vekAppListView::contextMenuEvent( QContextMenuEvent * event )
{
    int hitIndex = this->indexAt(event->pos()).row();
    if (hitIndex > -1)
    {      
        QMenu *pSubMenu = NULL;
        pMenu = new QMenu(this);
        std::map<QString,vekAppListView*>::iterator it;
        for (it=m_pListMap->begin();it != m_pListMap->end();++it)
        {
            if (!pSubMenu)
            {
                //增加容器转移功能
                pSubMenu = new QMenu(tr("转移软件到容器=>") ,pMenu);
                pMenu->addMenu(pSubMenu);
            }
            if (it->second != this)
            {
                QAction *pMoveAct = new QAction( it->first,pMenu);
                //记录菜单与分组的映射，在moveSlot()响应时需要用到。
                m_ActionMap.insert(std::pair<QAction*,vekAppListView*>(pMoveAct,it->second));
                pSubMenu->addAction(pMoveAct);
                connect(pMoveAct,SIGNAL(triggered ()),this,SLOT(moveSlot()));
            }

        }
        for(int i=0;i<=(int)objectTypeStr.size()-1;i++){
            QAction *pObject = new QAction(objectTypeStr[i],pMenu);
            pObject->setObjectName(QString::number(i, 10));
            pMenu->addAction(pObject);
            connect(pObject,SIGNAL(triggered (bool)),this,SLOT(ObjectRun()));
        }
        pMenu->popup(mapToGlobal(event->pos()));
    }
}
void vekAppListView::mouseDoubleClickEvent(QMouseEvent * event){
    UNUSED(event);
    int index = this->currentIndex().row();
    if(index>-1){
        startApp(START);
    }
}
void vekAppListView::ObjectRun(){
    int index = this->currentIndex().row();
    if (index > -1)
    {
        QObject *object = QObject::sender();
        QAction *action_obnject = qobject_cast<QAction *>(object);
        int object_int=START;
        if(action_obnject!=nullptr){
            object_int= action_obnject->objectName().toInt();
        }
        objectExtend* _objectExtend=new objectExtend();
        OBJTYPE _objType=DEFAULT;
        std::vector<QStringList> _codeAgrs;
        switch(object_int)
        {
        case WINECFG:
            _objType=WINECFG;
            break;
        case REGEDIT:
            _objType=REGEDIT;
            break;
        case CONTROL:
            _objType=CONTROL;
            break;
        case REMOVE:
            _objType=REMOVE;
            break;
        case WINETRICKSGUI:
            _objType=WINETRICKSGUI;
            break;
        case WINETRICKSLIBS:
            _objType=WINETRICKSLIBS;
            _codeAgrs=vekWinetricks_cArgs();
            if(_codeAgrs.empty()){
                return;
            }
            break;
        case START:
            _objType=START;
            break;
        case FORCEKILL:
            _objType=FORCEKILL;
            break;
        case DEBUG:
            objectExtendApp();
            return;
        case SETAPP:
            setItemSlot();
            return;
        case DELETEAPP:
            setUpDelData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),m_pModel->getItem(index),DELETE);
            return;
        case EXPORTJSON:
            ExportJson();
            return;
        case PACKAGEDEB:
            pObject::vekTip("功能开发中!");
            return;
        }       
        if(_objType==START){
            startApp(START);
        }else{
            _objectExtend->setDockOptionObjectData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),m_pModel->getItem(index)->app_CID,_codeAgrs,_objType,BOOTTYPE::BOOTDEFAULT,SERVERTYPE::SERVERDEFAULT);
            _objectExtend->start();
        }
    }
}
std::vector<QStringList> vekAppListView::vekWinetricks_cArgs(){
        QString dlgTitle="winetricks命令框";
        QString txtLabel="直接输入功能,多个库和功能空格隔开·例如:vcrun2012 vcrun2015";
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
void vekAppListView::startApp(OBJTYPE _objType){
    std::vector<QStringList> _codeAgrs;
    int index = this->currentIndex().row();
    if(index>-1){
        DockData dockData=pObject::getDockerData(mBox->tabText(mBox->currentIndex()));
        AppData* appData=m_pModel->getItem(index);
        if(!QDir(dockData.docker_WinePath).exists()){
            pObject::vekTip("Wine路径丢失!");
            return;
        }
        QString pDock=dockData.docker_Path+"/"+dockData.docker_Name;
        if(!QDir(pDock).exists()){
            pObject::vekTip("容器路径丢失!");
            return;
        }
        if(!QFile(appData->app_Exe).exists()){
            pObject::vekTip(appData->app_Name+"应用执行程序不存在!"+"路径:"+appData->app_Exe);
            return;
        }
        objectExtend* _objectExtend=new objectExtend();
        taskList.push_back(appData->app_MainProcName);
        auto pObjectVek=this->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget();
        connect(_objectExtend, SIGNAL(objexitTray(bool)), pObjectVek, SLOT(exitTray(bool)));
        emit _startTray();
        objectAppMT* oAMT=new objectAppMT(appData,&dockData);
        oAMT->sObjectInstall();
        delete oAMT;
        oAMT=nullptr;
        _objectExtend->setDockOptionObjectData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),appData->app_CID,_codeAgrs,_objType,BOOTTYPE::BOOTDEFAULT,SERVERTYPE::SERVERDEFAULT);
        _objectExtend->start();
    }

}
void vekAppListView::ExportJson(){
    int index = this->currentIndex().row();
    if(_vExportJson==nullptr){
        AppData bGameData=*m_pModel->getItem(index);
        _vExportJson=new vekExportJson();
        _vExportJson->setAttribute(Qt::WA_DeleteOnClose,true);
        _vExportJson->show();
        connect(_vExportJson,&vekExportJson::_unExportJson,this,&vekAppListView::unExportJson);
        _vExportJson->ExportJson(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),bGameData.app_CID);
    }
}
void vekAppListView::objectExtendApp(){
    if(_vExtendDebug==nullptr){
        _vExtendDebug=new vekExtendDebug();
        _vExtendDebug->setAttribute(Qt::WA_DeleteOnClose,true);
        QString currentTabText =mBox->tabText(mBox->currentIndex());
        QString currentAppCID=m_pModel->getItem(this->currentIndex().row())->app_CID;
        _vExtendDebug->ConnectDebugObject(currentTabText,currentAppCID);
        connect(_vExtendDebug,&vekExtendDebug::_unVekDebug,this,&vekAppListView::unDebugApp);
        _vExtendDebug->show();
    }
}
//设置选项
void vekAppListView::setItemSlot(){
    int index = this->currentIndex().row();
    if (index > -1)
    {
        if(_vek_App_Add==nullptr){
            //绑定传参槽
            _vek_App_Add=new vekAppAddMT();
            _vek_App_Add->setAttribute(Qt::WA_DeleteOnClose,true);
            _vek_App_Add->setWindowTitle("Vek软件设置");
            QString currentAppCID=m_pModel->getItem(this->currentIndex().row())->app_CID;
            _vek_App_Add->vekAppAddConnectObject(&g_vekLocalData.local_DockerData.at(mBox->tabText(mBox->currentIndex())),currentAppCID,SEETING);
            _vek_App_Add->setWindowFlags(Qt::WindowStaysOnTopHint);
            _vek_App_Add->show();
            connect(_vek_App_Add,&vekAppAddMT::_unDiyAppAdd,this,&vekAppListView::unAppAdd);
            connect(_vek_App_Add,SIGNAL(_upData(DockData,AppData*,objectTypeView)),this,SLOT(setUpDelData(DockData,AppData*,objectTypeView)));
        }
    }
}
void vekAppListView::setUpDelData(DockData dockData,AppData* appData,OBJAPP objTypeView){
    int index = this->currentIndex().row();
    if(index>-1){
        QString deleteCID=m_pModel->getItem(index)->app_CID;
        QString dockPathStr=dockData.docker_Path+"/";
        QString dockNameStr=dockData.docker_Name;
        objectJson _objectJson;
        bool dState=false;
        if(objTypeView==DELETE){
            if(m_pModel->rowCount()<=1){
                 dState=pObject::vekMesg("提示:这是"+dockNameStr+"最后一个程序,若是执意删除则Vek将删除"+dockNameStr+"容器");
            }
            m_pModel->deleteItem(index);
            _objectJson.deleteAppNodeData(dockData,deleteCID);
            if(dState){
                deleteDockerTab(dockPathStr,dockNameStr);
                _objectJson.deleteDockerNodeData(dockData.docker_Name);
            }
        }
        //修改设置
        if(objTypeView==SEETING){
            QString currentTabText =mBox->tabText(mBox->currentIndex());
            m_pModel->deleteItem(index);
            auto pObjectVek=this->parentWidget()->parentWidget()->parentWidget();
            //判断设置后的dockName和当前是否相同，该功能是利用设置修改容器名
            if(currentTabText==dockData.docker_Name){
                m_pModel->addItem(appData);
                _objectJson.updateAppNodeData(dockData,*appData);
                connect(this,SIGNAL(setUpGroupTabIcoSignal()),pObjectVek,SLOT(upTabIco()));
                emit setUpGroupTabIcoSignal();
            }else{
                //在新的容器中执行
                _objectJson.deleteAppNodeData(pObject::getDockerData(currentTabText),appData->app_CID);
                _objectJson.updateAppNodeData(dockData,*appData);     
                connect(this,SIGNAL(setUpDelDataSignal(DockData*,AppData*)),pObjectVek,SLOT(addAppObject(DockData*,AppData*)));
                emit setUpDelDataSignal(&dockData,appData);
            }  
        }
    }
}
void vekAppListView::deleteDockerTab(QString dockPathStr,QString dockNameStr){
    mBox->removeTab(mBox->currentIndex());
    if(dockPathStr!=nullptr&&dockNameStr!=nullptr){
        QDir dockPath(dockPathStr+dockNameStr);
        if(dockPath.exists()){
            dockPath.removeRecursively();
        }
    }
    g_vekLocalData.local_DockerData.erase(dockNameStr);
    objectJson _oJson;
    _oJson.deleteDockerNodeData(dockNameStr);
    m_pListMap->erase(dockNameStr);
}
void vekAppListView::unAppAdd(){
    _vek_App_Add=nullptr;
}
void vekAppListView::unExportJson(){
    _vExportJson=nullptr;
}
void vekAppListView::unDebugApp(){
    _vExtendDebug=nullptr;
}

void vekAppListView::setListMap( std::map<QString,vekAppListView*> *pListMap,QTabWidget* pBox)
{
    m_pListMap = pListMap;
    mBox=pBox;
}

void vekAppListView::addItem(AppData *pItem )
{
    m_pModel->addItem(pItem);
}

void vekAppListView::moveSlot()
{
    QAction *pSender = qobject_cast<QAction*>(sender());
    int index = this->currentIndex().row();
    if (pSender)
    {
        //根据点击的菜单，找到相应的列表，然后才能把图标转移过去
        vekAppListView *pList = m_ActionMap.find(pSender)->second;
        if (pList)
        {
            AppData *pItem = m_pModel->getItem(index);
            pList->setViewMode(QListView::IconMode);
            pList->setFlow(QListView::LeftToRight);
            pList->addItem(pItem);
            m_pModel->deleteItem(index);
            QString dockName=m_ActionMap.find(pSender)->first->text();
            objectJson _objectJson;
            _objectJson.deleteAppNodeData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),pItem->app_CID);
            _objectJson.addAppNodeData(pObject::getDockerData(dockName),*pItem);
        }
    }
    //操作完了要把这个临时的映射清空
    m_ActionMap.clear();
}
