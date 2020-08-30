#include "vekPanelAT.h"
#include <QGridLayout>
vekPanelAT::vekPanelAT(QWidget *parent) : QComboBox(parent)
{

}
vekPanelAT::~vekPanelAT(){

}
bool vekPanelAT::LoadAppListData(){
    return 0;
}
void vekPanelAT::showPopup()
{
    this->addItem("");
    emit sigPopup();
    QComboBox::showPopup();
    this->clear();
    qTab=new QTabWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(qTab);
    layout->setContentsMargins(0,0,0,0);
    QWidget *popup = this->findChild<QFrame*>();
    delete popup->layout();
    popup->setMinimumWidth(600);
    popup->setMinimumHeight(500);
    popup->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    popup->setLayout(layout);
    popup->show();
    std::map<QString,std::map<QString,BaseAppJson>>::reverse_iterator it;
    std::map<QString,BaseAppJson>::iterator its;
    for(auto a:g_vekLocalData.appJsonList){
        for(it = a.second.rbegin(); it != a.second.rend(); it++){
            vekViewAT *pListView=new vekViewAT();
            pListView->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
            pListView->setViewMode(QListView::IconMode);
            pListView->setFlow(QListView::LeftToRight);
            pListView->setResizeMode(QListView::Adjust);
            for(its=it->second.begin();its!=it->second.end();its++){
                BaseAppJson* baj=new BaseAppJson;
                *baj=its->second;
                pListView->addItem(baj);
            }
            qTab->addTab(pListView,it->first);
        }
        break;
    }
    popup->move(popup->x(), popup->y() + 1);
}
