#ifndef VEKWINEOPTION_H
#define VEKWINEOPTION_H

#include "obj/objectGitWine.h"
#include "obj/common.h"
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QTableView>
#include <QtConcurrent/QtConcurrentRun>
namespace Ui {
class vekWineOption;
}

class vekWineOption : public QWidget
{
    Q_OBJECT

public:
    static vekWineOption& GetInstance(){
        static vekWineOption instance;
        return instance;
    }

    void getWineGitInfo();
    void loadWineData();
private slots:
    void appendTextToLog(QString);
    void overGitThreadSignals(bool);
    void on_toolButton();
    void installWine(QString);
    void deleteWine(QString);
    void clicked_rightMenu(const QPoint &/*pos*/);
    void onTaskBoxContextMenuEvent();
private:
    vekWineOption();
    ~vekWineOption();
    vekWineOption(const vekWineOption& instance);
    const vekWineOption& operator =(const vekWineOption& instance);
    Ui::vekWineOption *ui;
    QStandardItemModel *ItemModelWine;
    //Wine线程
    QThread *obj_Thread;
    objectGitWine *objWine_Thread;
    void controlState(bool pState);
    void loadWineList(QTableView*);
private slots:
    void wineVersionComoboBox();
signals:
    void ToThread();
};

#endif // VEKOPTION_H
