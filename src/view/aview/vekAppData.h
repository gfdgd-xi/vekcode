#ifndef VEKAPPDATA_H
#define VEKAPPDATA_H

#include "../../obj/common.h"
#include "../../obj/objectJson.h"
#include <QMetaType>

typedef struct {
    QString iconPath;
    QString singer;
    QString songsNb;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)
class vekAppData:public QAbstractListModel
{

    Q_OBJECT
public:
    vekAppData(QObject *parent = NULL);
    ~vekAppData();
    void addItem(SappData *pItem);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    void deleteItem(int index);
    SappData* getItem(int index );
private:
    std::vector<SappData*> m_ItemDataVec;
};

#endif // vekAppData_H
