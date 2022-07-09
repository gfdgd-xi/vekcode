#include "objvgit.h"
#include <iostream>
#include <QDir>
using namespace std;

int main(int argc, char *argv[])
{
    objvgit* ovt=new objvgit();
    std::string url="https://jihulab.com/JackLee_CN/veklutris6.git";
    std::string path=(QDir::currentPath()+"/vekLutris6").toStdString();
    ovt->vek_Clone(url,path);
    return 0;
}
