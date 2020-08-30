#include "vekViewAT.h"

vekViewAT::vekViewAT(QWidget *parent):QListView(parent)
{  
    parent=nullptr;
    m_hitIndex=-1;
    m_pModel=new vekModelAT;
    this->setModel(m_pModel);
}
vekViewAT::~vekViewAT(){

}

void vekViewAT::addItem(BaseAppJson *pItem )
{
    m_pModel->addItem(pItem);
}
