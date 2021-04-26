#ifndef OBJECTVERSIONDATA_H
#define OBJECTVERSIONDATA_H

#include "objectGetCurl.h"
#include "objectJson.h"
#include "pObject.h"

class objectVersionData
{
public:
    objectVersionData();
    ~objectVersionData();
    bool upDataVek();
    QString sVersion;
    QString sUrlLogs;
    QString sUrlFile;
    QString sUrlFilePassword;
    QString sFileSHA512;
private:
    QString vekUpInfo="https://gitee.com/JackLee02/vekGame/raw/master/vekUpdateInfo.json";
    bool getVersionStr();
    bool unVersionData(string vData);

};

#endif // OBJECTVERSIONDATA_H
