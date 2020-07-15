#ifndef VEKGAMEADDMULTI_H
#define VEKGAMEADDMULTI_H

#include "common.h"
#include "vekGameAddMT.h"
namespace Ui {
class vekGameAddMulti;
}

class vekGameAddMulti : public QDialog
{
    Q_OBJECT
public:
    explicit vekGameAddMulti(QWidget *parent = nullptr);
    ~vekGameAddMulti();
private:
    Ui::vekGameAddMulti *ui;
    void connectObject();
    void MultiGameDiy();
    void MultiGameAuto();
signals:
    void _unMultGameAdd();
    void _MultiGameDiy();
    void _MultiGameAuto();
};

#endif // VEKGAMEMULTIADD_H
