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
    void updateWineNodeData(WineData);
    void updateDockerNodeData(DockData dockData,QString dockName);
    void deleteDockerNodeData(QString dockName);
    void addAppNodeData(DockData,AppData);
    void deleteAppNodeData(DockData,QString);
    void updateAppNodeData(DockData,AppData);
    void deleteWineNodeData(QString nwineName);
    bool unDataSerializeLocalData();
    bool unSerializeLocalWineApp(QString,QString urlData,UNJSONTYPE jsonType);
    void WriteLocalData();
    bool RemoteWineGitInfo(string info);
    AutoJson* unDataSerializeScriptData(AutoJson*,QString);
    QString GetRandomCID();
    void unSerializeBlackList(QString);
    json exportJson(DockData,QString);
private:
    json DataSerialize(json jsonData,const LocalData);
    void WriteJsonToFile(QString filePath,json jsonData);
    QString readJsonDataToStr(QString);
};

#endif // VEKOBJECTJSON_H
