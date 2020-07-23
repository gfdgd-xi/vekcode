#ifndef VEK_H
#define VEK_H
#include "vekWineOption.h"
#include "vekAbout.h"
#include "vekGameAddMT.h"
#include "vekInitObject.h"
#include "vekGameListView.h"
#include "common.h"
#include "vekExtendDebug.h"
#include "vekSourceEdit.h"
#include "objectProcManage.h"
#include "src/objectTray.h"

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
    void connectObject();
private:
    Ui::vek *ui=nullptr;
    vekWineOption *_vek_wine_option=nullptr;
    vekAbout* _vek_About=nullptr;
    vekSourceEdit* _vek_source_esit=nullptr;
    objectTray* objTray=nullptr;
public slots:
    void startTray();
    void exitTray(bool);
    void on_action_About_triggered();
private slots:
    void vekAddGame();
    void vekRunGame();
    void on_action_AddGame_triggered();   
    void on_action_Exit_triggered();
    void on_action_WineInstall_triggered();
    void on_action_EditSource_triggered();
    void unInitWineOption();
    void unVekAbout();
    void installApp();
    void unSourceEdit();
signals:
    void toObjectArgs(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);
};
#endif // VEK_H
