#ifndef OBJECTNET_H
#define OBJECTNET_H

#include <QObject>

class objectNet : public QObject
{
    Q_OBJECT
public:
    explicit objectNet(QObject *parent = nullptr);
    ~objectNet();
private:
    QString w_url;
    QString upass;
    void objSetNetDNS();
    void objSetNetHosts();
    void objNetSpeedTest();
    void objExtendQProc();
signals:

};

#endif // OBJECTNET_H
