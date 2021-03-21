﻿#ifndef OBJECTGITWINE_H
#define OBJECTGITWINE_H

#include "objectJson.h"
#include "git2.h"
#include "common.h"
#include "objectGetCurl.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QTextEdit>
//进度数据

typedef struct progress_data {
    git_indexer_progress fetch_progress;
    size_t completed_steps;
    size_t total_steps;
    const char *path;
} progress_data;

class objectGitWine : public QThread
{
    Q_OBJECT
public:
       explicit objectGitWine(QObject *parent = nullptr);
       ~objectGitWine();
       BaseWineData _wd;
       QString outputPrgressText;
protected:
       void run();
signals:
       void outputPrgressSignals();
       void overThreadSignals(bool);
public slots:
       void outputPrgressSlots(string text);
       void curlPrgressSlots();
private:
       objectGetCurl _vekgetcurl;
       void vek_Clone(BaseWineData _wd);
       static void output_progress(progress_data* pd);
       static void checkout_progress(const char *path, size_t cur, size_t tot, void *payload);
       static int sideband_progress(const char *str, int len, void *payload);
       static int fetch_progress(const git_indexer_progress *stats, void *payload);
       static int ssl_cert(git_cert *cert, int valid, const char *host, void *payload);
};

#endif // VEKDGITTHREAD_H
