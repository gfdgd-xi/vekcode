#ifndef VEKAPPLISTVIEW_H
#define VEKAPPLISTVIEW_H

#include "vekAppData.h"
#include "../../vekAppOption.h"
#include "../../obj/objectExtend.h"
#include "../../obj/pObject.h"
#include "../../vekExtendDebug.h"
#include "../../vekExportJson.h"
#include "../../vekPackage.h"
#include "../../obj/common.h"
class vekAppListView:public QListView
{
    Q_OBJECT
public:
    vekAppListView(QWidget *parent = NULL);
    ~vekAppListView();
    void setListMap(std::map<QString,vekAppListView*> *pListMap,QTabWidget*);
    void addItem(SappData*);
    void objectExtendApp();
protected:
    void contextMenuEvent ( QContextMenuEvent * event );
    void mouseDoubleClickEvent ( QMouseEvent * event );
private slots:
    void moveSlot();
    void setItemSlot();
    void unAppAdd();
    void setUpDelData(SdockerData,SappData*,EADEType);
    void unExportJson();
    void unDebugApp();
    void unPackage();
public slots:
    void ObjectRun();
signals:
    void toObjectArgs_ptr(SappData*,EADEType);
    void toObjectArgs_cl(SappData);
    void _startTray();
    void setUpDelDataSignal(SdockerData*,SappData*);
    void setUpGroupTabIcoSignal();
private:
    vekAppOption *_vek_App_option=nullptr;
    vekExportJson* _vExportJson=nullptr;
    vekExtendDebug* _vExtendDebug=nullptr;
    vekPackage* _vPackage=nullptr;
    int  m_hitIndex;
    vekAppData* m_pModel;
    QTabWidget* mBox;
    //这里还有一个用处就是在弹出的菜单需要分组的名称
    std::map<QString,vekAppListView*> *m_pListMap;
    //记录每个菜单项对应的列表，才能知道要转移到那个分组
    std::map<QAction*,vekAppListView*> m_ActionMap;
    void vekWriteJsonData();
    void vekReadJsonData(QString jsonPath);
    void vekInitJsonData();
    void ExportJson();
    void PackageDeb();
    void startApp(Extend_App);
    void deleteDockerTab(QString,QString);
    std::vector<QStringList> vekWinetricks_cArgs();
    std::vector<QString> objectTypeStr={"运行程序",
                                        "调试运行(测试功能)",
                                        "修改程序设置",
                                        "导出配置文件",
                                        "导出deb安装包",
                                        "强行关闭本程序",
                                        "删除本程序"};
    QMenu *pMenu=nullptr;
};
#endif // vekAppListView_H
