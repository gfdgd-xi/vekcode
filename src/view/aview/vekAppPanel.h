#ifndef VEKAPPPANEL_H
#define VEKAPPPANEL_H

#include "vekAppListView.h"
#include "../../vekAppAddMT.h"
#include "../../vekAppAddMulti.h"
#include "../../vekAppAddAT.h"
#include "../../obj/common.h"
#include "../../obj/objectTray.h"
class vekAppPanel : public QWidget
{
    Q_OBJECT
public:
    vekAppPanel(QWidget *parent = 0);
    ~vekAppPanel();   
public slots:
    void addAppSlot();
    void addGroupSlot(BaseDockData* dcokData);
    void addAppObject(BaseDockData* dcokData,BaseAppData* appData);
    void upTabIco();
    void objectRunApp();
    void objAppInstall();
    void objInitDock();
private:
    QTabWidget *m_pBox;
    vekAppAddMT* vek_app_add=nullptr;
    vekAppAddMulti* vek_app_multi_add=nullptr;
    vekAppAddAT* vek_app_add_auto=nullptr;
    objectTray* objTray=nullptr;
    void unMultAppAdd();
    void unDiyAppAdd();
    void unAutoDock();
    void addAppDiy();
    void addAppAuto();
    void startLoadData();
    std::map<QString,vekAppListView*> *m_pListMap;    //记录分组和分组名字的映射关系，好在转移图标时知道转移到那个分组
    void vekLoadJsonData();
    void vek_InitTabWidgetListApp();
    string GetReData(QString);

signals:
    void toObjAutoArgs_ptr();
};
#endif // vekAppPanel_H
