#ifndef VEKMODELAT_H
#define VEKMODELAT_H

#include "../../obj/common.h"
class vekModelAT: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit vekModelAT(QObject *parent = nullptr);
    ~vekModelAT();
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
private:
    std::vector<BaseAppData*> m_ItemDataVec;
};

#endif // VEKGAMEADDATJSONTABLEMODEL_H
