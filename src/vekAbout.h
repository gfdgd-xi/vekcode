#ifndef VEKABOUT_H
#define VEKABOUT_H

#include "common.h"
#include "vekGetCurl.h"
namespace Ui {
class vekAbout;
}

class vekAbout : public QDialog
{
    Q_OBJECT

public:
    explicit vekAbout(QWidget *parent = nullptr);
    ~vekAbout();
    void getUpdateLogs();
private:
    Ui::vekAbout *ui;
    vekGetCurl* vekgetcurl=nullptr;
signals:
     void _unVekAbout();
};

#endif // VEKDIALOG_H
