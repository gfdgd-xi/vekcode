#include <QApplication>
#include "src/vek.h"
#include "src/baseRes.h"
#include "src/objectSource.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    objectSource* objSource=new objectSource;
    objSource->loadAllData();
    delete objSource;
    objSource=nullptr;
    vek w;
    //w.startTray();
    w.show();
    return a.exec();
}

