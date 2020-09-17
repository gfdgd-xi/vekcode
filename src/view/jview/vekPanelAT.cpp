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
    if(qTab!=nullptr){
        delete qTab;
    }
    qTab=new QTabWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(qTab);
    layout->setContentsMargins(0,0,0,0);
    QWidget *popup = this->findChild<QFrame*>();
    delete popup->layout();
    popup->setMinimumWidth(668);
    popup->setMinimumHeight(500);
    popup->setLayout(layout);
    popup->show();
    std::map<QString,std::map<QString,BaseAppJson>>::reverse_iterator it;
    std::map<QString,BaseAppJson>::iterator its;
    QString srcText=this->parent()->parent()->findChild<QComboBox*>("comboBox_SrcApp")->currentText();
    for(auto a:g_vekLocalData.appJsonList){
        if(a.first==srcText){
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
                connect(pListView,SIGNAL(outAppData(BaseAppJson)),this,SLOT(qComboBoxJsonSet(BaseAppJson)));
            }
            break;
        }
    }
    popup->move(popup->x(), popup->y() + 1);
}
void vekPanelAT::qComboBoxJsonSet(BaseAppJson data){
    this->clear();
    this->addItem(data.appName);
    oData=data;
    this->hidePopup();
}
