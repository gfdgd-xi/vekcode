#include "vekViewAT.h"
vekViewAT::vekViewAT(QWidget *parent) : QComboBox(parent)
{  
    initQComboBox();
}
vekViewAT::~vekViewAT(){

}
void vekViewAT::initQComboBox(){
    qTab=new QTabWidget();
    QListWidget *item_list=new QListWidget(qTab);
    QListWidgetItem* item_wrap=new QListWidgetItem(item_list);
    item_list->setMinimumWidth(500);
    item_list->setMinimumHeight(400);
    this->setModel(item_list->model());
    this->setView(item_list);
    this->setCurrentIndex(-1);
    QVariant v(0);
    this->setItemData(2, v, Qt::UserRole - 1);
    qTab->setMaximumWidth(500);
    qTab->setMinimumHeight(400);
    for(auto a:g_vekLocalData.appJsonList){
        for(auto b:a.second){
            QWidget *item_widget=new QWidget();
            qTab->addTab(item_widget,b.first);
        }
        break;
    }
    item_list->setItemWidget(item_wrap,qTab);
}
bool vekViewAT::LoadAppListData(){
    for(auto [kData,vData]:g_vekLocalData.appJsonList){

    }
}
