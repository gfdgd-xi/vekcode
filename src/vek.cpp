#include "vek.h"
#include "ui_common.h"
#include <QCryptographicHash>
vek::vek(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vek)

{
    ui->setupUi(this);
}
vek::~vek()
{
    if(objTray){
       objTray->ExitTray();
    }
    delete ui;
}
void vek::connectObject(){
    connect(ui->pushButton_vekAddApp,&QPushButton::clicked,this,&vek::vekAddApp);
    connect(ui->pushButton_InstallApp,&QPushButton::clicked,this,&vek::installApp);
    connect(ui->pushButton_initDocker,&QPushButton::clicked,this,&vek::addInitDocker);
    connect(ui->pushButton_ServerTest,&QPushButton::clicked,this,&vek::wServerTest);
    connect(ui->pushButton_SetHosts,&QPushButton::clicked,this,&vek::wSetHosts);
    connect(ui->action_clear_ico,&QAction::triggered,this,&vek::on_action_Clear_Ico);
    connect(ui->action_inst_app,&QAction::triggered,this,&vek::installApp);
    connect(ui->action_add_docker,&QAction::triggered,this,&vek::addInitDocker);

    //默认样式
    connect(ui->styleDefault,&QAction::triggered,this,&vek::vekStyle);
    connect(ui->styleDark,&QAction::triggered,this,&vek::vekStyle);
    connect(ui->styleLight,&QAction::triggered,this,&vek::vekStyle);
    //
    connect(ui->action_SHA256,&QAction::triggered,this,&vek::hFileHash);
    //
    connect(ui->action_West,&QAction::triggered,this,&vek::changeQTabWidgetStyleNorth);
    connect(ui->action_North,&QAction::triggered,this,&vek::changeQTabWidgetStyleWest);
    //
    connect(ui->action_repair_stalonetray,&QAction::triggered,this,&vek::repair_Stalonetray);
    connect(ui->action_repair_wineprc,&QAction::triggered,this,&vek::repair_Wineprc);
    connect(ui->action_repair_winetricks,&QAction::triggered,this,&vek::repair_Winetricks);
    //
    connect(ui->comboBox_wServer,&QComboBox::currentTextChanged,this,&vek::wCurrentUrl);
    //
    //connect(ui->action_Inst_UEngine,&QAction::triggered,this,&vek::uenginInst);
    //connect(ui->action_Run_UEngine,&QAction::triggered,this,&vek::uengineRun);
    //connect(ui->action_InstApp_UEngine,&QAction::triggered,this,&vek::uengineInstApp);
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
void vek::uenginInst(){
    bool b_state=pObject::vekMesg("提示:安装UEngine需要管理员权限");
    bool bn_ok=false;
    QString mPassword;
    if(b_state){
        QString dnTitle="输入授权密码";
        QString dnLabel="输入错误后果自负";
        QLineEdit::EchoMode echoMode=QLineEdit::Normal;
        mPassword = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,mPassword, &bn_ok);
    }
    if(b_state&bn_ok){
        qInfo()<<mPassword;
        system(("echo "+mPassword+" | sudo -S apt install -f -y uengine").toLocal8Bit());
    }
}
void vek::uengineRun(){
    system("uengine launch --package=org.anbox.appmgr --component=org.anbox.appmgr.AppViewActivity");
}
void vek::uengineInstApp(){

}
void vek::on_action_Clear_Ico(){
    QDesktopServices::openUrl(QUrl(QDir::homePath()+"/.local/share/applications", QUrl::TolerantMode));
    QDesktopServices::openUrl(QUrl(QDir::homePath()+"/.local/share/desktop-directories", QUrl::TolerantMode));
}
void vek::repair_Winetricks(){
    objectVersionData OBJ_VER;
    OBJ_VER.repair_Wineprc_Stalonetray_Winetricks();
    pObject::vekTip("修复完毕!");
}
void vek::repair_Wineprc(){
    objectVersionData OBJ_VER;
    OBJ_VER.repair_Wineprc_Stalonetray_Winetricks();
    pObject::vekTip("修复完毕!");
}
void vek::repair_Stalonetray(){
    objectVersionData OBJ_VER;
    OBJ_VER.repair_Wineprc_Stalonetray_Winetricks();
    pObject::vekTip("修复完毕!");
}
void vek::setProcRow(int n){
    ui->label_Run_Proc->setText(QString::number(n));
}
void vek::changeQTabWidgetStyleWest(){
    ui->tabWidget->changeQTwidgetStyle(QTabWidget::West);
}
void vek::changeQTabWidgetStyleNorth(){
    ui->tabWidget->changeQTwidgetStyle(QTabWidget::North);
}
void vek::hFileHash()
{
    QString curPath=QApplication::applicationDirPath();//获取系统当前目录
    //获取应用程序的路径
    QString dlgTitle="选择一个文件";
    QString filter="所有文件(*.*)";
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (!aFileName.isEmpty())
    {
        QFile file(aFileName);
        QCryptographicHash Hash(QCryptographicHash::Sha256);
        if(file.open(QIODevice::ReadOnly)){
            while(file.atEnd() == false){
                QByteArray message = file.readAll();
                Hash.addData(message);
            }
            pObject::vekTip("文件名:"+file.fileName()+"\n"+"SHA256:"+Hash.result().toHex()+"\n");
        }
    }
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

void vek::installApp(){
    ui->tabWidget->objInitDocker(INSTALLAPP);
}
void vek::addInitDocker(){
    ui->tabWidget->objInitDocker(INITDOCKER);
}
void vek::on_action_EditSource_triggered(){
    vekSourceEdit& srcOption=vekSourceEdit::GetInstance();
    srcOption.setGeometry(this->geometry());
    srcOption.setWindowFlags(Qt::WindowStaysOnTopHint);
    srcOption.show();
}
void vek::vekAddApp()
{   
    ui->tabWidget->addAppSlot();
}
void vek::on_action_AddApp_triggered()
{
    ui->tabWidget->addAppSlot();
}

void vek::on_action_About_triggered()
{
    vekAbout& _vekAbout=vekAbout::GetInstance();
    _vekAbout.show();
    _vekAbout.GetVerInfo();

}
void vek::on_action_Exit_triggered()
{
    this->close();
}

void vek::on_action_WineInstall_triggered()
{
    vekWineOption& _vekWineOption=vekWineOption::GetInstance();
    _vekWineOption.setGeometry(this->geometry());
    _vekWineOption.setWindowFlags(Qt::WindowStaysOnTopHint);
    _vekWineOption.getWineGitInfo();
    _vekWineOption.loadWineData();
    _vekWineOption.show();
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
