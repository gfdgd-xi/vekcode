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
    void connectDockAutoData(SdockerData,SappData,SappDeployInfo);
    ~objectAppAT();
protected:
    void run();
private:
    //配置参数
    SappDeployData* _baseAutoSetJson=nullptr;
    //app数据
    SappData baseAppData={};
    //docker数据
    SdockerData baseDockData={};
    SappDeployInfo appJsonData;
    objectAppMT* objDiyAddApp=nullptr;
    QString jsonNetToStr(QString);
    QString jsonFileToStr(QString);
    JSONTYPE JsonType();
    bool jsonUnserialize(SappDeployInfo,JSONTYPE);
    void objectAutoObj();
    void objInstallRes();
    void objAppData();
    bool objDockerData();
signals:
    void Tips(QString TipsStr);
    void Error(QString ErrorInfo,bool cState);
    void Done(SdockerData*,SappData*);
};

#endif // VEKGAMEADDAUTOOBJECT_H
