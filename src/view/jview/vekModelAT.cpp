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
               return m_ItemDataVec[index.row()]->AppName;
           }
        break;
       case Qt::DecorationRole:
           {
               return QIcon(m_ItemDataVec[index.row()]->AppIco);
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



int vekModelAT::rowCount( const QModelIndex & parent ) const
{
    UNUSED(parent);
    return m_ItemDataVec.size();
}

