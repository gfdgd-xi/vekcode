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
    vekAbout(const QDialog)=delete;
    vekAbout& operator =(const QDialog&)=delete;
    static vekAbout& get_instance(){
        static vekAbout instance;
        return instance;
    }
    ~vekAbout();
    void GetVerInfo();
private:
    vekAbout();
    Ui::vekAbout *ui;
    QString vekLogShow="https://gitee.com/JackLee02/vekGame/raw/master/vekLogShow.json";
};

#endif // VEKDIALOG_H
