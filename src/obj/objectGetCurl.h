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
private:
    CURL *curl=nullptr;
};

#endif // VEKGETINFOCURLTHREAD_H
