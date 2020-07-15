#ifndef VEKGETCURL_H
#define VEKGETCURL_H

#include "curl/curl.h"
#include "curl/easy.h"
#include "common.h"

class vekGetCurl: public QThread
{
    Q_OBJECT
public:
    explicit vekGetCurl(QObject *parent = nullptr);
    ~vekGetCurl();
    std::string vekGetData(std::string url);
    BaseWineData _wd;
    QString outputPrgressText;
    QString fileName;
protected:
       void run();
private:
       CURL *curl=nullptr;
       bool DownloadFile(std::string url,std::string path);
public slots:
     void outLogText(string text);
signals:
     void curlPrgressSignals();
};

#endif // VEKGETINFOCURLTHREAD_H
