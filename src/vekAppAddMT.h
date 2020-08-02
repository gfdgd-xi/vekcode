#ifndef VEKAPPADDMT_H
#define VEKAPPADDMT_H

#include "common.h"
#include "objectJson.h"
#include "objectAppAddMT.h"
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
    BaseAppData* tempData=nullptr;
    BaseAppData* oldData=nullptr;
    QString tempCID=nullptr;
    objectTypeView objType;
    vector<QString> _dockSystemVersion={"win10","win7","win81","win8","winxp64"};
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
    void vekAppAddConnectObject(BaseAppData* _data,objectTypeView);
    void clicked_rightMenu(const QPoint &pos);  //右键信号槽函数
    void onTaskBoxContextMenuEvent();
};

#endif // VEKADDGAME_H
