#ifndef OBJECTSOURCE_H
#define OBJECTSOURCE_H

#include "common.h"
#include "vekGetCurl.h"
#include "objectJson.h"

class objectSource
{
public:
    objectSource();
    ~objectSource();
    void loadAllData();
    void updateSrcDataObject();
private:
    std::string GetReData(QString);
};

#endif // OBJECTSOURCE_H
