#ifndef VEKEXPORTJSON_H
#define VEKEXPORTJSON_H

#include "common.h"
#include "objectJson.h"
#include "vekInitObject.h"
namespace Ui {
class vekExportJson;
}

class vekExportJson : public QWidget
{
    Q_OBJECT

public:
    explicit vekExportJson(QWidget *parent = nullptr);
    ~vekExportJson();
    void ExportJson(BaseAppData);
private:
    Ui::vekExportJson *ui;
private slots:
    void SaveJson();
signals:
    void _unExportJson();
};

#endif // VEKEXPORTJSON_H
