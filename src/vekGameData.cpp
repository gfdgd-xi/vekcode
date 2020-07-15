#include "vekGameData.h"

vekGameData::vekGameData( QObject *parent):QAbstractListModel(parent)
{
    //init();
}

vekGameData::~vekGameData()
{

}

QVariant vekGameData::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
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
               return m_ItemDataVec[index.row()]->gameName;
           }
        break;
       case Qt::DecorationRole:
           {
               return QIcon(m_ItemDataVec[index.row()]->gameIco);
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



int vekGameData::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
    return m_ItemDataVec.size();
}

void vekGameData::init()
{
    /*
    for (int i = 1; i < 26; ++i)
    {
        vekGameData *pItem = new vekGameData;
        pItem->gmeName = QString::number(i).toStdString();;
        pItem->gameIco = QString(":/QQPanel/Resources/%1.jpg").arg(i).toStdString();;
        QFile Iconfile(QString::fromStdString(pItem->gameIco));
        if (Iconfile.exists())
        {
            m_ItemDataVec.push_back(pItem);
        }

    }
    */
}

void vekGameData::deleteItem( int index )
{
    std::vector<BaseGameData*>::iterator it = m_ItemDataVec.begin();
    m_ItemDataVec.erase(it + index);
}

void vekGameData::addItem( BaseGameData *pItem )
{
    if (pItem)
    {
        this->beginInsertRows(QModelIndex(),m_ItemDataVec.size(),m_ItemDataVec.size() + 1);
        m_ItemDataVec.push_back(pItem);
        this->endInsertRows();
    }

}

BaseGameData* vekGameData::getItem( int index )
{
    if (index > -1 && index < m_ItemDataVec.size())
    {
        return m_ItemDataVec[index];
    }
}
