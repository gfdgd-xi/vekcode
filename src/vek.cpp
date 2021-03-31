#include "vek.h"
#include "ui_common.h"

vek::vek(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vek)

{
    ui->setupUi(this);
}
vek::~vek()
{
    exitTray(true);
    delete ui;
}
void vek::connectObject(){
    connect(ui->pushButton_vekAddApp,&QPushButton::clicked,this,&vek::vekAddApp);
    connect(ui->pushButton_vekRunApp,&QPushButton::clicked,this,&vek::vekRunApp);
    connect(ui->pushButton_InstallApp,&QPushButton::clicked,this,&vek::installApp);
    connect(ui->pushButton_initDocker,&QPushButton::clicked,this,&vek::addInitDocker);
    //默认样式
    connect(ui->styleDefault,&QAction::triggered,this,&vek::vekStyle);
    connect(ui->styleDark,&QAction::triggered,this,&vek::vekStyle);
    connect(ui->styleLight,&QAction::triggered,this,&vek::vekStyle);
    //开发功能测试
    connect(ui->action_Dev,&QAction::triggered,this,&vek::option_Dev);
    //语言切换
    //connect(ui->langChinese,&QAction::triggered,this,&vek::vekLanguage);
    //connect(ui->langEnglish,&QAction::triggered,this,&vek::vekLanguage);
    pObject::qwidgetGeometry(this);
    QString vStr="Vek-";
    vStr.append(APP_VERSION);
    this->setWindowTitle(vStr);
    setAppSize();
    vekStyle();
}
void vek::option_Dev(){
    if(_vek_Package==nullptr){
        _vek_Package=new vekPackage();
        _vek_Package->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_Package->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_Package->setGeometry(this->geometry());
        _vek_Package->show();
    }
}
void vek::setAppSize(){
    int approw=0;
    //a 源
    //b 源下分类
    //c 分类下app
    for(auto a:g_vekLocalData.appJsonList){
        for(auto b:a.second){
            for(auto c:b.second){
                approw+=1;
            }
        }
    }
    ui->label_appSizeText->setText(QString::number(approw));
}
void vek::setProcRow(){
    ui->label_procRow->setText(QString::number(taskList.size()));
}
void vek::startTray(){
    if(!g_vekLocalData.wineVec.empty()){
        for(auto a:g_vekLocalData.wineVec){
            if(objTray==nullptr){
                objTray=new objectTray();
                objTray->_baseWineData=a.second;
                objTray->start(); 
            }
            break;
        }
    }
    setProcRow();
}
void vek::exitTray(bool trayState){
    if(trayState){
        if(objTray!=nullptr){
           objTray->exitTray();
        }
    }else{
        if(taskList.empty()){
        objTray->exitTray();
        }else{return;}
    }
    if(objTray==nullptr){
        return;
    }
    setProcRow();
    delete objTray;
    objTray=nullptr;
}
void vek::installApp(){
    ui->tabWidget->objInitDocker(INSTALLAPP);
}
void vek::addInitDocker(){
    ui->tabWidget->objInitDocker(INITDOCKER);
}
void vek::on_action_EditSource_triggered(){
    if(_vek_source_esit==nullptr){
        _vek_source_esit=new vekSourceEdit();
        _vek_source_esit->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_source_esit->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_source_esit->setGeometry(this->geometry());
        _vek_source_esit->show();
        connect(_vek_source_esit,&vekSourceEdit::_unSourveEdit,this,&vek::unSourceEdit);
    }
}
void vek::vekAddApp()
{   
     ui->tabWidget->addAppSlot();
}
void vek::vekRunApp()
{
    ui->tabWidget->objectRunApp();
}
void vek::on_action_AddApp_triggered()
{
    ui->tabWidget->addAppSlot();
}

void vek::on_action_About_triggered()
{
    if(_vek_About==nullptr){
        _vek_About=new vekAbout();
        _vek_About->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_About->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_About->setGeometry(this->geometry());
        _vek_About->GetVerInfo();
        _vek_About->show();
        connect(_vek_About,&vekAbout::_unVekAbout,this,&vek::unVekAbout);
    }
}
void vek::on_action_Exit_triggered()
{
    this->close();
}

void vek::on_action_WineInstall_triggered()
{
    if(_vek_wine_option==nullptr){
        _vek_wine_option=new vekWineOption();
        _vek_wine_option->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_wine_option->setGeometry(this->geometry());
        _vek_wine_option->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_wine_option->show();
        _vek_wine_option->getWineGitInfo();
        _vek_wine_option->loadWineData();
        connect(_vek_wine_option,&vekWineOption::_unInitWineOption,this,&vek::unInitWineOption);
    }
}
void vek::unInitWineOption(){
    _vek_wine_option=nullptr;
}
void vek::unVekAbout(){
    _vek_About=nullptr;
};
void vek::unSourceEdit(){
    _vek_source_esit=nullptr;
}
//切换Language
void vek::vekLanguage(){
    QObject *object = QObject::sender();
    QString objName=g_vekLocalData.vekOptions.vekLang;
    QString strLang;
    if(object){
        QAction *action_obnject = qobject_cast<QAction *>(object);
        objName=action_obnject->objectName();
    }
    if(objName=="langChinese"){
        strLang="vek_zh_CN.qm";
    }
    if(objName=="langEnglish"){
        strLang="vek_us_EN.qm";
    }
    QString langFilePath=":/res/lang/"+strLang;
    if (QFile(langFilePath).exists())
    {
        QTranslator* m_translator = new QTranslator;
        m_translator->load(langFilePath);
        vekThis->installTranslator(m_translator);
    }
    g_vekLocalData.vekOptions.vekLang=objName;
    objectJson oj;
    oj.WriteLocalData();
}
//切换Style
void vek::vekStyle()
{
    QObject *object = QObject::sender();
    QString objName=g_vekLocalData.vekOptions.vekStyle;
    QString strStyle;
    if(object){
        QAction *action_obnject = qobject_cast<QAction *>(object);
        objName=action_obnject->objectName();
    }
    setWindowIcon(QIcon(":/res/img/vek.ico"));
    if(objName=="styleDefault"){
        strStyle="Default.qss";
    }
    if(objName=="styleDark"){
        strStyle="Dark.qss";
    }
    if(objName=="styleLight"){
        strStyle="Light.qss";
    }
    QFile file(":/res/css/"+strStyle);
    file.open(QFile::ReadOnly|QFile::Text);
    if (file.isOpen())
    {
        QString styleSheet = QString::fromUtf8(file.readAll());
        vekThis->setStyleSheet(styleSheet);
        file.close();
    }
    g_vekLocalData.vekOptions.vekStyle=objName;
    objectJson oj;
    oj.WriteLocalData();
}
