#ifndef VEKMODELAT_H
#define VEKMODELAT_H

#include "../../obj/common.h"
class vekModelAT: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit vekModelAT(QObject *parent = nullptr);
    ~vekModelAT();
    void addItem(BaseAppJson *pItem);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    BaseAppJson* getItem(int index );
private:
    std::vector<BaseAppJson*> m_ItemDataVec;
};

#endif // VEKGAMEADDATJSONTABLEMODEL_H
