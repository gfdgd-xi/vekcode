#ifndef VEKPANELAT_H
#define VEKPANELAT_H

#include "../../obj/common.h"
#include <QComboBox>
#include "vekViewAT.h"
#include <QListWidget>
class vekPanelAT: public QComboBox
{
    Q_OBJECT
public:
     vekPanelAT(QWidget *parent = 0);
    ~vekPanelAT();
private:
    QTabWidget *qTab=nullptr;
    bool LoadAppListData();
    QString GetCurrentIndex();
    std::map<QString,vekViewAT*> *m_pListMap;
protected:
    void showPopup();
signals:
    void sigPopup();
};

#endif // VEKPANELAT_H
