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
        startApp(object_app_start);
    }
}
void vekAppListView::ObjectRun(){
    int index = this->currentIndex().row();
    if (index > -1)
    {
        QObject *object = QObject::sender();
        QAction *action_obnject = qobject_cast<QAction *>(object);
        int object_int=object_app_start;
        if(action_obnject!=nullptr){
            object_int= action_obnject->objectName().toInt();
        }
        objectExtend* _objectExtend=new objectExtend();
        ExtendType exType=EX_APP;
        ExtendArgs exArgs;
        std::vector<QStringList> _codeAgrs;
        switch(object_int)
        {
        case object_app_start:
            startApp(object_app_start);
            return;
        case object_app_debugstart:
            objectExtendApp();
            return;
        case object_app_setgame:
            setItemSlot();
            return;
        case object_app_exportJson:
            ExportJson();
            return;
        case object_app_packageDeb:
            PackageDeb();
            return;
        case object_app_forcekill:
            exArgs.ex_app=object_app_forcekill;
            break;
        case object_app_deletegame:
            setUpDelData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),m_pModel->getItem(index),object_delApp);
            return;       
        }
        if(exArgs.ex_app==object_app_forcekill){
            _objectExtend->setDockOptionObjectData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),m_pModel->getItem(index)->s_uid,_codeAgrs,exArgs,exType);
            _objectExtend->start();
        }
    }
}

void vekAppListView::startApp(Extend_App _objTypes){
    std::vector<QStringList> _codeAgrs;
    int index = this->currentIndex().row();
    if(index>-1){
        SdockerData dockData=pObject::getDockerData(mBox->tabText(mBox->currentIndex()));
        SappData* appData=m_pModel->getItem(index);
        if(appData!=nullptr){
            if(!QDir(dockData.s_dockers_wine_path).exists()){
                pObject::vekTip("Wine路径丢失!");
                return;
            }
            QString pDock=dockData.s_dockers_path+"/"+dockData.s_dockers_name;
            if(!QDir(pDock).exists()){
                pObject::vekTip("容器路径丢失!");
                return;
            }
            if(!QFile(appData->s_exe).exists()){
                pObject::vekTip(appData->s_name+"应用执行程序不存在!"+"路径:"+appData->s_exe);
                return;
            }
            objectExtend* _objectExtend=new objectExtend();
            if(objTray){
                if(objTray->procManages.empty()){
                    delete objTray;
                    objTray=nullptr;
                    objTray=new objectTray();
                    objTray->start();
                }
            }else{
                objTray=new objectTray();
                objTray->start();
            }
            objTray->procManages.push_back(appData->s_main_proc_name);
            //auto pObjectVek=this->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget();
            connect(_objectExtend, SIGNAL(eTray()), objTray, SLOT(ExitTray()));
            objectAppMT* oAMT=new objectAppMT(&dockData,appData);
            oAMT->InstallDXVK();
            delete oAMT;
            oAMT=nullptr;
            ExtendArgs exArgs;
            ExtendType exType=EX_APP;
            exArgs.ex_app=_objTypes;
            _objectExtend->setDockOptionObjectData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),appData->s_uid,_codeAgrs,exArgs,exType);
            _objectExtend->start();
        }
    }

}
//导出配置文件json
void vekAppListView::ExportJson(){
    int index = this->currentIndex().row();
    if(!_vExportJson){
        SappData bGameData=*m_pModel->getItem(index);
        _vExportJson=new vekExportJson();
        _vExportJson->setAttribute(Qt::WA_DeleteOnClose,true);
        _vExportJson->show();
        connect(_vExportJson,&vekExportJson::_unExportJson,this,&vekAppListView::unExportJson);
        _vExportJson->ExportJson(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),bGameData.s_uid);
    }
}
//导出Deb包
void vekAppListView::PackageDeb(){
    int index = this->currentIndex().row();
    if(!_vPackage){
        bool dn_ok=false;
        QString dnTitle="功能解锁密码";
        QString dnLabel="涉及版权问题 该功能为限制功能";
        QString movePassword="";
        QLineEdit::EchoMode echoMode=QLineEdit::Normal;
        movePassword = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,movePassword, &dn_ok);
        if(!dn_ok){
            return;
        }else if(movePassword=="413"){
            SappData bGameData=*m_pModel->getItem(index);
            _vPackage=new vekPackage();
            _vPackage->setAttribute(Qt::WA_DeleteOnClose,true);
            _vPackage->setGeometry(this->geometry());
            if(_vPackage->vAppData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),bGameData.s_uid)){
                _vPackage->show();
                connect(_vPackage,&vekPackage::_unPackage,this,&vekAppListView::unPackage);
            }else{
                delete _vPackage;
                _vPackage=nullptr;
            }
        }
    }
}

