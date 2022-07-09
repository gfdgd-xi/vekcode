#ifndef VEKEXPORTJSON_H
#define VEKEXPORTJSON_H

#include "obj/common.h"
#include "obj/objectJson.h"
#include "obj/pObject.h"
namespace Ui {
class vekExportJson;
}

class vekExportJson : public QWidget
{
    Q_OBJECT

public:
    explicit vekExportJson(QWidget *parent = nullptr);
    ~vekExportJson();
    void ExportJson(SdockerData,QString);
private:
    Ui::vekExportJson *ui;
private slots:
    void SaveJson();
signals:
    void _unExportJson();
};

#endif // VEKEXPORTJSON_H
