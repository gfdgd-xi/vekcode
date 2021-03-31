#ifndef VEKVIEWAT_H
#define VEKVIEWAT_H

#include "vekModelAT.h"
#include "../../obj/common.h"

class vekViewAT:public QListView
{
    Q_OBJECT
public:
    vekViewAT(QWidget *parent = NULL);
   ~vekViewAT();
    void addItem(BaseAppJson *pItem );
protected:
        void mouseDoubleClickEvent(QMouseEvent* event);
private:
    int  m_hitIndex;
    vekModelAT* m_pModel;
signals:
    void outAppData(BaseAppJson);
};

#endif // VEKATJSONVIEW_H
