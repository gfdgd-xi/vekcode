#ifndef DATACURL_H
#define DATACURL_H
#include "curl/curl.h"
#include "curl/easy.h"
#include <QThread>
#include <iostream>
#include <QFile>
#include <QProcess>
#include <QDebug>
using namespace std;
class datacurl:public QObject
{
    Q_OBJECT
public:
    explicit datacurl(QString,QString);
    ~datacurl();
    string vekGetData(QString urlStr);
protected:
       void run();
private:
       CURL *curl=nullptr;
       QString fileUrl;
       QString filePath;
       static datacurl *dcurl;
       CURLcode curl_res;
       FILE* file;
private:
     bool DownloadFile(std::string url);
     static size_t DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
     static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
public slots:
     void vUp();
     void SlotDeliverMessStatic(long,long,int);
signals:
     void SigDeliverMessStatic(long,long,int);
     void toPrgStr(long,long,int);
     void doneDown(bool,bool);
};

#endif // DATADOWNLOAD_H
