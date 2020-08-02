#ifndef VEKAPPPANEL_H
#define VEKAPPPANEL_H

#include "vekAppListView.h"
#include "vekAppAddMT.h"
#include "vekAppAddMulti.h"
#include "vekAppAddAT.h"
#include "common.h"
#include "objectTray.h"
class vekAppPanel : public QWidget
{
    Q_OBJECT
public:
    vekAppPanel(QWidget *parent = 0);
    ~vekAppPanel();   
public slots:
    void addGroupSlot(BaseAppData* data);
    void addAppSlot();
    void addAppObject(BaseAppData*);
    void objectRunApp();
    void objAppInstall();
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
    void vek_InitTabWidgetListApp();   
    std::map<QString,vekAppListView*> *m_pListMap;    //记录分组和分组名字的映射关系，好在转移图标时知道转移到那个分组
    void vekLoadJsonData();
    string GetReData(QString);
signals:
    void toObjDiyArgs_ptr(BaseAppData*,objectTypeView);
    void toObjAutoArgs_ptr(BaseAppData*);
    void toObjectArgs(BaseAppData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);
};
#endif // vekAppPanel_H
