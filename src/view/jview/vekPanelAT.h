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
     BaseAppJson oData;
private:
    QTabWidget *qTab=nullptr;
    bool LoadAppListData();
    void GetCurrentIndex();
    std::map<QString,vekViewAT*> *m_pListMap;
protected:
    void showPopup();
public slots:
    void qComboBoxJsonSet(BaseAppJson data);
signals:
    void sigPopup();
};

#endif // VEKPANELAT_H
