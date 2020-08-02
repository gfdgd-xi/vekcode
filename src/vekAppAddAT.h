#ifndef VEKAPPADDAT_H
#define VEKAPPADDAT_H

#include "common.h"
#include "objectJson.h"
#include "objectAppAddAT.h"
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

private:
    Ui::vekAppAddAT *ui;
    BaseAppData* autoAppData=nullptr;
    objectAppAddAT* objAutoAddApp=nullptr;
    void connectDockObject();
    void SetObject();
    void addAutoApp();
    QString JsonType(QString);
    void controlState(bool pState);
signals:
    void _unAutoDock();
    void autoObjDock(BaseAppData*);
private slots:
    void connectDockObject(BaseAppData* _data);
    void TipText(QString TipInfo);
    void ErrorText(QString ErrorInfo,bool cState);
    void ObjDone();
};

#endif // VEKGAMEAUTOADD_H
