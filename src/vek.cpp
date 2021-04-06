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
    connect(ui->pushButton_ServerTest,&QPushButton::clicked,this,&vek::wServerTest);
    connect(ui->pushButton_SetHosts,&QPushButton::clicked,this,&vek::wSetHosts);
    connect(ui->comboBox_wServer,&QComboBox::currentTextChanged,this,&vek::wCurrentUrl);
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
    loadWinetricksServerJson();
    setAppSize();
    vekStyle();
}
void vek::loadWinetricksServerJson(){
    if(!getWinetricksServerJson()){
        pObject::vekTip("获取winetricks上游服务器列表失败,winetricks将以默认服务器为你提供下载服务!");
        ui->pushButton_ServerTest->setEnabled(false);
        ui->pushButton_SetHosts->setEnabled(false);
        ui->comboBox_wServer->setEnabled(false);
    }else{
        wCurrentUrl();
    }

}
bool vek::getWinetricksServerJson(){
    objectGetCurl* _vekgetcurl=new objectGetCurl;
    string verInfoStr=_vekgetcurl->vekGetData(vek_winetricks_server.toStdString());
    try {
        if(verInfoStr!="error"){

            json jx=json::parse(verInfoStr);
            for(auto [x,y]:jx.items()){
                winetricks_server_url_list.insert(pair<QString, QString> (QString::fromStdString(x), QString::fromStdString(y)));
            }
            QStringList sList;
            for(const auto &name:winetricks_server_url_list){
                qInfo()<<name.first;
                sList<<name.first;
            }
            ui->comboBox_wServer->addItems(sList);
        }else{
            return false;
        }
    }  catch (...) {
        return false;
    }
    return true;
}
void vek::wCurrentUrl(){
    sWinetrickUrl=winetricks_server_url_list[ui->comboBox_wServer->currentText()];
    qInfo()<<sWinetrickUrl;
}
void vek::wServerTest(){
    QString wServerUrl=winetricks_server_url_list[ui->comboBox_wServer->currentText()];
    pObject::vekTip("如果浏览器能打开:\n"+wServerUrl+"\n则无需测速和修改hosts当然修改后可能更加适合您的网络环境");
    QStringList tUrl = wServerUrl.replace(QRegExp("http://|https://"),"").split("/");
    qInfo()<<tUrl[0];
    QDesktopServices::openUrl(QUrl("http://ping.pe/"+tUrl[0]));
}
void vek::wSetHosts(){
    QString dnPd="输入系统sudo密码";
    QString dnPdLabel="输入错误后果自负";
    QString setHostsPd="";
    QLineEdit::EchoMode echoPass=QLineEdit::Password;
    bool dn_ok=false;
    setHostsPd = QInputDialog::getText(nullptr, dnPd,dnPdLabel, echoPass,setHostsPd, &dn_ok);
    if(!dn_ok){
        return;
    }else{
        QString dnTitle="输入Hosts IP";
        QString dnLabel="输入错误后果自负";
        QString setHostsIp="";
        QLineEdit::EchoMode echoMode=QLineEdit::Normal;
        setHostsIp = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,setHostsIp, &dn_ok);
        if(!dn_ok){
            return;
        }else{
            QStringList tUrl = winetricks_server_url_list[ui->comboBox_wServer->currentText()].replace(QRegExp("http://|https://"),"").split("/");
            QString agrs="echo "+setHostsIp+" "+tUrl[0]+" >> /etc/hosts";
            QString dAgrs="echo "+setHostsPd+" | sudo -S sed -i "+"'/"+tUrl[0]+"/d'" +" /etc/hosts";
            //修改hosts权限
            system(("echo "+setHostsPd+" | sudo -S chmod a+w /etc/hosts").toLocal8Bit());
            //删除hosts含有当前url的行
            system(dAgrs.toLocal8Bit());
            //写入当前hosts
            system(agrs.toLocal8Bit());
            //重启网络hosts生效
            system(("echo "+setHostsPd+" | sudo -S /etc/init.d/networking restart").toLocal8Bit());
            //恢复hosts文件权限
            system(("echo "+setHostsPd+" | sudo -S chmod 644 /etc/hosts").toLocal8Bit());
        }
    }
}
void vek::option_Dev(){
    pObject::vekTip("开发中!");
    /*
    if(_vek_Package==nullptr){
        _vek_Package=new vekPackage();
        _vek_Package->setAttribute(Qt::WA_DeleteOnClose,true);
        _vek_Package->setWindowFlags(Qt::WindowStaysOnTopHint);
        _vek_Package->setGeometry(this->geometry());
        _vek_Package->show();
    }
    */
}

void vek::setAppSize(){
    int approw=0;
    //a 源
    //b 源下分类
    //c 分类下app
    for(auto a:g_vekLocalData.map_app_json_list){
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
    if(!g_vekLocalData.map_wine_list.empty()){
        for(auto a:g_vekLocalData.map_wine_list){
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
