#ifndef VEK_CURLTHREAD_H
#define VEK_CURLTHREAD_H
#include "curl/curl.h"
#include "curl/easy.h"
#include <iostream>

class vek_CurlThread
{
public:
    vek_CurlThread();
    int downloadFile();
};

#endif // VEKDOWNLOADCURLTHREAD_H
