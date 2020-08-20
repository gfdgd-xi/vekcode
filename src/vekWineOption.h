#ifndef VEKWINEOPTION_H
#define VEKWINEOPTION_H

#include "vekGitWine.h"
#include "common.h"
#include "vekInitObject.h"
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
    vekGitWine *githread;
    void InitWineInstall();
    void GetWineGitInfo();   
    void WineVersionComoboBox();
    void controlState(bool pState);
signals:
    void _unInitWineOption();
};

#endif // VEKOPTION_H
