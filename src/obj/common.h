#ifndef COMMON_H
#define COMMON_H
#define UNUSED(x) (void)(x)
#define GIT_UNUSED(x) ((void)(x))
#define FILE_PATH_LEN 128
#define toStr(name) (#name)
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif
#include <iostream>
using namespace std;
//#################QT head###############//
#include <QPushButton>
#include <QDialog>
#include <QThread>
#include <QProcess>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QAbstractListModel>
#include <QFile>
#include <QIcon>
#include <QDir>
#include <QListView>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QInputDialog>
#include <QTabWidget>
#include <QThread>
#include <QProgressBar>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QApplication>
//###################C++ head################//
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <iostream>
#include <fstream>
#include <zlib.h>
#include <string.h>
#include "baseData.h"

/*
//##################3rdparty head############//
#include <zlib.h>
#include "curl/curl.h"
#include "curl/easy.h"
#include "git2.h"
#include "git2/clone.h"
#include "git2/cred_helpers.h"
#include "json.hpp"

//##################vek head###############//
#include "vekJsonData.h"
#include "vekGetCurl.h"
#include "vekGitWine.h"
#include "vekWineOption.h"
#include "vekAbout.h"
#include "vekUseCas.h"
#include "vekDebug.h"
#include "vekGameData.h"
#include "vekDockOptinObject.h"
#include "vekStyle.h"
#include "vekGameListView.h"
#include "vekGameAdd.h"
*/
#endif // COMMON_H
