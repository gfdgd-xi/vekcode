#include "vekAppData.h"

vekAppData::vekAppData( QObject *parent):QAbstractListModel(parent)
{

}

vekAppData::~vekAppData()
{

}

QVariant vekAppData::data( const QModelIndex & index, int role ) const
{
    int pIndex=m_ItemDataVec.size();
    if (index.row() > pIndex)
    {
        return QVariant();
    }
    else
    {
       switch (role)
       {
       case Qt::DisplayRole:
           {
               return m_ItemDataVec[index.row()]->s_name;
           }
        break;
       case Qt::DecorationRole:
           {
               QString icoPath=m_ItemDataVec[index.row()]->s_ico;
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
    std::vector<SappData*>::iterator it = m_ItemDataVec.begin();
    m_ItemDataVec.erase(it + index);
}

void vekAppData::addItem( SappData *pItem )
{
    if (pItem)
    {
        this->beginInsertRows(QModelIndex(),m_ItemDataVec.size(),m_ItemDataVec.size() + 1);
        m_ItemDataVec.push_back(pItem);
        this->endInsertRows();
    }

}

SappData* vekAppData::getItem( int index )
{
    int pindex=m_ItemDataVec.size();
    if (index > -1 && index < pindex)
    {
        return m_ItemDataVec[index];
    }
    return nullptr;
}
