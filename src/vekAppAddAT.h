#ifndef VEKAPPADDAT_H
#define VEKAPPADDAT_H

#include "common.h"
#include "objectJson.h"
#include "objectAppAT.h"
#include "vekInitObject.h"
#include "vekATJsonView.h"
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
    BaseAppData* autoAppData=new BaseAppData();
    BaseDockData* autoDockData=new BaseDockData();
    void SetObject();
    void addAutoApp();
    void controlState(bool pState);
signals:
    void _unAutoDock();
    void autoObjDock(BaseDockData*,BaseAppData*);
private slots:
    void TipText(QString TipInfo);
    void ErrorText(QString ErrorInfo,bool cState);
    void ObjDone();
};

#endif // VEKGAMEAUTOADD_H
