#include "vekGitWine.h"

vekGitWine *pThis=nullptr;

vekGitWine::vekGitWine(QObject *parent) : QThread(parent)
{
}
vekGitWine::~vekGitWine(){
}
//输出进度信息
void vekGitWine::output_progress(progress_data *pd)
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
int vekGitWine::sideband_progress(const char *str, int len, void *payload)
{
    (void)payload; /* unused */
    string prlog="remote:"+std::to_string(len)+str;
    pThis->outputPrgressSlots(prlog);
    fflush(stdout);
    return 0;
}
//拉取进度
int vekGitWine::fetch_progress(const git_indexer_progress *stats, void *payload)
{
    progress_data *pd = (progress_data*)payload;
    pd->fetch_progress = *stats;
    pThis->output_progress(pd);
    return 0;
}
//检查输出进度
void vekGitWine::checkout_progress(const char *path, size_t cur, size_t tot, void *payload)
{
    progress_data *pd = (progress_data*)payload;
    pd->completed_steps = cur;
    pd->total_steps = tot;
    pd->path = path;
    pThis->output_progress(pd);
}
//sslcert
int vekGitWine::ssl_cert(git_cert *cert, int valid, const char *host, void *payload)
{
   GIT_UNUSED(valid);
   GIT_UNUSED(cert);
   GIT_UNUSED(host);
   GIT_UNUSED(payload);
    return 1;
}
void vekGitWine::outputPrgressSlots(string text){
    outputPrgressText=QString::fromStdString(text);
    emit outputPrgressSignals();
}
void vekGitWine::curlPrgressSlots(){
    outputPrgressText=_vekgetcurl.outputPrgressText;
    emit outputPrgressSignals();
}
void vekGitWine::vek_Clone(BaseWineData _wd){
    pThis=this;
    pThis->outputPrgressSlots("Init Repo");
    if(!git_libgit2_init())
        return;
    progress_data pd = {{0}};
    //初始化git_repository
    git_repository *cloned_repo;
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
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
    pThis->outputPrgressSlots("clone:"+_wd.IwineName.toStdString());
    git_clone(&cloned_repo, url, path, &clone_opts);
    git_repository_free(cloned_repo);
    git_libgit2_shutdown();
    objectJson* _objectJson=new objectJson() ;
    _objectJson->updateWineNodeData(_wd);
    pThis->outputPrgressSlots("Done clone!");
    delete _objectJson;
    _objectJson=nullptr;
}
int i=0;
void vekGitWine::run()
{
   if(_wd.IwinePath==NULL){
       return;
   }
   QDir dir(_wd.IwinePath);
   if(dir.removeRecursively()){
       vek_Clone(_wd);
   }
   i+=1;
   qDebug()<<i;
   outputPrgressSlots("开始下载组件请稍等!");
   connect(&_vekgetcurl,&vekGetCurl::curlPrgressSignals,this,&vekGitWine::curlPrgressSlots);
   _vekgetcurl.DoewloadPlugs(_wd);
   emit overThreadSignals();
}
