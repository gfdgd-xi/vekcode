#ifndef VEKWINEOPTION_H
#define VEKWINEOPTION_H

#include "obj/objectGitWine.h"
#include "obj/common.h"
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QTableView>
#include <QtConcurrent/QtConcurrentRun>
namespace Ui {
class vekWineOption;
}

class vekWineOption : public QWidget
{
    Q_OBJECT

public:
    explicit vekWineOption(QWidget *parent = nullptr);
    void dealclicked();
    ~vekWineOption();
private slots:
    void appendTextToLog();
    void overGitThreadSignals(bool);
    void on_toolButton();
    void installWine(QString);
    void deleteWine(QString);
    void clicked_rightMenu(const QPoint &/*pos*/);
    void onTaskBoxContextMenuEvent();
private:
    Ui::vekWineOption *ui;
    objectGitWine *githread;
    QStandardItemModel *ItemModelWinen;
    QStandardItemModel *ItemModelWined;
    QPoint _pos;
    void GetWineGitInfo();
    void WineVersionComoboBox();
    void controlState(bool pState);
    void loadData();
    void LoadWineList(QTableView*);
    void AddWine();
    void RemoveWine();  
signals:
    void _unInitWineOption();
};

#endif // VEKOPTION_H
