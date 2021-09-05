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
    static vekAbout& GetInstance(){
        static vekAbout instance;
       return instance;
    }
    void GetVerInfo();
private:
    vekAbout();
    ~vekAbout();
    vekAbout(const vekAbout& instance);
    const vekAbout& operator =(const vekAbout& instance);
    Ui::vekAbout *ui;
    QString vekLogShow="https://gitee.com/JackLee02/vekGame/raw/master/vekLogShow.json";
};

#endif // VEKDIALOG_H
