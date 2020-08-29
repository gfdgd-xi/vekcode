#ifndef VEKAPPADDMULTI_H
#define VEKAPPADDMULTI_H

#include "obj/common.h"
#include "obj/objectAppMT.h"
#include "obj/pObject.h"
namespace Ui {
class vekAppAddMulti;
}

class vekAppAddMulti : public QDialog
{
    Q_OBJECT
public:
    explicit vekAppAddMulti(QWidget *parent = nullptr);
    ~vekAppAddMulti();
private:
    Ui::vekAppAddMulti *ui;
    void connectObject();
    void MultiAppDiy();
    void MultiAppAuto();
signals:
    void _unMultAppAdd();
    void _MultiAppDiy();
    void _MultiAppAuto();
};

#endif // VEKGAMEMULTIADD_H
