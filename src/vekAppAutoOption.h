#ifndef VEKAPPAUTOOPTION_H
#define VEKAPPAUTOOPTION_H

#include "obj/common.h"
#include "obj/objectJson.h"
#include "obj/objectAppAT.h"
#include "view/jview/vekViewAT.h"
namespace Ui {
class vekAppAutoOption;
}

class vekAppAutoOption : public QWidget
{
    Q_OBJECT
public:
    explicit vekAppAutoOption(QWidget *parent = nullptr);
    ~vekAppAutoOption();
    void connectDockObject(SdockerData);
private:
    Ui::vekAppAutoOption *ui;
    SappData* autoAppData=nullptr;
    SdockerData* autoDockData=nullptr;
    void SetObject();
    void addAutoApp();
    void controlState(bool pState);
    void defalutValue();
signals:
    void _unAutoDock();
    void autoObjDock(SdockerData*,SappData*);
private slots:
    void TipText(QString TipInfo);
    void ErrorText(QString ErrorInfo,bool cState);
    void ObjDone(SdockerData*,SappData*);

};

#endif // VEKGAMEAUTOADD_H
