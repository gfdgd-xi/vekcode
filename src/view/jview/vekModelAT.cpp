#include "vekModelAT.h"

vekModelAT::vekModelAT(QObject *parent) : QAbstractListModel(parent)
{

}
vekModelAT::~vekModelAT(){

}
QVariant vekModelAT::data( const QModelIndex & index, int role ) const
{
    if (index.row() >m_ItemDataVec.size())
    {
        return QVariant();
    }
    else
    {
        switch (role)
        {
        case Qt::DisplayRole:
        {
            return m_ItemDataVec[index.row()]->appName;
        }
            break;
        case Qt::DecorationRole:
        {
            QString icoPath=m_ItemDataVec[index.row()]->appIco;
            QString icoCache=QDir::currentPath()+"/vekCache/"+icoPath;
            if(!QFile(icoCache).exists()){
                icoPath=":/res/img/vek.ico";
            }else if(QFileInfo(icoCache).size()<=0){
                icoPath=":/res/img/vek.ico";
            }else{
                icoPath=icoCache;
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

void vekModelAT::addItem( BaseAppJson *pItem )
{
    if (pItem)
    {
        this->beginInsertRows(QModelIndex(),m_ItemDataVec.size(),m_ItemDataVec.size() + 1);
        m_ItemDataVec.push_back(pItem);
        this->endInsertRows();
    }

}

int vekModelAT::rowCount( const QModelIndex & parent ) const
{
    UNUSED(parent);
    return m_ItemDataVec.size();
}

BaseAppJson* vekModelAT::getItem( int index )
{
    if (index > -1 && index < m_ItemDataVec.size())
    {
        return m_ItemDataVec[index];
    }
}
