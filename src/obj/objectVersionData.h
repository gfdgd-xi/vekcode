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
    void repair_Wineprc_Stalonetray_Winetricks();
    void repair_Stalonetray();
    void repair_Wineprc();
    void repair_Winetricks();
private:
    QString vekUpInfo="https://bitbucket.org/jacklee_CN/vekserver/raw/f446b578a52c64aa0ca26bfe1dfe11cc4976a14c/vekUpdateInfo.json";
    bool getVersionStr();
    bool unVersionData(string vData);
    void copyFile(QString);
    void repairFilePerm(QString);   
    QStringList pFileName={"wineprc","stalonetray","winetricks"};
};

#endif // OBJECTVERSIONDATA_H
