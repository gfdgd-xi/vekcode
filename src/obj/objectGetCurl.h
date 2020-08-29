#ifndef OBJECTGETCURL_H
#define OBJECTGETCURL_H

#include "curl/curl.h"
#include "curl/easy.h"
#include "common.h"

class objectGetCurl: public QThread
{
    Q_OBJECT
public:
    explicit objectGetCurl(QObject *parent = nullptr);
    ~objectGetCurl();
    std::string vekGetData(std::string url);
    QString outputPrgressText;
    QString fileName;
    void DoewloadPlugs(BaseWineData _wd);
private:
       CURL *curl=nullptr;
       bool DownloadFile(std::string url,std::string path);
       static size_t DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
       static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
public slots:
     void outLogText(string text);
signals:
     void curlPrgressSignals();

};

#endif // VEKGETINFOCURLTHREAD_H
