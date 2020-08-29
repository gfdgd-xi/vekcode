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
private:
    Ui::vekAbout *ui;
signals:
     void _unVekAbout();
};

#endif // VEKDIALOG_H
