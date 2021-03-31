#ifndef VEKMODELAT_H
#define VEKMODELAT_H

#include "../../obj/common.h"
class vekModelAT: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit vekModelAT(QObject *parent = nullptr);
    ~vekModelAT();
    void addItem(AppJson *pItem);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    AppJson* getItem(int index );
private:
    std::vector<AppJson*> m_ItemDataVec;
};

#endif // VEKGAMEADDATJSONTABLEMODEL_H
