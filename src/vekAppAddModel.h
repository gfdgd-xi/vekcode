#ifndef VEKAPPADDMODEL_H
#define VEKAPPADDMODEL_H

#include "obj/common.h"
#include "obj/objectAppMT.h"
namespace Ui {
class vekAppAddModel;
}

class vekAppAddModel : public QDialog
{
    Q_OBJECT
public:
    explicit vekAppAddModel(QWidget *parent = nullptr);
    ~vekAppAddModel();
private:
    Ui::vekAppAddModel *ui;
    void connectObject();
    void MultiAppDiy();
    void MultiAppAuto();
signals:
    void _unMultAppAdd();
    void _MultiAppDiy();
    void _MultiAppAuto();
};

#endif // VEKGAMEMULTIADD_H
