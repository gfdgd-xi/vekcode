#include "vekGameListView.h"


vekGameListView::vekGameListView( QWidget *parent):QListView(parent)
{
    parent=nullptr;
    m_hitIndex = -1;
    m_pModel = new vekGameData;
    this->setModel(m_pModel);
    m_pListMap = NULL;}

vekGameListView::~vekGameListView()
{

}
void vekGameListView::contextMenuEvent( QContextMenuEvent * event )
{
    int hitIndex = this->indexAt(event->pos()).row();
    if (hitIndex > -1)
    {
        //增加容器转移功能
        QMenu *pSubMenu = NULL;
        pMenu = new QMenu(this);
        std::map<QString,vekGameListView*>::iterator it = m_pListMap->begin();
        for (it;it != m_pListMap->end();++it)
        {
            if (!pSubMenu)
            {
                pSubMenu = new QMenu(tr("转至软件到容器=>") ,pMenu);
                pMenu->addMenu(pSubMenu);
            }
            if (it->second != this)
            {
                QAction *pMoveAct = new QAction( it->first,pMenu);
                //记录菜单与分组的映射，在moveSlot()响应时需要用到。
                m_ActionMap.insert(std::pair<QAction*,vekGameListView*>(pMoveAct,it->second));
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
void vekGameListView::ObjectRun(){
    int index = this->currentIndex().row();
    if (index > -1)
    {
        QObject *object = QObject::sender();
        QAction *action_obnject = qobject_cast<QAction *>(object);
        int object_int=object_start;
        if(action_obnject!=nullptr){
            object_int= action_obnject->objectName().toInt();
        }
        objectExtend* _objectExtend=new objectExtend();
        objectType _objType=object_default;
        switch(object_int)
        {
        case object_winecfg:
            _objType=object_winecfg;
            break;
        case object_regedit:
            _objType=object_regedit;
            break;
        case object_control:
            _objType=object_control;
            break;
        case object_uninstall:
            _objType=object_uninstall;
            break;
        case object_winetricks_gui:
            _objType=object_winetricks_gui;
            break;
        case object_start:
            _objType=object_start;
            break;
        case object_forcekill:
            _objType=object_forcekill;
            break;
        case object_debugstart:
            objectExtendGame();
            return;
            break;
        case object_setgame:
            setItemSlot();
            return;
            break;
        case object_deletegame:
            deleteItemSlot();
            return;
            break;
        }
        std::vector<QStringList> _codeAgrs;
        connect(this, SIGNAL(toObjectArgs(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)), _objectExtend, SLOT(setDockOptionObjectData(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer)));
        emit(toObjectArgs(*m_pModel->getItem(index),_codeAgrs,_objType,objectWineBoot::object_wineboot_default,objectWineServer::object_wineserver_default));
        _objectExtend->start();
    }
}
void vekGameListView::objectExtendGame(){
    _vExtendDebug=new vekExtendDebug();
    _vExtendDebug->setAttribute(Qt::WA_DeleteOnClose,true);
    _vExtendDebug->setGeometry(this->geometry());
    _vExtendDebug->show();
    connect(this,SIGNAL(toObjectArgs_cl(BaseGameData)),_vExtendDebug,SLOT(ExtendGame(BaseGameData)));
    int index = this->currentIndex().row();
    emit toObjectArgs_cl(*m_pModel->getItem(index));
}
//设置选项
void vekGameListView::setItemSlot(){
    int index = this->currentIndex().row();
    if (index > -1)
    {
        BaseGameData* bGameData=m_pModel->getItem(index);
        if(_vek_Game_Add==nullptr){
            //绑定传参槽
            _vek_Game_Add=new vekGameAddMT();
            connect(this, SIGNAL(toObjectArgs_ptr(BaseGameData*)), _vek_Game_Add, SLOT(vekGameAddConnectObject(BaseGameData*)));
            _vek_Game_Add->setAttribute(Qt::WA_DeleteOnClose,true);
            _vek_Game_Add->setGeometry(this->geometry());
            _vek_Game_Add->setWindowTitle("VekGameSet");
            emit(toObjectArgs_ptr(bGameData));
            _vek_Game_Add->show();
            connect(_vek_Game_Add,&vekGameAddMT::_unDiyGameAdd,this,&vekGameListView::unGameAdd);
            connect(_vek_Game_Add,SIGNAL(_upData(BaseGameData*)),this,SLOT(upData(BaseGameData*)));
        }
    }
}
void vekGameListView::upData(BaseGameData* data){
    int index = this->currentIndex().row();
    m_pModel->deleteItem(index);
    m_pModel->addItem(data);
}
void vekGameListView::unGameAdd(){
    _vek_Game_Add=nullptr;
}
void vekGameListView::deleteItemSlot()
{
    int index = this->currentIndex().row();
    if (index > -1)
    {
        QString deleteCID=m_pModel->getItem(index)->gameCID;
        QString dockPathStr=m_pModel->getItem(index)->dockPath+"/";
        QString dockNameStr=m_pModel->getItem(index)->dockName;
        m_pModel->deleteItem(index);
        objectJson _objectJson;
        _objectJson.deleteGameNodeData(deleteCID);
        if(m_pModel->rowCount()<=0){
            mBox->removeTab(mBox->currentIndex());
            if(dockPathStr!=NULL&dockNameStr!=NULL){
                QDir dockPath(dockPathStr+dockNameStr);
                if(dockPath.exists()){
                    dockPath.removeRecursively();
                }
            }
        }
    }
}

void vekGameListView::setListMap( std::map<QString,vekGameListView*> *pListMap,QTabWidget* pBox)
{
    m_pListMap = pListMap;
    mBox=pBox;
}

void vekGameListView::addItem(BaseGameData *pItem )
{
    m_pModel->addItem(pItem);
}

void vekGameListView::moveSlot()
{
    QAction *pSender = qobject_cast<QAction*>(sender());
    if (pSender)
    {
        //根据点击的菜单，找到相应的列表，然后才能把图标转移过去
        vekGameListView *pList = m_ActionMap.find(pSender)->second;
        if (pList)
        {
            int index = this->currentIndex().row();
            BaseGameData *pItem = m_pModel->getItem(index);
            pList->setViewMode(QListView::IconMode);
            pList->setFlow(QListView::LeftToRight);
            pList->addItem(pItem);
            m_pModel->deleteItem(index);
            pItem->dockName=m_ActionMap.find(pSender)->first->text();
            objectJson _objectJson;
            _objectJson.deleteGameNodeData(pItem->gameCID);
            _objectJson.updateGameNodeData(pItem->dockName,*pItem);
        }
    } 
    //操作完了要把这个临时的映射清空
    m_ActionMap.clear();
}
