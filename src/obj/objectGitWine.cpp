#include "objectGitWine.h"

//objectGitWine *pThis;
objectGitWine *g_calcThread = new objectGitWine;
objectGitWine::objectGitWine(QObject *parent) : QThread(parent)
{
    //delete pThis;
}
objectGitWine::~objectGitWine(){
}
//输出进度信息
void objectGitWine::output_progress(progress_data *pd)
{
    int network_percent = pd->fetch_progress.total_objects > 0 ?
        (100*pd->fetch_progress.received_objects) / pd->fetch_progress.total_objects :
        0;
    int index_percent = pd->fetch_progress.total_objects > 0 ?
        (100*pd->fetch_progress.indexed_objects) / pd->fetch_progress.total_objects :
        0;

    int checkout_percent = pd->total_steps > 0
        ? (int)((100 * pd->completed_steps) / pd->total_steps)
        : 0;
    size_t kbytes = pd->fetch_progress.received_bytes / 1024;

        string prlog="Net:   "+std::to_string(network_percent)+"%   "+
        "("+std::to_string(kbytes)+"   kb,"+std::to_string(pd->fetch_progress.received_objects)+"/"+std::to_string(pd->fetch_progress.total_objects)+")"+
        "   idx:   "+std::to_string(index_percent)+"%"+"("+std::to_string(pd->fetch_progress.indexed_objects)+"/"+std::to_string(pd->fetch_progress.total_objects)+")"+
        "   chk:   "+std::to_string(checkout_percent)+"%"+"("+std::to_string(pd->completed_steps)+"/"+std::to_string(pd->total_steps)+")"+
        "   Resolving deltas:   "+"("+std::to_string(pd->fetch_progress.indexed_deltas)+"/"+std::to_string(pd->fetch_progress.total_deltas)+")";
        outputPrgressSlots(prlog);
        //qDebug()<<QString::fromStdString(prlog);
}
//网络进度
int objectGitWine::sideband_progress(const char *str, int len, void *payload)
{
    (void)payload; /* unused */
    string prlog="remote:"+std::to_string(len)+str;
    g_calcThread->outputPrgressSlots(prlog);
    fflush(stdout);
    return 0;
}
//拉取进度
int objectGitWine::fetch_progress(const git_indexer_progress *stats, void *payload)
{
    progress_data* pd = (progress_data*)payload;
    pd->fetch_progress = *stats;
    g_calcThread->output_progress(pd);
    return 0;
}
//检查输出进度
void objectGitWine::checkout_progress(const char *path, size_t cur, size_t tot, void *payload)
{
    progress_data* pd = (progress_data*)payload;
    pd->completed_steps = cur;
    pd->total_steps = tot;
    pd->path = path;
    g_calcThread->output_progress(pd);
}
//sslcert
int objectGitWine::ssl_cert(git_cert *cert, int valid, const char *host, void *payload)
{
   GIT_UNUSED(valid);
   GIT_UNUSED(cert);
   GIT_UNUSED(host);
   GIT_UNUSED(payload);
    return 1;
}
void objectGitWine::outputPrgressSlots(string text){
    QtConcurrent::run([=]()
    {
        outputPrgressText=QString::fromStdString(text);
        emit outputPrgressSignals();
    });

}
void objectGitWine::curlPrgressSlots(){
    QtConcurrent::run([=]()
    {
        outputPrgressText=_vekgetcurl.outputPrgressText;
        emit outputPrgressSignals();
    });

}
void objectGitWine::vek_Clone(BaseWineData _wd){
    outputPrgressSlots("Init Repo");
    if(!git_libgit2_init())
        return;
    progress_data pd;
    //初始化git_repository
    git_repository *cloned_repo=nullptr;
    git_clone_options clone_opts =  GIT_CLONE_OPTIONS_INIT;
    git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
    checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
    checkout_opts.progress_cb = checkout_progress;
    checkout_opts.progress_payload = &pd;
    clone_opts.checkout_opts = checkout_opts;
    clone_opts.fetch_opts.callbacks.sideband_progress = sideband_progress;
    clone_opts.fetch_opts.callbacks.transfer_progress = &fetch_progress;
    clone_opts.fetch_opts.callbacks.certificate_check = ssl_cert;
    clone_opts.fetch_opts.callbacks.payload = &pd;
    /* Do the clone */
    QByteArray b2,b3;
    b2.append(_wd.IwinePath);
    const char *path = b2.data();
    b3.append(_wd.IwineUrl);
    const char *url = b3.data();
    outputPrgressSlots("clone:"+_wd.IwineName.toStdString());
    git_clone(&cloned_repo, url, path, &clone_opts);
    git_repository_free(cloned_repo);
    git_libgit2_shutdown();
    outputPrgressSlots("Done clone!");
}

void objectGitWine::run()
{
    try{
        //pThis=this;
        if(_wd.IwinePath==nullptr){
            return;
        }
        QDir dir(_wd.IwinePath);
        if(dir.exists()){
            dir.removeRecursively();
        }
        vek_Clone(_wd);
        dir.mkdir(_wd.IwinePath+"/plugs");
        outputPrgressSlots("开始下载组件请稍等!");
        connect(&_vekgetcurl,&objectGetCurl::curlPrgressSignals,this,&objectGitWine::curlPrgressSlots);
        _vekgetcurl.DoewloadPlugs(_wd.IwineMono,_wd.IwinePath+"/plugs/Mono.msi");
        _vekgetcurl.DoewloadPlugs(_wd.IwineGeckoX86,_wd.IwinePath+"/plugs/GeckoX86.msi");
        _vekgetcurl.DoewloadPlugs(_wd.IwineGeckoX86_64,_wd.IwinePath+"/plugs/GeckoX86_64.msi");
        outputPrgressSlots("组件下载完毕!");
        objectJson* _objectJson=new objectJson() ;
        _objectJson->updateWineNodeData(_wd);
        delete _objectJson;
        _objectJson=nullptr;
        emit overThreadSignals(true);
    }catch(...){
        emit overThreadSignals(false);
    }

}
