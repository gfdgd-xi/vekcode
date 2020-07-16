#ifndef OBJECTADDGAMEAT_H
#define OBJECTADDGAMEAT_H
#include "common.h"
#include "objectJson.h"
#include "objectAddGameMT.h"
#include "vekInitObject.h"
#include "vekGetCurl.h"

typedef struct{
    QString pJsonPath=nullptr;
    QString pDockName=nullptr;
    QString pDckPath=nullptr;
    QString pWineVersion=nullptr;
    QString pGameExePath=nullptr;
    BaseGameData* pBaseGameData=nullptr;
}ObjectAddDataAT;
class objectAddGameAT : public QThread
{
    Q_OBJECT
public:
    objectAddGameAT(ObjectAddDataAT);
    ~objectAddGameAT();
protected:
    void run();
private:
    BaseAutoSetJson* _baseAutoSetJson=nullptr;
    BaseGameData* baseGameData=nullptr;
    ObjectAddDataAT _objAddDataAT;
    objectAddGameMT* objDiyAddGame=nullptr;
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
