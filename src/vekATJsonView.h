#ifndef VEKATJSONVIEW_H
#define VEKATJSONVIEW_H

#include "common.h"
#include <QListWidget>
#include <QComboBox>
class vekATJsonView: public QComboBox
{
    Q_OBJECT
public:
   explicit vekATJsonView(QWidget *parent = 0);
   ~vekATJsonView();
private:
    void initQComboBox();
    QTabWidget *qTab=nullptr;
};

#endif // VEKATJSONVIEW_H
