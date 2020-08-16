#include "vekGetCurl.h"
vekGetCurl::vekGetCurl(QObject *parent) : QThread(parent)
{
}
vekGetCurl::~vekGetCurl()
{
}
static size_t getData(void *buffer, size_t sz, size_t nmemb, void *writer)
{
    std::string* psResponse =static_cast<std::string *>(writer);
    size_t size = sz * nmemb;
    psResponse->append(static_cast<char*>(buffer), size);
    return sz * nmemb;
}
std::string vekGetCurl::vekGetData(std::string url){
    CURL *curl=curl_easy_init();
    CURLcode res =CURLE_QUOTE_ERROR;
    std::string strRsp;
    while(res==CURLE_QUOTE_ERROR){
        std::string strTmpStr;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_HEADER, false);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strTmpStr);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK||
                QString::fromStdString(strTmpStr).contains("404",Qt::CaseSensitive)||
                QString::fromStdString(strTmpStr).contains("500",Qt::CaseSensitive)||
                QString::fromStdString(strTmpStr).contains("403",Qt::CaseSensitive)||
                QString::fromStdString(strTmpStr).contains("502",Qt::CaseSensitive)||
                res==CURLE_QUOTE_ERROR)
        {
            strRsp = "error";
            break;
        }else{
            strRsp = strTmpStr;
            break;
        }
    }
    curl_easy_cleanup(curl);
    return strRsp;
}
size_t vekGetCurl::DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam)
{
    FILE* fp = (FILE*)pParam;
    size_t nWrite = fwrite(pBuffer, nSize, nMemByte, fp);
    return nWrite;
}
static vekGetCurl* dThis=nullptr;
double olnow=0;
int vekGetCurl::ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
    dThis = (vekGetCurl*)clientp;
    if ( dltotal > -0.1 && dltotal < 0.1 )
    {
        return 0;
    }
    //int nPos = (int) ( (dlnow/dltotal)*100 );
    //QThread::msleep(5);
    if(olnow!=dlnow){
        string logText="文件名:"+dThis->fileName.toStdString()+"   总大小/当前下载进度:"+std::to_string((long)dltotal)+"/"+std::to_string((long)dlnow);
        dThis->outLogText(logText);
        olnow=dlnow;
    }
    return 0;
}
void vekGetCurl::outLogText(string text){
    outputPrgressText=QString::fromStdString(text);
    emit curlPrgressSignals();
}

bool vekGetCurl::DownloadFile(std::string URLADDR,std::string path)
{        
    CURL *curl;
    CURLcode curl_res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl){
        FILE* file= fopen(path.c_str(), "ab+");
        curl_easy_setopt(curl, CURLOPT_URL, URLADDR.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,file);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA,this);
        curl_res = curl_easy_perform(curl);
        /* Check for errors */
        if(curl_res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(curl_res));
        }
        if(CURLE_OK == curl_res)
        {
            char *url;
            curl_res = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

            if((CURLE_OK == curl_res) && url)
                printf("重定向后的url: %s\n", url);
        }
        /* always cleanup */
        fclose(file);
        curl_easy_cleanup(curl);
        /* we're done with libcurl, so clean it up */
        curl_global_cleanup();
    }
    return !curl_res;
}
void vekGetCurl::DoewloadPlugs(BaseWineData _wd){
    if(!QDir(_wd.IwinePath+"/plugs").exists()){
        QDir().mkdir(_wd.IwinePath+"/plugs");
    }
    if(_wd.IwineMono!=NULL){
        olnow=0;
        fileName="Mono组件";
        DownloadFile(_wd.IwineMono.toStdString(),(_wd.IwinePath+"/plugs/Mono.msi").toStdString());
    }
    if(_wd.IwineGeckoX86!=NULL){
        olnow=0;
        fileName="GeckoX86组件";
        DownloadFile(_wd.IwineGeckoX86.toStdString(),(_wd.IwinePath+"/plugs/GeckoX86.msi").toStdString());
    }
    if(_wd.IwineGeckoX86_64!=NULL){
        olnow=0;
        fileName="GeckoX86_64组件";
        DownloadFile(_wd.IwineGeckoX86_64.toStdString(),(_wd.IwinePath+"/plugs/GeckoX86_64.msi").toStdString());
    }
    outLogText("组件下载完毕!");
}
