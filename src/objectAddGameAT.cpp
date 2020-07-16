#include "objectAddGameAT.h"

objectAddGameAT::objectAddGameAT(ObjectAddDataAT objAddDataAT)
{
   _objAddDataAT=objAddDataAT;
}

objectAddGameAT::~objectAddGameAT(){
    delete _baseAutoSetJson;
    _baseAutoSetJson=nullptr;
}
QString objectAddGameAT::jsonPathTypeToStr(QString jsonPathFile){  
    try {
        QString jsonDataStr=nullptr;
        if(jsonPathFile.contains("http",Qt::CaseSensitive)||jsonPathFile.contains("https",Qt::CaseSensitive)){
            vekGetCurl* _vekgetcurl=new vekGetCurl();
            jsonDataStr=QString::fromStdString(_vekgetcurl->vekGetData(jsonPathFile.toStdString()));
            delete _vekgetcurl;
            _vekgetcurl=nullptr;
        }else{
            QFile file(jsonPathFile);
            if(!file.exists())
            {
                return nullptr;
            }
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            jsonDataStr = file.readAll();
            file.close();
        }
        if(jsonDataStr=="error"||jsonDataStr==nullptr){
            return nullptr;
        }
        return jsonDataStr;
    } catch (nullopt_t) {
        return nullptr;
    }
}
bool objectAddGameAT::jsonUnserialize(QString jsonPathFile){
    QString jsonData=jsonPathTypeToStr(jsonPathFile);
        if(jsonData==nullptr){
            return false;
        }
        objectJson _objectJson;
        if(_objectJson.unDataSerializeScriptData(_baseAutoSetJson,jsonData)==nullptr){
            return false;
        }
    return true;
}
void objectAddGameAT::dataToBase(){
    if(!_baseAutoSetJson->Option.empty()){
        for(auto a:_baseAutoSetJson->Option){
            if(a.first=="gameName"){
                baseGameData->gameName=a.second;
            }
            if(a.first=="defaultFont"){
                QVariant defaultFontValue=a.second;
                baseGameData->defaultFonts=(defaultFontValue).toBool();
            }
            if(a.first=="sharedMemory"){
                QVariant sharedMemoryValue=a.second;
                baseGameData->taskMemorySharing=(sharedMemoryValue).toBool();
            }
            if(a.first=="writeCopy"){
                QVariant writeCopyValue=a.second;
                baseGameData->taskMemoryOptimization=(writeCopyValue).toBool();
            }
            if(a.first=="rtServer"){
                QVariant rtServerValue=a.second;
                baseGameData->taskRealTimePriority=(rtServerValue).toBool();
            }
            if(a.first=="dockSystemVersion"){
                baseGameData->dockSystemVersion=a.second;
            }
            if(a.first=="monoState"){
                QVariant monoState=a.second;
                baseGameData->monoState=(monoState).toBool();;
            }
            if(a.first=="geckoState"){
                QVariant geckoState=a.second;
                baseGameData->geckoState=(geckoState).toBool();;
            }
            if(a.first=="mainPrcoName"){
                baseGameData->mainPrcoName=a.second;
            }
            baseGameData->wineVersion=_objAddDataAT.pWineVersion;
        }
    }
    if(!_baseAutoSetJson->Dxvk.empty()){
        for(auto a:_baseAutoSetJson->Dxvk){
            if(a.first=="dxvkVersion"){
                baseGameData->dxvkVerson=a.second;
            }
            if(a.first=="dxvkState"){
                QVariant dxvkStateValue=a.second;
                baseGameData->dxvkState=(dxvkStateValue).toBool();
            }
            if(a.first=="dxvkHUD"){
                QVariant dxvkHUDValue=a.second;
                baseGameData->dxvkHUD=(dxvkHUDValue).toBool();
            }
        }
    }
    if(!_baseAutoSetJson->Regs.empty()){
        baseGameData->dockRegs=_baseAutoSetJson->Regs;
    }
    if(!_baseAutoSetJson->Libs.empty()){
        baseGameData->dockLibs=_baseAutoSetJson->Libs;
    }
    if(!_baseAutoSetJson->Env.empty()){
        baseGameData->dockEnv=_baseAutoSetJson->Env;
    }
    if(_baseAutoSetJson->Args!=nullptr){
        baseGameData->gameOtherAgrs=_baseAutoSetJson->Args;
    }
    if(!_baseAutoSetJson->AttachProc.empty()){
        baseGameData->attachProc=_baseAutoSetJson->AttachProc;
    }
    baseGameData->dockPath=_objAddDataAT.pDckPath;
    baseGameData->dockName=_objAddDataAT.pDockName;
    baseGameData->gameExe=_objAddDataAT.pGameExePath;
    QFileInfo fi = QFileInfo(_objAddDataAT.pGameExePath);
    baseGameData->workPath=fi.path();
    objectJson* _objectJson=new objectJson();
    baseGameData->gameCID=_objectJson->GetRandomCID();
    delete _objectJson;
    _objectJson=nullptr;
    baseGameData->gameIco=":/res/img/vek.ico";
    for(auto &x : g_vekLocalData.wineVec){
        if(x.first==_objAddDataAT.pWineVersion){
            baseGameData->wineVersion=x.second.WineInstallName;
            baseGameData->winePath=x.second.wineInstallPath;
            break;
        }
    }
}
void objectAddGameAT::objectAutoObj(){
    if(objDiyAddGame!=nullptr){
        delete objDiyAddGame;
        objDiyAddGame=nullptr;
    }
    emit Tips("配置容器中请稍候!");
    objDiyAddGame=new objectAddGameMT(baseGameData,nullptr);
    objDiyAddGame->InitDockObj(false);
    objDiyAddGame->optionRegs();
    objDiyAddGame->DockLibsInstall();
    objDiyAddGame->SaveDataToJson(baseGameData->dockName,*baseGameData);
    delete objDiyAddGame;
    objDiyAddGame=nullptr;
}
void objectAddGameAT::run(){
    _baseAutoSetJson=new BaseAutoSetJson();
    baseGameData=_objAddDataAT.pBaseGameData;
    if(!jsonUnserialize(_objAddDataAT.pJsonPath)){
        emit Error("配置容器出错!",true);
        return;
    }else{
        dataToBase();
        objectAutoObj();
        emit Done();
    }
}
