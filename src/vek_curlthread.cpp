#include "vek_curlthread.h"
#include <stdlib.h>
vek_CurlThread::vek_CurlThread()
{

}
// 数据返回时的回调函数
size_t onDataReceive(void *buffer, size_t size, size_t nmemb, void *user_p)
{
    FILE *fp = (FILE*)user_p;
    size_t receivedDataLen;
    receivedDataLen = fwrite(buffer, size, nmemb, fp);
    return receivedDataLen;
}

// 显示下载进度
int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow,int dtotal)
{
    if (0 != dltotal) {
        dtotal=100 * dlnow / dltotal;
        std::cout<<"download progress: " << dtotal << "%" << std::endl;
        //textEdit.append(QString::fromStdString(std::to_string(100 * dlnow / dltotal)));
    }
    return 0;
}
int vek_CurlThread::downloadFile(){
        std::string url = "https://coding-net-production-file-1257242599.cos.ap-shanghai.myqcloud.com/c7494ae0-8872-11ea-af73-e30f59805045.7z?sign=q-sign-algorithm%3Dsha1%26q-ak%3DAKIDay83lFmaS6Y4LTdzMVO1SdZOyJSNOYpr%26q-sign-time%3D1588000011%3B1588003611%26q-key-time%3D1588000011%3B1588003611%26q-header-list%3D%26q-url-param-list%3Dresponse-content-disposition%3Bresponse-expires%26q-signature%3Da765d7e7f8038e9ae99c6cc1abcc190699cef0b0&response-content-disposition=attachment%3Bfilename%3Dwine.7z&response-expires=Thu%2C%2030%20Apr%202020%2003%3A06%3A51%20GMT";
        char *filename = "/home/jacklee/wine.7z";
        CURLcode code;
        // 设置运行环境
       code = curl_global_init(CURL_GLOBAL_ALL);
       if (CURLE_OK != code) {
          std::cerr << "init libcurl failed." << std::endl;
           return -1;
        }
        CURL *easy_handle = curl_easy_init();
        void *clientp = NULL;
        FILE *file_param;
        file_param = fopen(filename, "wb");
        // 开启进度设置
        curl_easy_setopt(easy_handle, CURLOPT_NOPROGRESS, 0);
        // 设置进度回调函数
        curl_easy_setopt(easy_handle, CURLOPT_XFERINFOFUNCTION, &progress_callback);
        // 设置传给进度回调函数的指针
        curl_easy_setopt(easy_handle, CURLOPT_XFERINFODATA, clientp);
        // 设置下载地址
        curl_easy_setopt(easy_handle, CURLOPT_URL, url.c_str());
        // 设置接受数据的回调函数
        curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &onDataReceive);
        // 设置传给回调函数的参数，这里是个文件指针
        curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, file_param);
        // 连接远端站点，执行必要的命令并处理返回结果
        curl_easy_perform(easy_handle);
        curl_easy_cleanup(easy_handle);
        fclose(file_param);
        curl_global_cleanup();
       return 0;
}
