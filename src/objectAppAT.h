#ifndef OBJECTAPPAT_H
#define OBJECTAPPAT_H
#include "common.h"
#include "objectJson.h"
#include "objectAppMT.h"
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
class objectAppAT : public QThread
{
    Q_OBJECT
public:
    objectAppAT(ObjectAddDataAT);
    ~objectAppAT();
protected:
    void run();
private:
    //配置参数
    BaseAutoSetJson* _baseAutoSetJson=nullptr;
    BaseAppData* baseAppData=nullptr;

    ObjectAddDataAT _objAddDataAT;
    objectAppMT* objDiyAddApp=nullptr;
    QString jsonPathTypeToStr(QString);
    bool jsonUnserialize(QString);
    void dataToBase();
    void objectAutoObj();
    void objInstallRes();
    void objDockerData(QString);
signals:
    void Tips(QString TipsStr);
    void Error(QString ErrorInfo,bool cState);
    void Done();
};

#endif // VEKGAMEADDAUTOOBJECT_H
