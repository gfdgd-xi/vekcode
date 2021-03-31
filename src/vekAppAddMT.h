#ifndef VEKAPPADDMT_H
#define VEKAPPADDMT_H

#include "obj/common.h"
#include "obj/objectJson.h"
#include "obj/objectAppMT.h"
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
    void vekAppAddConnectObject(DockData*,QString,OBJAPP);
    ~vekAppAddMT();
public:
    Ui::vekAppAddMT *ui;
private:
    AppData* tempAppData=new AppData();
    DockData* tempDockData=new DockData();
    OBJAPP objType;
    vector<QString> _dockSystemVersion={"win10","win7","win81","win8","winxp","winxp64"};
    vector<QString> _dockVer={"win32","win64"};
    vector<QString> _dockWineVer={"wine","wine64"};
    void initAppAndDockData(DockData* _data,QString _appCID);
    bool vekAppAddObj(bool _forceState);
    bool vekAppConfigObj();
    void loadTableView(QTableView* qtv,AppData*);
    void setTableView(QTableView*);
    QStandardItemModel* tableModel;
    void objectAdd(QTableView*);
    void objectDelete(QTableView*);
    void dxvkOptionLinkState(bool cState);
    void dxvkOptionLoad();
    bool checkDocerOption();
    bool checkAppOption();
    bool checkDxvkOption();
    bool checkAllOption();
signals:
    void doneAddApp(DockData*,AppData*);
    void toObjectArgs(AppData);
    void _unDiyAppAdd();
    void _upData(DockData,AppData*,OBJAPP);
private slots:
    void objectButton();
    void plugsLoad();
    void clicked_rightMenu(const QPoint &pos);  //右键信号槽函数
    void onTaskBoxContextMenuEvent();
};

#endif // VEKADDGAME_H
