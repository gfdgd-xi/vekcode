#include "pObject.h"
#include "objectJson.h"

void pObject::oLogs(QString str){
    qInfo()<<str;
}
void pObject::vekTip(QString tipInfo){
    QMessageBox::warning(nullptr,"TIP",tipInfo);
}
void pObject::vekError(QString tipInfo){
    QMessageBox::warning(nullptr,"ERROR",tipInfo);
}
bool pObject::vekMesg(QString tipText){
    QMessageBox msgBox;
    msgBox.setInformativeText(tipText);
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setStyleSheet("QLabel{"
                          "qproperty-alignment:AlignHCenter;"
                          "min-width: 400px;"
                          "min-height: 20px; "
                          "}");
    int msgRet=msgBox.exec();
    if(msgRet==QMessageBox::Ok){
        return true;
    }
    return false;
}
//保存Docker数据
void pObject::saveDockerDataToJson(BaseDockData dockData,QString dockName){
    objectJson _objectJson;
    _objectJson.updateDockerNodeData(dockData,dockName);
}
//保存Docker数据
void pObject::addAppDataToJson(BaseDockData dockData,BaseAppData appData){
    objectJson _objectJson;
    _objectJson.addAppNodeData(dockData,appData);
}
//保存App数据
void pObject::saveAppDataToJson(BaseDockData dockData,BaseAppData appData){
    objectJson _objectJson;
    _objectJson.updateAppNodeData(dockData,appData);
}
//删除wine
void pObject::deleteWineDataToJson(QString wineName){
    objectJson _objectJson;
    _objectJson.deleteWineNodeData(wineName);
}
BaseDockData pObject::getDockerData(QString dockName){
    BaseDockData tempDockData={};
    if(!g_vekLocalData.dockerVec.empty()){
        for(auto a:g_vekLocalData.dockerVec){
            if(a.first==dockName){
                tempDockData=a.second;
                break;
            }
        }
    }
    return tempDockData;
}
BaseAppData pObject::getAppData(BaseDockData dockData,QString appCID){
    BaseAppData tempAppData={};
    for(auto a:dockData.dData){
        if(a.first==appCID){
            tempAppData=a.second;
            break;
        }
    }
    return tempAppData;
}
QString pObject::getFileStr(QString filePath){
    QFile file(filePath);
    if(!file.exists())
    {
        return nullptr;
    }
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QString temp = file.readAll();
    file.close();
    return temp;
}
void pObject::saveStrToFile(QString strFile,QString filePath){
    QFile file(filePath);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&file);
    out << strFile;
    file.close();
}
QString pObject::pathNullToStr(QString str){
    if(str.contains(" ",Qt::CaseSensitive)){
        str="\""+str+"\"";
    }
    return str;
}
//综合注册表操作
QStringList pObject::dockerRegeditStr(QString rObj,QString rPath,QString rKey,QString rTValue,QString rValue){
    QStringList argsList;
    //处理注册表路径空格
    if(rPath.contains(" ",Qt::CaseSensitive)){
        rPath="\""+rPath+"\"";
    }
    //处理注册表键空格
    if(rKey.contains(" ",Qt::CaseSensitive)){
        rKey="\""+rKey+"\"";
    }
    //处理注册表值空格
    if(rValue.contains(" ",Qt::CaseSensitive)){
        rValue="\""+rValue+"\"";
    }
    if(rObj=="add"){
        argsList.append("reg");
        argsList.append(rObj);
        argsList.append(rPath);
        argsList.append("/v");
        argsList.append(rKey);
        argsList.append("/t");
        argsList.append(rTValue);
        argsList.append("/d");
        argsList.append(rValue);
        argsList.append("/f");
    }
    if(rObj=="delete"){
        argsList.append("reg");
        argsList.append(rObj);
        argsList.append(rPath);
        argsList.append("/v");
        argsList.append(rKey);
        argsList.append("/f");
    }
    return argsList;
}

void pObject::qwidgetGeometry(QWidget* qwidget){
    QDesktopWidget *deskdop = QApplication::desktop();
    qwidget->move((deskdop->width() - qwidget->width())/2, (deskdop->height() - qwidget->height())/2);
}
