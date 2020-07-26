#ifndef VEKATJSONMODEL_H
#define VEKATJSONMODEL_H

#include <QAbstractItemModel>
#include <QColor>
class vekATJsonModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit vekATJsonModel(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;

    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;

    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    void setList(QStringList *list, int row, int column);

signals:

public slots:

private:
    QStringList *list;
    int row, column;  //多少行、多少列
};

#endif // VEKGAMEADDATJSONTABLEMODEL_H
