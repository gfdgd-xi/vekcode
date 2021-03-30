#ifndef DATACURL_H
#define DATACURL_H
#include "curl/curl.h"
#include "curl/easy.h"
#include <QThread>
#include <iostream>
#include <QDir>
#include <QFile>
#include <QProcess>
using namespace std;
class datacurl:public QThread
{
    Q_OBJECT
public:
    explicit datacurl(QObject *parent = nullptr);
    ~datacurl();
    void SetUrlPath(QString,QString);
    string vekGetData(QString urlStr);
protected:
       void run();
private:
       CURL *curl=nullptr;
       QString fileUrl;
       QString filePath;
private:
    bool DownloadFile(std::string url,std::string path);
public slots:
    void outLogText(long,long,int);
signals:
     void curlPrgressSignals(long,long,int);
     void doneDown();
};

#endif // DATADOWNLOAD_H
