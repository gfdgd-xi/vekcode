#ifndef VEKAPPADDAT_H
#define VEKAPPADDAT_H

#include "obj/common.h"
#include "obj/objectJson.h"
#include "obj/objectAppAT.h"
#include "view/jview/vekViewAT.h"
namespace Ui {
class vekAppAddAT;
}

class vekAppAddAT : public QWidget
{
    Q_OBJECT
public:
    explicit vekAppAddAT(QWidget *parent = nullptr);
    ~vekAppAddAT();
    void connectDockObject();
private:
    Ui::vekAppAddAT *ui;
    AppData* autoAppData=nullptr;
    DockData* autoDockData=nullptr;
    void SetObject();
    void addAutoApp();
    void controlState(bool pState);
signals:
    void _unAutoDock();
    void autoObjDock(DockData *,AppData *);
private slots:
    void TipText(QString TipInfo);
    void ErrorText(QString ErrorInfo,bool cState);
    void ObjDone(DockData*,AppData*);

};

#endif // VEKGAMEAUTOADD_H
