#ifndef VEK_H
#define VEK_H
#include "vekWineOption.h"
#include "vekAbout.h"
#include "vekAppOption.h"
#include "view/aview/vekAppListView.h"
#include "obj/common.h"
#include "vekExtendDebug.h"
#include "vekSourceEdit.h"
#include "obj/objectProcManage.h"
#include "obj/objectVersionData.h"
#include "QTranslator"
#include "vekPackage.h"

#include <qdesktopservices.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class vek;
}
QT_END_NAMESPACE
class vek : public QWidget
{
    Q_OBJECT

public:
    explicit vek(QWidget *parent = nullptr);
    ~vek();
    QApplication* vekThis;
    void connectObject();   
private:
    Ui::vek *ui=nullptr;
    //vekWineOption *_vek_wine_option=nullptr;
    //vekAbout* _vek_About=nullptr;
    vekPackage* _vek_Package=nullptr;
    objectTray* objTray=nullptr;
    QString vek_winetricks_server="https://gitee.com/JackLee02/vekGame/raw/master/vekWinetricksServer.json";
    bool getWinetricksServerJson();
    void loadWinetricksServerJson();
public slots:
    void setProcRow(int);
    void on_action_About_triggered();
private slots:
    void vekAddApp();
    void on_action_AddApp_triggered();
    void on_action_Exit_triggered();
    void on_action_WineInstall_triggered();
    void on_action_EditSource_triggered();
    void on_action_Clear_Ico();
    void installApp();
    void setAppSize();
    void vekStyle();
    void vekLanguage();
    void addInitDocker();
    void wServerTest();
    void wSetHosts();
    void wCurrentUrl();
    void wCurrentEngine();
    void hFileHash();
    void changeQTabWidgetStyleWest();
    void changeQTabWidgetStyleNorth();
    void repair_Stalonetray();
    void repair_Winetricks();
    void repair_Wineprc();
    void uenginInst();
    void uengineRun();
    void uengineInstApp();
    void uengineUnInst();
};
#endif // VEK_H
