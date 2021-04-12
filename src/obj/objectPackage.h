#ifndef OBJECTPACKAGE_H
#define OBJECTPACKAGE_H

#include "baseData.h"
#include <QProcess>
#include <QDir>
class objectPackage
{
public:
    objectPackage(SdockerData,Spackage);
   ~objectPackage();
private:
    QProcess* v_package;
    QString _tagdir=QDir::homePath()+"/.deepinwine/";
    QString _password;
    QString d_path;
    QString p_package_tool_path;
    SdockerData d_data;
    Spackage p_data;
    int CopyDocker();
    int InstallToolDeb();
    int RepairToolLib();
    int RepairToolChmod();
    bool StatCheck(int);
    int EXPackage();
signals:
    void slot_logs();
};

#endif // OBJECTPACKAGE_H
