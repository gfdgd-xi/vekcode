﻿#ifndef VEKAPPADDMT_H
#define VEKAPPADDMT_H

#include "common.h"
#include "objectJson.h"
#include "objectAppMT.h"
#include "vekInitObject.h"
#include <QTableView>
#include <QStandardItemModel>
namespace Ui {
class vekAppAddMT;
}

class vekAppAddMT : public QWidget
{
    Q_OBJECT
public:
    explicit vekAppAddMT(QWidget *parent = nullptr);
    ~vekAppAddMT();
public:
    Ui::vekAppAddMT *ui;
private:
    BaseAppData* tempAppData=nullptr;
    BaseDockData* temDockData=nullptr;
    objectTypeView objType;
    vector<QString> _dockSystemVersion={"win10","win7","win81","win8","winxp64"};
    vector<QString> _dockVer={"win32","win64"};
    vector<QString> _dockWineVer={"wine","wine64"};
    bool vekAppAddObj(bool _forceState);
    bool vekAppConfigObj();
    void loadTableView(QTableView* qtv,BaseAppData*);
    void setTableView(QTableView*);
    QStandardItemModel* tableModel;
    void objectAdd(QTableView*);
    void objectDelete(QTableView*);
    void dxvkOptionLinkState(bool cState);
signals:
    void doneAddApp(BaseAppData*);
    void toObjectArgs(BaseAppData);
    void _unDiyAppAdd();
    void _upData(BaseAppData*,objectTypeView);
private slots:
    void objectButton();
    void dxvkOptionLink();
    void vekAppAddConnectObject(BaseDockData*,QString,objectTypeView);
    void clicked_rightMenu(const QPoint &pos);  //右键信号槽函数
    void onTaskBoxContextMenuEvent();
};

#endif // VEKADDGAME_H
