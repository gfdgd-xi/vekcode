#ifndef VEKGAMEDATA_H
#define VEKGAMEDATA_H

#include "common.h"
#include "objectJson.h"


class vekGameData:public QAbstractListModel
{
    Q_OBJECT
public:
    vekGameData(QObject *parent = NULL);
    ~vekGameData();
    void addItem(BaseGameData *pItem);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    void deleteItem(int index);
    BaseGameData* getItem(int index );
private:
    std::vector<BaseGameData*> m_ItemDataVec;
};

#endif // VEKGAMEDATA_H
