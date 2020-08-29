#ifndef VEKVIEWAT_H
#define VEKVIEWAT_H

#include "../../obj/common.h"
#include <QListWidget>
#include <QComboBox>
class vekViewAT: public QComboBox
{
    Q_OBJECT
public:
   explicit vekViewAT(QWidget *parent = 0);
   ~vekViewAT();
private:
    void initQComboBox();
    QTabWidget *qTab=nullptr;

    bool LoadAppListData();
    QString GetCurrentIndex();

};

#endif // VEKATJSONVIEW_H
