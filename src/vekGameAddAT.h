#ifndef VEKGAMEADDAT_H
#define VEKGAMEADDAT_H

#include "common.h"
#include "objectJson.h"
#include "objectAddGameAT.h"
#include "vekInitObject.h"
#include "vekATJsonView.h"
namespace Ui {
class vekGameAddAT;
}

class vekGameAddAT : public QWidget
{
    Q_OBJECT
public:
    explicit vekGameAddAT(QWidget *parent = nullptr);
    ~vekGameAddAT();

private:
    Ui::vekGameAddAT *ui;
    BaseGameData* autoGameData=nullptr;
    objectAddGameAT* objAutoAddGame=nullptr;
    void connectDockObject();
    void SetObject();
    void addAutoGame();
    QString JsonType(QString);
    void controlState(bool pState);
signals:
    void _unAutoDock();
    void autoObjDock(BaseGameData*);
private slots:
    void connectDockObject(BaseGameData* _data);
    void TipText(QString TipInfo);
    void ErrorText(QString ErrorInfo,bool cState);
    void ObjDone();
};

#endif // VEKGAMEAUTOADD_H
