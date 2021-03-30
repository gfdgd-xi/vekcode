#include "vupdate.h"

#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vUpdate w;
    w.show();
    w.lableVersionShow(argv[1]);
    w.vUrlLogStr=argv[2];
    w.vUrlFileStr=argv[3];
    w.GetVerInfo();
    w.connectOBject();
    return a.exec();
}
