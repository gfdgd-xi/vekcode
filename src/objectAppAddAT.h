#ifndef OBJECTAPPADDGAMEAT_H
#define OBJECTAPPADDGAMEAT_H
#include "common.h"
#include "objectJson.h"
#include "objectAppAddMT.h"
#include "vekInitObject.h"
#include "vekGetCurl.h"

typedef struct{
    QString pJsonPath=nullptr;
    QString pDockName=nullptr;
    QString pDckPath=nullptr;
    QString pWineVersion=nullptr;
    QString pAppExePath=nullptr;
    BaseAppData* pBaseAppData=nullptr;
}ObjectAddDataAT;
class objectAppAddAT : public QThread
{
    Q_OBJECT
public:
    objectAppAddAT(ObjectAddDataAT);
    ~objectAppAddAT();
protected:
    void run();
private:
    BaseAutoSetJson* _baseAutoSetJson=nullptr;
    BaseAppData* baseAppData=nullptr;
    ObjectAddDataAT _objAddDataAT;
    objectAppAddMT* objDiyAddApp=nullptr;
    QString jsonPathTypeToStr(QString);
    bool jsonUnserialize(QString);
    void dataToBase();
    void objectAutoObj();
    void objInstallRes();
signals:
    void Tips(QString TipsStr);
    void Error(QString ErrorInfo,bool cState);
    void Done();
};

#endif // VEKGAMEADDAUTOOBJECT_H
