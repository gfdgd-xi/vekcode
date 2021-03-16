#ifndef VEKABOUT_H
#define VEKABOUT_H

#include "obj/common.h"
namespace Ui {
class vekAbout;
}

class vekAbout : public QDialog
{
    Q_OBJECT

public:
    explicit vekAbout(QWidget *parent = nullptr);
    ~vekAbout();
    void GetVerInfo();
private:
    Ui::vekAbout *ui;
    QString vekLogShow="https://gitee.com/JackLee02/vekGame/raw/master/vekLogShow.json";
signals:
     void _unVekAbout();
};

#endif // VEKDIALOG_H
