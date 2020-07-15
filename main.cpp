#include <QApplication>
#include "src/vek.h"
#include "src/baseRes.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vek w;
    w.show();
    return a.exec();
}

