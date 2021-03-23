#ifndef VEK_H
#define VEK_H
#include "vekWineOption.h"
#include "vekAbout.h"
#include "vekAppAddMT.h"
#include "view/aview/vekAppListView.h"
#include "obj/common.h"
#include "vekExtendDebug.h"
#include "vekSourceEdit.h"
#include "obj/objectProcManage.h"
#include "obj/objectTray.h"
#include "QTranslator"
#include "vekPackage.h"

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
    vekWineOption *_vek_wine_option=nullptr;
    vekAbout* _vek_About=nullptr;
    vekSourceEdit* _vek_source_esit=nullptr;
    vekPackage* _vek_Package=nullptr;
    objectTray* objTray=nullptr;
    void setProcRow(); 
public slots:
    void startTray();
    void exitTray(bool);
    void on_action_About_triggered();
private slots:
    void vekAddApp();
    void vekRunApp();
    void on_action_AddApp_triggered();
    void on_action_Exit_triggered();
    void on_action_WineInstall_triggered();
    void on_action_EditSource_triggered();
    void unInitWineOption();
    void unVekAbout();
    void installApp();
    void unSourceEdit();
    void setAppSize();
    void vekStyle();
    void vekLanguage();
    void option_Dev();
    void addInitDocker();
};
#endif // VEK_H
