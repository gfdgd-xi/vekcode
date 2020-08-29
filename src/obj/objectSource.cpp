#include "objectSource.h"

objectSource::objectSource()
{

}
objectSource::~objectSource()
{

}
string objectSource::GetReData(QString url){
    objectGetCurl* _vekgetcurl=new objectGetCurl();
    string sdata=_vekgetcurl->vekGetData(url.toStdString());
    delete _vekgetcurl;
    _vekgetcurl=nullptr;
    return sdata;
}
void objectSource::updateSrcDataObject(){
    objectJson _objectJson;
    for(auto &[d,k]:g_vekLocalData.wineSource){
        string sdata=GetReData(k);
        if(sdata!="error"){
            _objectJson.unSerializeLocalWineApp(d,QString::fromStdString(sdata),unJsonWineList);
        }else{
            vekError("更新wine源数据失败");
        }
    }
    for(auto &[i,o]:g_vekLocalData.appScrSource){
        string sdata=GetReData(o);
        if(sdata!="error"){
            _objectJson.unSerializeLocalWineApp(i,QString::fromStdString(sdata),unJsonGameList);
        }else{
            vekError("更新游戏源数据失败");
        }
    }
}
void objectSource::loadAllData(){
    QString jsonPath=QDir::currentPath()+"/data.json";
    objectJson _objectJson;
    if(!QFile(jsonPath).exists()){
        //默认源数据
        g_vekLocalData.wineSource.insert(pair<QString,QString>("DefaultWineSrc","https://gitee.com/JackLee02/vekGame/raw/master/wineJsonSource.json"));
        g_vekLocalData.appScrSource.insert(pair<QString,QString>("DefaultGameSrc","https://gitee.com/JackLee02/vekGame/raw/master/appJsonSource.json"));
        updateSrcDataObject();
    }else{
        if(_objectJson.unDataSerializeLocalData()){
            g_vekLocalData.appJsonList.clear();
            g_vekLocalData.wineJsonList.clear();
            updateSrcDataObject();  
        }
    }
    _objectJson.WriteLocalData();
}
