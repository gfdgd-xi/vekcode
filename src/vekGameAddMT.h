#ifndef VEKGAMEADDMT_H
#define VEKGAMEADDMT_H

#include "common.h"
#include "objectJson.h"
#include "objectAddGameMT.h"
#include "vekInitObject.h"
#include <QTableView>
#include <QStandardItemModel>
namespace Ui {
class vekGameAddMT;
}

class vekGameAddMT : public QWidget
{
    Q_OBJECT
public:
    explicit vekGameAddMT(QWidget *parent = nullptr);
    ~vekGameAddMT();
public:
    Ui::vekGameAddMT *ui;
private:
    BaseGameData* tempData=nullptr;
    BaseGameData* oldData=nullptr;
    QString tempCID=nullptr;
    objectTypeView objType;
    vector<QString> _dockSystemVersion={"win10","win7","win81","win8","winxp64"};
    bool vekGameAddObj(bool _forceState);
    bool vekGameConfigObj();
    void loadTableView(QTableView* qtv,BaseGameData*);
    void setTableView(QTableView*);
    QStandardItemModel* tableModel;
    void objectAdd(QTableView*);
    void objectDelete(QTableView*);
    void dxvkOptionLinkState(bool cState);
signals:
    void doneAddGame(BaseGameData*);
    void toObjectArgs(BaseGameData);
    void _unDiyGameAdd();
    void _upData(BaseGameData*,objectTypeView);
private slots:
    void objectButton();
    void dxvkOptionLink();
    void vekGameAddConnectObject(BaseGameData* _data,objectTypeView);
    void clicked_rightMenu(const QPoint &pos);  //右键信号槽函数
    void onTaskBoxContextMenuEvent();
};

#endif // VEKADDGAME_H
