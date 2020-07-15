#ifndef VEKGAMEPANEL_H
#define VEKGAMEPANEL_H

#include "vekGameListView.h"
#include "vekGameAddMT.h"
#include "vekGameAddMulti.h"
#include "vekGameAddAT.h"
#include "common.h"
#include "objectSource.h"
class vekGamePanel : public QWidget
{
    Q_OBJECT
public:
    vekGamePanel(QWidget *parent = 0);
    ~vekGamePanel();

protected:
    void contextMenuEvent ( QContextMenuEvent * event );
public slots:
    void addGroupSlot(BaseGameData* data);
    void addGameSlot();
    void addGameObject(BaseGameData*);
    void objectRunGame();
private:
    vekGameAddMT* vek_game_add=nullptr;
    vekGameAddMulti* vek_game_multi_add=nullptr;
    vekGameAddAT* vek_game_add_auto=nullptr;
    void unMultGameAdd();
    void unDiyGameAdd();
    void unAutoDock();
    void addGameDiy();
    void addGameAuto();
    void startLoadData();
    void vek_InitTabWidgetListGame();
    QTabWidget  *m_pBox;
    std::map<QString,vekGameListView*> *m_pListMap;    //记录分组和分组名字的映射关系，好在转移图标时知道转移到那个分组
    void vekLoadJsonData();
    string GetReData(QString);
signals:
    void toObjDiyArgs_ptr(BaseGameData*);
    void toObjAutoArgs_ptr(BaseGameData*);
};
#endif // VEKGAMEPANEL_H
