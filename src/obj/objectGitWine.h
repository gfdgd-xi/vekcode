#ifndef OBJECTGITWINE_H
#define OBJECTGITWINE_H

#include "objectJson.h"
#include "git2.h"
#include "common.h"
#include "objectGetCurl.h"
#include <QTextEdit>
#include <QMetaObject>
typedef struct progress_data {
    git_indexer_progress fetch_progress;
    size_t completed_steps;
    size_t total_steps;
    const char *path;
} progress_data;

class objectGitWine : public QObject
{
    Q_OBJECT
public:
    objectGitWine(BaseWineData);
    ~objectGitWine();
private slots:
    void gitWine();
private:
    BaseWineData wData;
    QTextEdit* qTextEdit;
    static objectGitWine *objGitWine;
    void downWine();
    static void output_progress(progress_data* pd);
    static void checkout_progress(const char *path, size_t cur, size_t tot, void *payload);
    static int sideband_progress(const char *str, int len, void *payload);
    static int fetch_progress(const git_indexer_progress *stats, void *payload);
    static int ssl_cert(git_cert *cert, int valid, const char *host, void *payload);
signals:
    void toPrgStr(QString);
    void SigDeliverMessStatic(string);
    void overThreadSignals(bool);
private slots:
    void SlotDeliverMessStatic(string);
};

#endif // VEKDGITTHREAD_H
