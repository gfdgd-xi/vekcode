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
    void vekAppAddConnectObject(SdockerData*,QString,EADEType);
    ~vekAppAddMT();
public:
    Ui::vekAppAddMT *ui;
private:
    SappData* tempAppData=new SappData();
    SdockerData* tempDockData=new SdockerData();
    EADEType objType;
    vector<QString> _dockSystemVersion={"win10","win7","win81","win8","winxp","winxp64"};
    vector<QString> _dockVer={"win32","win64"};
    vector<QString> _dockWineVer={"wine","wine64"};
    void initAppAndDockData(SdockerData* _data,QString _appCID);
    bool vekAppAddObj(bool _forceState);
    bool vekAppConfigObj();
    void loadTableView(QTableView* qtv,SappData*);
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
    void doneAddApp(SdockerData*,SappData*);
    void toObjectArgs(SappData);
    void _unDiyAppAdd();
    void _upData(SdockerData,SappData*,EADEType);
private slots:
    void objectButton();
    void plugsLoad();
    void clicked_rightMenu(const QPoint &pos);  //右键信号槽函数
    void onTaskBoxContextMenuEvent();
};

#endif // VEKADDGAME_H
