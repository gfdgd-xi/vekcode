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
    std::map<QString,std::map<QString,SappDeployInfo>>::reverse_iterator it;
    std::map<QString,SappDeployInfo>::iterator its;
    QString srcText=this->parent()->parent()->findChild<QComboBox*>("comboBox_SrcApp")->currentText();
    for(auto a:g_vekLocalData.map_app_json_list){
        if(a.first==srcText){
            for(it = a.second.rbegin(); it != a.second.rend(); it++){
                vekViewAT *pListView=new vekViewAT();
                pListView->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
                pListView->setViewMode(QListView::IconMode);
                pListView->setFlow(QListView::LeftToRight);
                pListView->setResizeMode(QListView::Adjust);
                for(its=it->second.begin();its!=it->second.end();its++){
                    SappDeployInfo* baj=new SappDeployInfo;
                    *baj=its->second;
                    pListView->addItem(baj);
                }
                qTab->addTab(pListView,it->first);
                connect(pListView,SIGNAL(outAppData(SappDeployInfo*)),this,SLOT(qComboBoxJsonSet(SappDeployInfo*)));
            }
            break;
        }
    }
    popup->move(popup->x(), popup->y() + 1);
}
void vekPanelAT::qComboBoxJsonSet(SappDeployInfo* data){
    if(data!=nullptr){
        this->clear();
        this->addItem(data->s_deploy_app_name);
        oData=*data;
        this->hidePopup();
    }
}
