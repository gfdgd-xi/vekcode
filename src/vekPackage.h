#ifndef VEKPACKAGE_H
#define VEKPACKAGE_H

#include "obj/common.h"


namespace Ui {
class vekPackage;

}

class vekPackage : public QDialog
{
    Q_OBJECT

public:
    explicit vekPackage(QWidget *parent = nullptr);
    ~vekPackage();
private:
    Ui::vekPackage *ui;
    void initUI();
};
static QString str_ui[]={"包描述:",
                        "包名-英文",
                        "包名-中文",
                        "原始容器名",
                        "目标容器名:",
                        "应用分类:",
                        "图标名",
                        "启动程序名",
                        "启动文件路径",
                        "输出包名",
                        "专业版包名",
                        "包版本号",
                        "旧包名",
                        "Wine依赖：",
                        "虚组件",
                        "wine运行路径",
                        "补丁加载路径"};
#endif // VEKDEBUG_H
