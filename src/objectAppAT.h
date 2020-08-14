#ifndef OBJECTAPPAT_H
#define OBJECTAPPAT_H
#include "common.h"
#include "objectJson.h"
#include "objectAppMT.h"
#include "vekInitObject.h"
#include "vekGetCurl.h"

typedef struct{
    QString pJsonPath=nullptr;
    QString pAppExePath=nullptr;
    QString pWinePath=nullptr;
    QString pWineVersion=nullptr;
    QString pDockPath=nullptr;
    QString pDockName=nullptr;
    QString pDockSysVer=nullptr;
    QString pDockVer=nullptr;
    bool pMonoState=false;
    bool pGeckoState=false;
}ObjectDockAT;
class objectAppAT : public QThread
{
    Q_OBJECT
public:
    objectAppAT();
    ~objectAppAT();
protected:
    void run();
private:
    //配置参数
    BaseAutoSetJson* _baseAutoSetJson=nullptr;
    //app数据
    BaseAppData baseAppData={};
    //传入Dock数据
    ObjectDockAT _objAddDataAT;
    //docker数据
    BaseDockData baseDockData={};
    objectAppMT* objDiyAddApp=nullptr;
    QString jsonPathTypeToStr(QString);
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
