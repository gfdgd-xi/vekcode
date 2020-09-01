#include "vekAppData.h"

vekAppData::vekAppData( QObject *parent):QAbstractListModel(parent)
{

}

vekAppData::~vekAppData()
{

}

QVariant vekAppData::data( const QModelIndex & index, int role ) const
{
    if (index.row() > m_ItemDataVec.size())
    {
        return QVariant();
    }
    else
    {
       switch (role)
       {
       case Qt::DisplayRole:
           {
               return m_ItemDataVec[index.row()]->AppName;
           }
        break;
       case Qt::DecorationRole:
           {
               QString icoPath=m_ItemDataVec[index.row()]->AppIco;
               if(!QFile(icoPath).exists()){
                   icoPath=":/res/img/vek.ico";
               }else if(QFileInfo(icoPath).size()<=0){
                   icoPath=":/res/img/vek.ico";
               }
               return QIcon(icoPath);
           }
           break;
       case Qt::SizeHintRole:
           {
               return QSize(127,100);

           }
       }
    }
    return QVariant();
}



int vekAppData::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
    UNUSED(parent);
    return m_ItemDataVec.size();
}

void vekAppData::deleteItem( int index )
{
    std::vector<BaseAppData*>::iterator it = m_ItemDataVec.begin();
    m_ItemDataVec.erase(it + index);
}

void vekAppData::addItem( BaseAppData *pItem )
{
    if (pItem)
    {
        this->beginInsertRows(QModelIndex(),m_ItemDataVec.size(),m_ItemDataVec.size() + 1);
        m_ItemDataVec.push_back(pItem);
        this->endInsertRows();
    }

}

BaseAppData* vekAppData::getItem( int index )
{
    if (index > -1 && index < m_ItemDataVec.size())
    {
        return m_ItemDataVec[index];
    }
}
