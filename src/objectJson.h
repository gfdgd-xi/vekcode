#ifndef OBJECTJSON_H
#define OBJECTJSON_H

#include "json.hpp"
#include "common.h"
#include "baseData.h"
using json = nlohmann::json;
typedef enum{
    unJsonWineList,
    unJsonGameList,
}UNJSONTYPE;
class objectJson
{
public:
    objectJson();
    ~objectJson();
    void updateWineNodeData(BaseWineData);
    void updateDockerNodeData(BaseDockData dockData,QString dockName);
    void deleteDockerNodeData(QString dockName);
    void deleteAppNodeData(BaseDockData,QString);
    void updateAppNodeData(BaseDockData,BaseAppData);
    void deleteWineNodeData(QString nwineName);
    bool unDataSerializeLocalData();
    bool unSerializeLocalWineApp(QString,QString urlData,UNJSONTYPE jsonType);
    void WriteLocalData();
    bool RemoteWineGitInfo(string info);
    BaseAutoSetJson* unDataSerializeScriptData(BaseAutoSetJson*,QString);
    QString GetRandomCID();
    void unSerializeBlackList(QString);
    json exportJson(BaseDockData,QString);
private:
    json DataSerialize(json jsonData,const BaseLocalData);
    void WriteJsonToFile(QString filePath,json jsonData);
    QString readJsonDataToStr(QString);
};

#endif // VEKOBJECTJSON_H
