#include "datacurl.h"


datacurl *datacurl::dcurl = nullptr;

datacurl::datacurl(QString fUrl,QString fPath)
{
    fileUrl=fUrl;
    filePath=fPath;
    dcurl=this;
    connect(this,SIGNAL(SigDeliverMessStatic(long,long,int)),this,SLOT(SlotDeliverMessStatic(long,long,int)));
}
datacurl::~datacurl()
{
   curl=nullptr;
}
static size_t getData(void *buffer, size_t sz, size_t nmemb, void *writer)
{
    std::string* psResponse =static_cast<std::string *>(writer);
    size_t size = sz * nmemb;
    psResponse->append(static_cast<char*>(buffer), size);
    return sz * nmemb;
}
std::string datacurl::vekGetData(QString url){
    CURL *curl=curl_easy_init();
    CURLcode res =CURLE_QUOTE_ERROR;
    std::string strRsp;
    while(res==CURLE_QUOTE_ERROR){
        std::string strTmpStr;
        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_HEADER, false);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strTmpStr);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK||QString::fromStdString(strTmpStr).contains("404",Qt::CaseSensitive)||res==CURLE_QUOTE_ERROR)
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
size_t datacurl::DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam)
{
    FILE* fp = (FILE*)pParam;
    size_t nWrite = fwrite(pBuffer, nSize, nMemByte, fp);

    return nWrite;
}

int datacurl::ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
    datacurl* dd = (datacurl*)clientp;

    if ( dltotal > -0.1 && dltotal < 0.1 )
    {
        return 0;
    }
    int nPos = (int) ( (dlnow/dltotal)*100 );
    emit dcurl->SigDeliverMessStatic(dlnow,dltotal,nPos);
    return 0;
}
void datacurl::SlotDeliverMessStatic(long dlnow,long dltotal,int xPos){
    emit toPrgStr(dlnow,dltotal,xPos);
}
bool datacurl::DownloadFile(std::string URLADDR)
{ 
    curl_global_init(CURL_GLOBAL_ALL);
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, URLADDR.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        //curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,file);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA,this);
        curl_res = curl_easy_perform(curl);
        /* Check for errors */
        if(curl_res == CURLE_OK){
            if(CURLE_OK == curl_res)
            {
                char *url;
                curl_res = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
                if((CURLE_OK == curl_res) && url)
                    printf("重定向后的url: %s\n", url);
            }
        }else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(curl_res));
        }
        fclose(file);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    if(curl_res != CURLE_OK){
        return false;
    }
    return !curl_res;
}
void datacurl::vUp(){
    QFile uFile(filePath);
    if(uFile.exists()){
        uFile.remove();
    }
    file= fopen(filePath.toStdString().c_str(), "ab+");
    curl = curl_easy_init();
    bool dState=DownloadFile(fileUrl.toStdString());
    emit doneDown(true,dState);
}
