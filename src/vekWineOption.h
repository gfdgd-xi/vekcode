#ifndef VEKWINEOPTION_H
#define VEKWINEOPTION_H

#include "obj/objectGitWine.h"
#include "obj/common.h"
#include "obj/pObject.h"
namespace Ui {
class vekWineOption;
}

class vekWineOption : public QWidget
{
    Q_OBJECT

public:
    explicit vekWineOption(QWidget *parent = nullptr);
    void dealclicked();
    ~vekWineOption();
private slots:
    void appendTextToLog();
    void overGitThreadSignals();
    void on_toolButton();
    void onButton_Install();
    void deleteWine();
private:
    Ui::vekWineOption *ui;
    objectGitWine *githread;
    void InitWineInstall();
    void GetWineGitInfo();   
    void WineVersionComoboBox();
    void controlState(bool pState);
signals:
    void _unInitWineOption();
};

#endif // VEKOPTION_H