//调试
void vekAppListView::objectExtendApp(){
    if(!_vExtendDebug){
        _vExtendDebug=new vekExtendDebug();
        _vExtendDebug->setAttribute(Qt::WA_DeleteOnClose,true);
        QString currentTabText =mBox->tabText(mBox->currentIndex());
        QString currentAppCID=m_pModel->getItem(this->currentIndex().row())->s_uid;
        _vExtendDebug->ConnectDebugObject(currentTabText,currentAppCID);
        _vExtendDebug->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vExtendDebug->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
        connect(_vExtendDebug,&vekExtendDebug::_unVekDebug,this,&vekAppListView::unDebugApp);
        _vExtendDebug->show();
        pObject::vekTip("温馨提示:调试模式需要在终端内运行vek进行\n 执行:sudo chmod +x vek\n 执行:./vek");
    }
}
//设置选项
void vekAppListView::setItemSlot(){
    int index = this->currentIndex().row();
    if (index > -1)
    {
        if(!_vek_App_option){
            //绑定传参槽
            _vek_App_option=new vekAppOption();
            _vek_App_option->setAttribute(Qt::WA_DeleteOnClose,true);
            _vek_App_option->setWindowTitle("Vek软件设置");
            QString currentAppCID=m_pModel->getItem(this->currentIndex().row())->s_uid;
            _vek_App_option->vekAppAddConnectObject(&g_vekLocalData.map_docker_list.at(mBox->tabText(mBox->currentIndex())),currentAppCID,object_setApp);
            _vek_App_option->setWindowFlags(Qt::WindowStaysOnTopHint);
            _vek_App_option->show();
            connect(_vek_App_option,&vekAppOption::_unDiyAppAdd,this,&vekAppListView::unAppAdd);
            connect(_vek_App_option,SIGNAL(_upAppData(SdockerData,SappData*,EADEType)),this,SLOT(setUpDelData(SdockerData,SappData*,EADEType)));
        }
    }
}
void vekAppListView::setUpDelData(SdockerData dockData,SappData* appData,EADEType objTypeView){
    int index = this->currentIndex().row();
    if(index>-1){
        QString deleteCID=m_pModel->getItem(index)->s_uid;
        QString dockPathStr=dockData.s_dockers_path+"/";
        QString dockNameStr=dockData.s_dockers_name;
        objectJson _objectJson;
        bool dState=false;
        if(objTypeView==object_delApp){
            if(m_pModel->rowCount()<=1){
                dState=pObject::vekMesg("提示:这是"+dockNameStr+"最后一个程序,若是执意删除则Vek将删除"+dockNameStr+"容器");
            }
            m_pModel->deleteItem(index);
            _objectJson.deleteAppNodeData(dockData,deleteCID);
            if(dState){
                deleteDockerTab(dockPathStr,dockNameStr);
                _objectJson.deleteDockerNodeData(dockData.s_dockers_name);
            }
        }
        //修改设置
        if(objTypeView==object_setApp){
            QString currentTabText =mBox->tabText(mBox->currentIndex());
            m_pModel->deleteItem(index);
            auto pObjectVek=this->parentWidget()->parentWidget()->parentWidget();
            //判断设置后的dockName和当前是否相同，该功能是利用设置修改容器名
            if(currentTabText==dockData.s_dockers_name){
                m_pModel->addItem(appData);
                _objectJson.updateAppNodeData(dockData,*appData);
                connect(this,SIGNAL(setUpGroupTabIcoSignal()),pObjectVek,SLOT(upTabIco()));
                emit setUpGroupTabIcoSignal();
            }else{
                //在新的容器中执行
                _objectJson.deleteAppNodeData(pObject::getDockerData(currentTabText),appData->s_uid);
                _objectJson.updateAppNodeData(dockData,*appData);
                connect(this,SIGNAL(setUpDelDataSignal(SdockerData*,SappData*)),pObjectVek,SLOT(addAppObject(SdockerData*,SappData*)));
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
    g_vekLocalData.map_docker_list.erase(dockNameStr);
    objectJson _oJson;
    _oJson.deleteDockerNodeData(dockNameStr);
    m_pListMap->erase(dockNameStr);
}
void vekAppListView::unPackage(){
    _vPackage=nullptr;
}
void vekAppListView::unAppAdd(){
    _vek_App_option=nullptr;
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

void vekAppListView::addItem(SappData *pItem )
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
            SappData *pItem = m_pModel->getItem(index);
            pList->setViewMode(QListView::IconMode);
            pList->setFlow(QListView::LeftToRight);
            pList->addItem(pItem);
            m_pModel->deleteItem(index);
            QString dockName=m_ActionMap.find(pSender)->first->text();
            objectJson _objectJson;
            _objectJson.deleteAppNodeData(pObject::getDockerData(mBox->tabText(mBox->currentIndex())),pItem->s_uid);
            _objectJson.addAppNodeData(pObject::getDockerData(dockName),*pItem);
        }
    }
    //操作完了要把这个临时的映射清空
    m_ActionMap.clear();
}
