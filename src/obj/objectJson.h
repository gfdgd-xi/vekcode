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
    void updateWineNodeData(SwineData);
    void updateDockerNodeData(SdockerData dockData,QString dockName);
    void deleteDockerNodeData(QString dockName);
    void addAppNodeData(SdockerData,SappData);
    void deleteAppNodeData(SdockerData,QString);
    void updateAppNodeData(SdockerData,SappData);
    void deleteWineNodeData(QString nwineName);
    bool unDataSerializeLocalData();
    bool unSrcData(std::string tData);
    bool unSerializeLocalWineApp(QString,QString urlData,UNJSONTYPE jsonType);
    void WriteLocalData();
    bool RemoteWineGitInfo(string info);
    SappDeployData* unDataSerializeScriptData(SappDeployData*,QString);
    QString GetRandomCID();
    void unSerializeBlackList(QString);
    json exportJson(SdockerData,QString);
private:
    json DataSerialize(json jsonData,const SlocalGloablData);
    void WriteJsonToFile(QString filePath,json jsonData);
    QString readJsonDataToStr(QString);
};

#endif // VEKOBJECTJSON_H
