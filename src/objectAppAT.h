#ifndef OBJECTAPPAT_H
#define OBJECTAPPAT_H
#include "common.h"
#include "objectJson.h"
#include "objectAppMT.h"
#include "vekInitObject.h"
#include "vekGetCurl.h"

class objectAppAT : public QThread
{
    Q_OBJECT
public:
    objectAppAT();
    void connectDockAutoData(BaseDockData,BaseAppData,QString);
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
    QString jsonCfg=nullptr;
    objectAppMT* objDiyAddApp=nullptr;
    QString jsonPathTypeToStr(QString);
    bool JsonType(QString);
    bool jsonUnserialize(QString);
    void objectAutoObj();
    void objInstallRes();
    void objAppData();
    bool objDockerData(QString);
signals:
    void Tips(QString TipsStr);
    void Error(QString ErrorInfo,bool cState);
    void Done();
};

#endif // VEKGAMEADDAUTOOBJECT_H
