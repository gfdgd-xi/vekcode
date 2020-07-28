#ifndef VEKATJSONMODEL_H
#define VEKATJSONMODEL_H

#include "common.h"
class vekATJsonModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit vekATJsonModel(QObject *parent = nullptr);
    ~vekATJsonModel();
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const ;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
private:
    std::vector<BaseGameData*> m_ItemDataVec;
};

#endif // VEKGAMEADDATJSONTABLEMODEL_H
