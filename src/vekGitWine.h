#ifndef VEKGITWINE_H
#define VEKGITWINE_H

#include "objectJson.h"
#include "git2.h"
#include "git2/clone.h"
#include "git2/cred_helpers.h"
#include "common.h"
#include "vekGetCurl.h"
//进度数据
typedef struct progress_data {
    git_indexer_progress fetch_progress;
    size_t completed_steps;
    size_t total_steps;
    const char *path;
} progress_data;


class vekGitWine : public QThread
{
    Q_OBJECT
public:
       explicit vekGitWine(QObject *parent = nullptr);
       ~vekGitWine();
       BaseWineData _wd;
       QString outputPrgressText;
protected:
       void run();
signals:
       void outputPrgressSignals();
       void overThreadSignals();
public slots:
       void outputPrgressSlots(string text);
       void curlPrgressSlots();
private:
       vekGetCurl _vekgetcurl;
       void vek_Clone(BaseWineData _wd);
};

#endif // VEKDGITTHREAD_H
