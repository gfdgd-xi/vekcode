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
    void addItem(AppData *pItem);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    void deleteItem(int index);
    AppData* getItem(int index );
private:
    std::vector<AppData*> m_ItemDataVec;
};

#endif // vekAppData_H
