#include "objectSource.h"
#include "pObject.h"
objectSource::objectSource()
{

}
objectSource::~objectSource()
{

}
//获取数据
string objectSource::GetReData(QString url){
    objectGetCurl* _vekgetcurl=new objectGetCurl();
    string sdata=_vekgetcurl->vekGetData(url.toStdString());
    delete _vekgetcurl;
    _vekgetcurl=nullptr;
    return sdata;
}
//更新源数据
void objectSource::updateSrcDataObject(){
    objectJson _objectJson;
    for(auto &[d,k]:g_vekLocalData.map_wine_src_list){
        string sdata=GetReData(k);
        if(sdata!="error"){
            _objectJson.unSerializeLocalWineApp(d,QString::fromStdString(sdata),unJsonWineList);
        }else{
            pObject::vekError("更新wine源数据失败");
        }
    }
    for(auto &[i,o]:g_vekLocalData.map_app_src_list){
        string sdata=GetReData(o);
        if(sdata!="error"){
            _objectJson.unSerializeLocalWineApp(i,QString::fromStdString(sdata),unJsonGameList);
        }else{
            pObject::vekError("更新软件源数据失败");
        }
    }
    //更新和获取winetricksServer数据
    std::string swdata=GetReData(g_srcUrl.SrcWinetrickServerUrl);
    if(swdata!="error"){
        json jx=json::parse(swdata);
        for(auto [x,y]:jx.items()){
            winetricks_server_url_list.insert(pair<QString, QString> (QString::fromStdString(x), QString::fromStdString(y)));
        }
    }else{
        pObject::vekError("获取winetricks上游服务器列表失败,winetricks将以默认服务器为你提供下载服务");
    }
}
//加载所有数据
void objectSource::loadAllData(){
    QString jsonPath=QApplication::applicationDirPath()+"/data.json";
    objectJson _objectJson;
    g_vekLocalData.map_app_json_list.clear();
    g_vekLocalData.map_wine_json_list.clear();
    if(!QFile(jsonPath).exists()){
        //默认源数据
        g_vekLocalData.map_wine_src_list["DefaultWineSrc"]=g_srcUrl.SrcWineUrl;
        g_vekLocalData.map_app_src_list["DefaultGameSrc"]=g_srcUrl.SrcAppUrl;
        updateSrcDataObject();
    }else{
        if(_objectJson.unDataSerializeLocalData()){
            updateSrcDataObject();
        }
    }
    _objectJson.WriteLocalData();
}
