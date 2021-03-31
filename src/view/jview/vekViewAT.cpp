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
void vekViewAT::mouseDoubleClickEvent(QMouseEvent *event){
    UNUSED(event);
    int rindex = this->currentIndex().row();
    if(rindex>-1){
        AppJson bAppJson=*m_pModel->getItem(rindex);
        emit outAppData(bAppJson);
    }
}
void vekViewAT::addItem(AppJson *pItem )
{
    m_pModel->addItem(pItem);
}
