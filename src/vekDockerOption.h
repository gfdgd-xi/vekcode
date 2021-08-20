#ifndef VEKDOCKEROPTION_H
#define VEKDOCKEROPTION_H

#include "obj/common.h"
#include "obj/objectJson.h"
#include "obj/objectAppMT.h"
#include <QTableView>
#include <QStandardItemModel>
namespace Ui {
class vekDockerOption;
}

class vekDockerOption : public QWidget
{
    Q_OBJECT
public:
    explicit vekDockerOption(QWidget *parent = nullptr);
    void vekAppAddConnectObject(const SdockerData&);
    ~vekDockerOption();
public:
    Ui::vekDockerOption *ui;
private:
    SdockerData* tempDockData=nullptr;
    vector<QString> _dockSystemVersion={"win10","win7","win81","win8","winxp","winxp64"};
    vector<QString> _dockVer={"win32","win64"};
    vector<QString> _dockWineVer={"wine","wine64"};
    bool vekAppConfigObj();
    bool checkDocerOption();
    bool forceInitDocer();
    void saveOptionData();

signals:
    void toObjectArgs(SappData);
    void _unOption();
    void _upData(SdockerData,SappData*,EADEType);
private slots:
    void objectButton();
    void wineChanged();
};

#endif // VEKADDGAME_H
