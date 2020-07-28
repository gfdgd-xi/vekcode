#include "vekATJsonView.h"
vekATJsonView::vekATJsonView(QWidget *parent) : QComboBox(parent)
{  
    initQComboBox();
}
vekATJsonView::~vekATJsonView(){
}
void vekATJsonView::initQComboBox(){
    qTab=new QTabWidget();
    QListWidget *item_list=new QListWidget();
    QListWidgetItem* item_wrap=new QListWidgetItem(item_list);
    item_list->setMinimumWidth(500);
    item_list->setMinimumHeight(400);
    this->setModel(item_list->model());
    this->setView(item_list);
    this->setCurrentIndex(-1);
    qTab->setMaximumWidth(500);
    qTab->setMinimumHeight(400);
    QString tabName[]={"网络游戏","单机游戏","聊天软件","工业软件","其他"};
    for(int i=0;i<=tabName->size();i++){
        QWidget *item_widget=new QWidget();
        qTab->addTab(item_widget,tabName[i]);
    }
    item_list->setItemWidget(item_wrap,qTab);
    this->showPopup();
}
