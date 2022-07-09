#ifndef OBJECTTRAY_H
#define OBJECTTRAY_H

#include <QThread>
#include <QProcess>
#include <QApplication>

class objectTray:public QThread
{
    Q_OBJECT
public:
    explicit objectTray(QObject *parent = nullptr);
    ~objectTray();
    std::vector<QString> procManages;
private:
   QProcess* m_cmd=nullptr;
   void StartTray();
protected:
   void run();
public slots:
    void ExitTray();
};

#endif // OBJECTTRAY_H
