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
    void updateAppNodeData(QString dockName,BaseAppData base_wine_data);
    void deleteAppNodeData(QString nodeName);
    void deleteWineNodeData(QString nwineName);
    bool unDataSerializeLocalData();
    bool unSerializeLocalWineApp(QString,QString urlData,UNJSONTYPE jsonType);
    void WriteLocalData();
    bool RemoteWineGitInfo(string info);
    BaseAutoSetJson* unDataSerializeScriptData(BaseAutoSetJson*,QString);
    QString GetRandomCID();
    void unSerializeBlackList(QString);
    json exportJson(BaseAppData);
private:
    json DataSerialize(json jsonData,const BaseLocalData);
    void WriteJsonToFile(QString filePath,json jsonData);
    QString readJsonDataToStr(QString);
};

#endif // VEKOBJECTJSON_H
