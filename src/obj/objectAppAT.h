#ifndef OBJECTAPPAT_H
#define OBJECTAPPAT_H
#include "common.h"
#include "objectJson.h"
#include "objectAppMT.h"
#include "pObject.h"
#include "objectGetCurl.h"

typedef enum{
    jNet,
    jFile,
    jDefault
}JSONTYPE;

class objectAppAT : public QThread
{
    Q_OBJECT
public:
    objectAppAT();
    void connectDockAutoData(BaseDockData,BaseAppData,BaseAppJson);
    ~objectAppAT();
protected:
    void run();
private:
    //配置参数
    BaseAutoSetJson* _baseAutoSetJson=nullptr;
    //app数据
    BaseAppData baseAppData={};
    //docker数据
    BaseDockData baseDockData={};
    BaseAppJson appJsonData;
    objectAppMT* objDiyAddApp=nullptr;
    QString jsonNetToStr(QString);
    QString jsonFileToStr(QString);
    JSONTYPE JsonType();
    bool jsonUnserialize(BaseAppJson,JSONTYPE);
    void objectAutoObj();
    void objInstallRes();
    void objAppData();
    bool objDockerData();
signals:
    void Tips(QString TipsStr);
    void Error(QString ErrorInfo,bool cState);
    void Done(BaseDockData*,BaseAppData*);
};

#endif // VEKGAMEADDAUTOOBJECT_H
