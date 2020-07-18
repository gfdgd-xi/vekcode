#ifndef OBJECTTRAY_H
#define OBJECTTRAY_H

#include "common.h"
class objectTray:public QThread
{
    Q_OBJECT
public:
    explicit objectTray(QObject *parent = nullptr);
    ~objectTray();
    BaseWineData _baseWineData;
    void exitTray();
private:
   QProcess* m_cmd=nullptr;
   void startTray();
protected:
    void run();
};

#endif // OBJECTTRAY_H
