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
    void connectDockAutoData(DockData,AppData,AppJson);
    ~objectAppAT();
protected:
    void run();
private:
    //配置参数
    AutoJson* _baseAutoSetJson=nullptr;
    //app数据
    AppData baseAppData={};
    //docker数据
    DockData baseDockData={};
    AppJson appJsonData;
    objectAppMT* objDiyAddApp=nullptr;
    QString jsonNetToStr(QString);
    QString jsonFileToStr(QString);
    JSONTYPE JsonType();
    bool jsonUnserialize(AppJson,JSONTYPE);
    void objectAutoObj();
    void objInstallRes();
    void objAppData();
    bool objDockerData();
signals:
    void Tips(QString TipsStr);
    void Error(QString ErrorInfo,bool cState);
    void Done(DockData*,AppData*);
};

#endif // VEKGAMEADDAUTOOBJECT_H
