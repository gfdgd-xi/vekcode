#ifndef VEKAPPPANEL_H
#define VEKAPPPANEL_H

#include "vekAppListView.h"
#include "../../vekAppOption.h"
#include "../../vekAppAddModel.h"
#include "../../vekAppAutoOption.h"
#include "../../vekDockerOption.h"
#include "../../obj/common.h"
#include "../../obj/objectTray.h"
#include "vekAppCustomBarStyle.h"
typedef enum{
    INSTALLAPP,
    INITDOCKER
}INITTYPE;

class vekAppPanel : public QWidget
{
    Q_OBJECT
public:
    vekAppPanel(QWidget *parent = 0);
    ~vekAppPanel();   
public slots:
    void addAppSlot();
    void addGroupSlot(SdockerData* dcokData);
    void addAppObject(SdockerData* dcokData,SappData* appData);
    void upTabIco();
    void objectRunApp();
    void objInitDocker(INITTYPE);
    void changeQTwidgetStyle(QTabWidget::TabPosition);
private:
    QTabWidget *m_pBox;
    vekAppOption* vek_app_add=nullptr;
    vekAppAddModel* vek_app_add_model=nullptr;
    vekAppAutoOption* vek_app_add_auto=nullptr;
    vekDockerOption* vek_docker_option=nullptr;
    objectTray* objTray=nullptr;
    int cindex;
    void unMultAppAdd();
    void unDiyAppAdd();
    void unAutoDock();
    void unDockOption();
    void AddAppDiyType();
    void AddAppAutoType();
    void startLoadData();
    std::map<QString,vekAppListView*> *m_pListMap;    //记录分组和分组名字的映射关系，好在转移图标时知道转移到那个分组
    void vek_InitTabWidgetListApp();
    string GetReData(QString);
    void setDockerSlot();
    QMenu *pMenu=nullptr;
    vector<QStringList> vekWinetricks_cArgs();
    QStringList dockerops={
        "容器基础设置",
        "Winecfg设置",
        "容器注册表",
        "容器控制面板",
        "软件卸载|增加",
        "删除当前容器",
        "winetricks-GUI",
        "winetricks-CMD",

    };
private slots:
    void deleteGroupSlot(bool);
    void DockerObject();
protected:
    void contextMenuEvent ( QContextMenuEvent * event );
signals:
    void toObjAutoArgs_ptr();
};
#endif // vekAppPanel_H
