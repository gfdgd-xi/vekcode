#ifndef OBJVGIT_H
#define OBJVGIT_H

#include "git2.h"
#include "git2/clone.h"
#include "git2/cred_helpers.h"
#include "common.h"
//进度数据
typedef struct progress_data {
    git_indexer_progress fetch_progress;
    size_t completed_steps;
    size_t total_steps;
    const char *path;
} progress_data;


class objvgit:public QObject
{
    Q_OBJECT
public:
       objvgit();
       ~objvgit();
  void vek_Clone(std::string url,std::string path);
};

#endif // VEKDGITTHREAD_H
