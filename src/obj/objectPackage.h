#ifndef OBJECTPACKAGE_H
#define OBJECTPACKAGE_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include "baseData.h"
#include <QDebug>
class objectPackage : public QObject
{
    Q_OBJECT
public:
    objectPackage(SdockerData,Spackage,QString);
   ~objectPackage();
    void EXPackage();
    void EXToolDeb();
private:
    QProcess* v_package=nullptr;
    QString _tagdir=QDir::homePath()+"/.deepinwine/";
    QString _password;
    QString d_path;
    QString p_package_tool_path;
    SdockerData d_data;
    Spackage p_data;   
private slots:
    void ontRead();
signals:
    void slot_logs();  
    void outQStr(QString);
};

#endif // OBJECTPACKAGE_H
