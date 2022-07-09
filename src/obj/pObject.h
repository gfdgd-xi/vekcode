#ifndef POBJECT_H
#define POBJECT_H

#include "common.h"
#include "baseData.h"

static std::vector<QString> styleNames= {"Default","Dark","Light"};

class pObject
{
public:
static void vekTip(QString tipInfo);
static void vekError(QString tipInfo);
static bool vekMesg(QString tipText);
static QStringList dockerRegeditStr(QString rObj,QString rPath,QString rKey,QString rTValue,QString rValue);
static QString getFileStr(QString filePath);
static QString pathNullToStr(QString str);
static void saveStrToFile(QString strFile,QString filePath);
static SdockerData getDockerData(QString dockName);
static SappData getAppData(SdockerData dockData,QString appCID);
static void saveDockerDataToJson(SdockerData dockData,QString dockName);
static void addAppDataToJson(SdockerData dockData,SappData appData);
static void saveAppDataToJson(SdockerData dockData,SappData appData);
static void deleteWineDataToJson(QString wineName);
static void qwidgetGeometry(QWidget*);
static void oLogs(QString str);
};
#endif // LOADSTYLE_H
