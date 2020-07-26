#include "vekATJsonModel.h"

vekATJsonModel::vekATJsonModel(QObject *parent) :
    QAbstractItemModel(parent)
{

}
//list的setter方法
void vekATJsonModel::setList(QStringList *list, int row, int column)
{
    this->list = list;
    this->column = column;
    this->row = row;
}

//建立索引
QModelIndex vekATJsonModel::index(int row, int column, const QModelIndex &parent) const
{
    int i = row * this->column + column;
    return createIndex(row, column);
}

QModelIndex vekATJsonModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int vekATJsonModel::rowCount(const QModelIndex &parent) const
{
    return row;
}

int vekATJsonModel::columnCount(const QModelIndex &parent) const
{
    return column;
}

QVariant vekATJsonModel::data(const QModelIndex &index, int role) const
{
    if( role == Qt::CheckStateRole)
        return QVariant();
    if( role == Qt::TextAlignmentRole)
        return (Qt::AlignVCenter);
    if( role == Qt::ForegroundRole)
        return QColor(250, 150, 150);
    int row = index.row();
    int column = index.column();
    int i = row * this->column + column;
    return list->at(i);
}
