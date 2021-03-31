#ifndef VEKAPPDATA_H
#define VEKAPPDATA_H

#include "../../obj/common.h"
#include "../../obj/objectJson.h"


class vekAppData:public QAbstractListModel
{
    Q_OBJECT
public:
    vekAppData(QObject *parent = NULL);
    ~vekAppData();
    void addItem(BaseAppData *pItem);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    void deleteItem(int index);
    BaseAppData* getItem(int index );
private:
    std::vector<BaseAppData*> m_ItemDataVec;
};

#endif // vekAppData_H
